#!/usr/bin/env python3
"""Round-trip write tests for the C++11 read-write target.

For every format that has a Java specwrite test, take the existing KST-derived
C++ read test, make it read the .bin, _write() it into a same-size buffer,
re-read that buffer and run the original assertions on the re-read object.
"""
import concurrent.futures as cf, os, re, subprocess, sys, glob, json, shutil

K = os.path.expanduser('~/claude/kaitai')
T = f'{K}/kaitai_struct_tests'
RT = os.environ.get('RT', f'{K}/kaitai_struct_cpp_stl_runtime')
STD = os.environ.get('STD', '11')  # C++ standard: 11 or 98 (98 only with MODE=ro)
SAN = ['-fsanitize=address,undefined', '-fno-omit-frame-pointer'] if os.environ.get('SAN') == '1' else []
KSC = os.environ.get('KSC', f'{K}/kaitai_struct_compiler/jvm/target/universal/stage/bin/kaitai-struct-compiler')
ALL = os.environ.get('ALL') == '1'  # every C++ test, not only those with a Java write test
RO = os.environ.get('MODE') == 'ro'  # read-only baseline: upstream C++11 output, unmodified tests
OUT = f'{K}/rwtest/' + os.environ.get('OUTNAME', 'out' + ('-ro' if RO else ''))
WFLAG = [] if RO else ['-w']
CXX = ['g++', f'-std=c++{STD}', '-O0', '-g', '-w'] + SAN + [ '-DKS_ZLIB', '-DKS_STR_ENCODING_ICONV',
       '-I', f'{OUT}/gen', '-I', RT, '-I', f'{T}/spec/cpp_stl_{STD}/prereq', '-I', f'{T}/spec/cpp_stl_{STD}']

def norm(s): return s.replace('_', '').lower()

def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)

def main():
    only = sys.argv[1:]
    java = {norm(os.path.basename(p)[4:-5]) for p in glob.glob(f'{T}/spec/java/src/io/kaitai/struct/specwrite/Test*.java')}
    tests = {}
    for p in sorted(glob.glob(f'{T}/spec/cpp_stl_{STD}/test_*.cpp') + glob.glob(os.environ.get('EXTRA_SPEC', '/nonexistent') + '/test_*.cpp')):
        name = os.path.basename(p)[5:-4]
        if ALL or norm(name) in java:
            tests[name] = p
    if only:
        tests = {k: v for k, v in tests.items() if k in only}
    os.makedirs(f'{OUT}/obj', exist_ok=True)
    gen = f'{OUT}/gen'
    if not only or not os.path.isdir(gen):
        shutil.rmtree(gen, ignore_errors=True)
        os.makedirs(gen)
        ksys = sorted(glob.glob(f'{T}/formats/*.ksy'))
        r = sh([KSC, '-t', 'cpp_stl', '--cpp-standard', STD] + WFLAG + [ '--ksc-json-output',
                '--outdir', gen, '-I', f'{T}/formats:{T}/formats/ks_path:{K}/formats'] + ksys, cwd=f'{T}/formats')
        open(f'{OUT}/ksc.json', 'w').write(r.stdout)
    else:
        for name in tests:
            sh([KSC, '-t', 'cpp_stl', '--cpp-standard', STD] + WFLAG + [ '--outdir', gen,
                '-I', f'{T}/formats:{T}/formats/ks_path:{K}/formats', f'{T}/formats/{name}.ksy'], cwd=f'{T}/formats')

    def compile_obj(src, obj):
        if os.path.exists(obj) and os.path.getmtime(obj) > os.path.getmtime(src) and not only:
            return True, ''
        r = sh(CXX + ['-c', src, '-o', obj])
        return r.returncode == 0, r.stderr

    rt_objs = []
    for src in [f'{RT}/kaitai/kaitaistream.cpp'] + glob.glob(f'{T}/spec/cpp_stl_{STD}/prereq/*.cpp'):
        obj = f'{OUT}/obj/rt_' + os.path.basename(src) + '.o'
        ok, err = compile_obj(src, obj)
        if not ok:
            print('runtime/prereq compile failed', src, err[:2000]); sys.exit(1)
        rt_objs.append(obj)
    main_cpp = f'{OUT}/main.cpp'
    open(main_cpp, 'w').write('#define BOOST_TEST_MODULE rw\n#define BOOST_TEST_DYN_LINK\n#include <boost/test/unit_test.hpp>\n')
    main_obj = f'{OUT}/obj/main.o'
    if not os.path.exists(main_obj):
        r = sh(CXX + ['-c', main_cpp, '-o', main_obj]); assert r.returncode == 0, r.stderr

    gen_objs = {}
    def build_gen(src):
        obj = f'{OUT}/obj/' + os.path.basename(src) + '.o'
        ok, err = compile_obj(src, obj)
        return src, obj, ok, err
    with cf.ThreadPoolExecutor(40) as ex:
        for src, obj, ok, err in ex.map(build_gen, glob.glob(f'{gen}/*.cpp')):
            gen_objs[os.path.basename(src)[:-4]] = (obj, ok, err)

    def deps(name, seen):
        if name in seen: return
        seen.add(name)
        h = f'{gen}/{name}.h'
        if not os.path.exists(h): return
        for inc in re.findall(r'#include "([a-z0-9_]+)\.h"', open(h).read() + open(f'{gen}/{name}.cpp').read()):
            if os.path.exists(f'{gen}/{inc}.cpp'):
                deps(inc, seen)

    def run_test(item):
        name, path = item
        if name not in gen_objs:
            return name, 'ksc', 'not generated'
        seen = set(); deps(name, seen)
        for d in seen:
            obj, ok, err = gen_objs[d]
            if not ok:
                return name, 'cc-format', d + ': ' + err
        src = open(path).read()
        m = re.search(r'kaitai::kstream ks\(&ifs\);\n(\s*)(\w+)\* r = new (\w+)\((.*?)&ks\);\n', src)
        if not m:
            return name, 'skip', 'unrecognised test shape'
        ind, typ, args = m.group(1), m.group(2), m.group(4)
        if RO:
            new = m.group(0)
        else:
          new = (f'kaitai::kstream ks(&ifs);\n'
               f'{ind}{typ}* r0 = new {typ}({args}&ks);\n'
               f'{ind}r0->_read();\n'
               f'{ind}r0->_fetch_instances();\n'
               f'{ind}r0->_check();\n'
               f'{ind}kaitai::kstream wks(std::string(ks.size(), \'\\0\'));\n'
               f'{ind}r0->_write(&wks);\n'
               f'{ind}std::string wbuf = wks.to_byte_array();\n'
               f'{ind}kaitai::kstream ks2(wbuf);\n'
               f'{ind}{typ}* r = new {typ}({args}&ks2);\n'
               + ('' if re.search(r'(^|\n)\s*r->_read\(\);', src[m.end():]) else f'{ind}r->_read();\n'))
        src = src[:m.start()] + new + src[m.end():]
        if not RO:
            src = src.replace('    delete r;\n', '    delete r;\n    delete r0;\n')
        tdir = f'{OUT}/t/{name}'
        os.makedirs(tdir, exist_ok=True)
        tsrc = f'{tdir}/test.cpp'
        open(tsrc, 'w').write(src)
        exe = f'{tdir}/test'
        objs = [gen_objs[d][0] for d in sorted(seen)]
        r = sh(CXX + [tsrc, main_obj] + objs + rt_objs + ['-lboost_unit_test_framework', '-lz', '-o', exe])
        if r.returncode != 0:
            return name, 'cc-test', r.stderr
        r = sh([exe], cwd=T, timeout=60)
        if r.returncode != 0:
            return name, 'fail', (r.stdout + r.stderr)[-3000:]
        return name, 'pass', ''

    results = {}
    with cf.ThreadPoolExecutor(40) as ex:
        for name, status, detail in ex.map(run_test, sorted(tests.items())):
            results[name] = (status, detail)
    json.dump(results, open(f'{OUT}/results.json', 'w'), indent=1)
    from collections import Counter
    c = Counter(s for s, _ in results.values())
    print(f'{len(results)} tests:', dict(c))

main()

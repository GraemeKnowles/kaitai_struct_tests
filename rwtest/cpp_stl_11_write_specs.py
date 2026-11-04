#!/usr/bin/env python3
"""Build and run the hand-written C++11 read-write tests in
kaitai_struct_tests/spec/cpp_stl_11_write (ported from the Java specwrite tests).

Each test file becomes its own executable, so one crash doesn't hide the rest.
Env: KSC (compiler binary), RT (runtime source dir containing kaitai/).
Usage: write_specs.py [test_name ...]
"""
import concurrent.futures as cf, glob, json, os, re, shutil, subprocess, sys

K = os.path.expanduser('~/claude/kaitai')
T = f'{K}/kaitai_struct_tests'
STD = os.environ.get('STD', '11')
SPEC = f'{T}/spec/cpp_stl_{STD}_write'
OUT = f'{K}/rwtest/wspec' + ('' if STD == '11' else STD) + ('-san' if os.environ.get('SAN') == '1' else '')
KSC = os.environ.get('KSC', f'{K}/rwtest/ksc-snapshot/bin/kaitai-struct-compiler')
RT = os.environ.get('RT', f'{K}/rwtest/rt-snapshot')
PREREQ = f'{T}/spec/cpp_stl_{STD}/prereq'
SAN = ['-fsanitize=address,undefined', '-fno-omit-frame-pointer'] if os.environ.get('SAN') == '1' else []
CXX = ['g++', f'-std=c++{STD}', '-O0', '-g', '-w'] + SAN + [ '-DKS_ZLIB', '-DKS_STR_ENCODING_ICONV',
       '-I', f'{OUT}/gen', '-I', RT, '-I', PREREQ, '-I', SPEC]

def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)

def main():
    only = sys.argv[1:]
    gen = f'{OUT}/gen'
    shutil.rmtree(gen, ignore_errors=True)
    os.makedirs(gen)
    os.makedirs(f'{OUT}/obj', exist_ok=True)
    r = sh([KSC, '-t', 'cpp_stl', '--cpp-standard', STD, '-w', '--ksc-json-output', '--outdir', gen,
            '-I', f'{T}/formats:{T}/formats/ks_path:{K}/formats'] + sorted(glob.glob(f'{T}/formats/*.ksy')),
           cwd=f'{T}/formats')

    def build(src):
        obj = f'{OUT}/obj/' + os.path.basename(src) + '.o'
        r = sh(CXX + ['-c', src, '-o', obj])
        return os.path.basename(src)[:-4], obj, r.returncode == 0, r.stderr
    srcs = glob.glob(f'{gen}/*.cpp')
    common = [f'{RT}/kaitai/kaitaistream.cpp'] + glob.glob(f'{PREREQ}/*.cpp')
    objs = {}
    with cf.ThreadPoolExecutor(40) as ex:
        for name, obj, ok, err in ex.map(build, srcs + common):
            objs[name] = (obj, ok, err)
    common_objs = []
    for c in common:
        name = os.path.basename(c)[:-4]
        assert objs[name][1], objs[name][2]
        common_objs.append(objs[name][0])
    main_cpp = f'{OUT}/main.cpp'
    open(main_cpp, 'w').write('#define BOOST_TEST_MODULE cpp_stl_11_write\n#define BOOST_TEST_DYN_LINK\n#include <boost/test/unit_test.hpp>\n')
    r = sh(CXX + ['-c', main_cpp, '-o', f'{OUT}/obj/main.o']); assert r.returncode == 0, r.stderr

    def deps(name, seen):
        if name in seen or not os.path.exists(f'{gen}/{name}.cpp'): return
        seen.add(name)
        for inc in re.findall(r'#include "([a-z0-9_]+)\.h"', open(f'{gen}/{name}.h').read() + open(f'{gen}/{name}.cpp').read()):
            deps(inc, seen)

    def run(path):
        name = os.path.basename(path)[5:-4]
        seen = set()
        for inc in re.findall(r'#include "([a-z0-9_]+)\.h"', open(path).read()):
            deps(inc, seen)
        bad = [d for d in seen if not objs[d][1]]
        if bad:
            return name, 'cc-format', bad[0] + ': ' + objs[bad[0]][2][-3000:]
        exe = f'{OUT}/bin/{name}'
        os.makedirs(f'{OUT}/bin', exist_ok=True)
        r = sh(CXX + [path, f'{OUT}/obj/main.o'] + [objs[d][0] for d in sorted(seen)] + common_objs +
               ['-lboost_unit_test_framework', '-lz', '-o', exe])
        if r.returncode:
            return name, 'cc-test', r.stderr[-4000:]
        try:
            r = sh([exe, '--log_level=error', '--report_level=detailed'], cwd=T, timeout=60)
        except subprocess.TimeoutExpired:
            return name, 'timeout', ''
        out = re.sub(r'\x1b\[[0-9;]*m', '', r.stdout + r.stderr)
        return name, 'pass' if r.returncode == 0 else 'fail', out

    tests = sorted(glob.glob(f'{SPEC}/test_*.cpp'))
    if only:
        tests = [t for t in tests if os.path.basename(t)[5:-4] in only]
    res = {}
    with cf.ThreadPoolExecutor(40) as ex:
        for name, st, det in ex.map(run, tests):
            res[name] = (st, det)
    json.dump(res, open(f'{OUT}/results.json', 'w'), indent=1)
    for n, (s, d) in sorted(res.items()):
        bad = sorted(set(re.findall(r'Test case "(\w+)" (?:has failed|was aborted)', d)))
        crash = 'memory access violation' in d or 'signal' in d
        print(f'{s:9} {n}' + (f'  failing: {" ".join(bad)}' if bad else '') + ('  [CRASH]' if crash else ''))
    from collections import Counter
    print(len(res), dict(Counter(s for s, _ in res.values())))

main()

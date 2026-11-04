#!/usr/bin/env python3
"""Compare bytes written by the C++11 and Java read-write code for each test format.

Both read the format's test .bin, fetch instances and write into a buffer of
the same size; outputs must be identical.
"""
import concurrent.futures as cf, glob, json, os, re, subprocess, sys
K = os.path.expanduser('~/claude/kaitai')
T = f'{K}/kaitai_struct_tests'
STD = os.environ.get('STD', '11')
RW = os.environ.get('RW', f'{K}/rwtest/new-rw')
O = f'{K}/oracle'
CXX = ['g++', f'-std=c++{STD}', '-O0', '-g', '-w', '-DKS_ZLIB', '-DKS_STR_ENCODING_ICONV',
       '-I', f'{RW}/gen', '-I', f'{K}/kaitai_struct_cpp_stl_runtime', '-I', f'{T}/spec/cpp_stl_{STD}/prereq']

def camel(n): return ''.join(p[:1].upper() + p[1:] for p in n.split('_'))

items = []
for p in sorted(glob.glob(f'{T}/spec/cpp_stl_11/test_*.cpp') + glob.glob(f'{K}/rwtest/newspec/test_*.cpp')):
    name = os.path.basename(p)[5:-4]
    src = open(p).read()
    m = re.search(r'std::ifstream ifs\("src/([^"]+)"', src)
    m2 = re.search(r'(\w+)\* r = new (\w+)\(&ks\);', src)
    if not m or not m2 or not os.path.exists(f'{O}/cls/io/kaitai/struct/testwrite/{camel(name)}.class'):
        continue
    if not os.path.exists(f'{RW}/gen/{name}.cpp'):
        continue
    items.append((name, m.group(1), m2.group(1)))
if sys.argv[1:]:
    items = [i for i in items if i[0] in sys.argv[1:]]
os.makedirs(f'{O}/out', exist_ok=True)
for f in glob.glob(f'{O}/out/*'): os.remove(f)
args = []
for name, binf, _ in items:
    args += [camel(name), f'{T}/src/{binf}', f'{O}/out/{name}.java.bin']
subprocess.run(['java', '-cp', f'{O}/rt:{O}/cls', 'Dump'] + args, cwd=T)

objs = {os.path.basename(o)[:-6]: o for o in glob.glob(f'{RW}/obj/*.cpp.o')}
rt = [f'{RW}/obj/' + x for x in os.listdir(f'{RW}/obj') if x.startswith('rt_')]
def deps(name, seen):
    if name in seen or not os.path.exists(f'{RW}/gen/{name}.cpp'): return
    seen.add(name)
    for inc in re.findall(r'#include "([a-z0-9_]+)\.h"', open(f'{RW}/gen/{name}.h').read() + open(f'{RW}/gen/{name}.cpp').read()):
        deps(inc, seen)

def run(item):
    name, binf, typ = item
    d = f'{O}/c/{name}'; os.makedirs(d, exist_ok=True)
    open(f'{d}/main.cpp', 'w').write(f'''#include "{name}.h"
#include <fstream>
#include <iostream>
int main() {{
    try {{
        std::ifstream ifs("{T}/src/{binf}", std::ifstream::binary);
        kaitai::kstream ks(&ifs);
        {typ} r(&ks);
        r._read();
        r._fetch_instances();
        kaitai::kstream wks(std::string(ks.size(), '\\0'));
        r._write(&wks);
        std::ofstream ofs("{O}/out/{name}.cpp.bin", std::ios::binary);
        ofs << wks.to_byte_array();
    }} catch (std::exception& e) {{
        std::ofstream ofs("{O}/out/{name}.cpp.bin.err");
        ofs << e.what();
    }}
}}
''')
    seen = set(); deps(name, seen)
    if any(s not in objs for s in seen):
        return name, 'cc', 'missing obj'
    r = subprocess.run(CXX + [f'{d}/main.cpp'] + [objs[s] for s in sorted(seen)] + rt + ['-lz', '-o', f'{d}/main'], capture_output=True, text=True)
    if r.returncode: return name, 'cc', r.stderr[:2000]
    r = subprocess.run([f'{d}/main'], capture_output=True, text=True, timeout=60)
    if r.returncode: return name, 'crash', r.stderr[-500:]
    def get(ext):
        p = f'{O}/out/{name}.{ext}.bin'
        if os.path.exists(p): return open(p, 'rb').read()
        if os.path.exists(p + '.err'): return 'ERR: ' + open(p + '.err').read()
        return 'missing'
    j, c = get('java'), get('cpp')
    if isinstance(j, str) and isinstance(c, str): return name, 'both-err', f'java={j[:200]} | cpp={c[:200]}'
    if isinstance(j, str): return name, 'java-err', j[:300]
    if isinstance(c, str): return name, 'cpp-err', c[:300]
    if j == c: return name, 'same', ''
    i = next(k for k in range(min(len(j), len(c))) if j[k] != c[k]) if len(j) == len(c) else -1
    return name, 'differ', f'first diff at {i}: java={j[max(i,0):max(i,0)+8].hex()} cpp={c[max(i,0):max(i,0)+8].hex()}'

res = {}
with cf.ThreadPoolExecutor(40) as ex:
    for name, st, det in ex.map(run, items):
        res[name] = (st, det)
json.dump(res, open(f'{O}/results.json', 'w'), indent=1)
from collections import Counter
print(len(res), dict(Counter(s for s, _ in res.values())))
for n, (s, d) in sorted(res.items()):
    if s not in ('same',): print(f'{s:9} {n}: {d[:220]}')

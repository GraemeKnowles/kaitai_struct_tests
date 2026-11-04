#!/usr/bin/env python3
"""Derive the C++98 read-write tests (spec/cpp_stl_98_write) from the C++11 ones.

The C++98 target uses raw owning pointers: setters take ownership of a `T*`.
"""
import glob, os, re, sys
T = os.path.expanduser('~/claude/kaitai/kaitai_struct_tests/spec')
src, dst = f'{T}/cpp_stl_11_write', f'{T}/cpp_stl_98_write'
for p in sorted(glob.glob(f'{src}/*.cpp') + glob.glob(f'{src}/*.h')):
    s = open(p).read()
    s = s.replace('std::unique_ptr<', 'std::auto_ptr<')
    s = re.sub(r'std::move\((\w+)\)', r'\1.release()', s)
    s = s.replace('nullptr', '0')
    s = re.sub(r'(?<=[\w*])>>', '> >', s)   # no `>>` closing nested templates in C++98
    s = s.replace('> > ', '> > ').replace('cpp_stl_11', 'cpp_stl_98')
    header = '// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.\n'
    open(f'{dst}/{os.path.basename(p)}', 'w').write(header + s)

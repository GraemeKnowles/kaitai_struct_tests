#!/bin/sh
# Usage: pywrite.sh <ksc> <outdir>: run the Python write specs with the given compiler.
KSC=$1; OUT=$2; K=$HOME/claude/kaitai; T=$K/kaitai_struct_tests
rm -rf $OUT; mkdir -p $OUT/testwrite
$KSC -t python -w --python-package testwrite --outdir $OUT/testwrite -I "$T/formats:$T/formats/ks_path:$K/formats" $T/formats/*.ksy > $OUT/ksc.log 2>&1
touch $OUT/testwrite/__init__.py
cd $T && PYTHONPATH="$K/kaitai_struct_python_runtime:$OUT:spec/python/extra" PYTHONDONTWRITEBYTECODE=1 timeout 900 python3 -m unittest discover -s spec/python/specwrite -t spec/python > $OUT/result.txt 2>&1
tail -3 $OUT/result.txt

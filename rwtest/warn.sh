#!/bin/sh
# Usage: warn.sh <gen dir> <compiler> <std>: compile generated .cpp files with upstream's warning flags
GEN=$1; CC=$2; STD=$3; RT=${RT:-$HOME/claude/kaitai/kaitai_struct_cpp_stl_runtime}
ls $GEN/*.cpp | xargs -P 40 -I{} sh -c "$CC -std=$STD -fsyntax-only -Wall -Wextra -Wpedantic -DKS_ZLIB -DKS_STR_ENCODING_ICONV -I$GEN -I$RT -I$HOME/claude/kaitai/kaitai_struct_tests/spec/cpp_stl_${PREREQ_STD:-11}/prereq {} 2>&1" | grep -E "warning:" | sed -E 's/.*warning: //' | sed -E "s/‘[^’]*’/X/g; s/'[^']*'/X/g" | sort | uniq -c | sort -rn | head -12

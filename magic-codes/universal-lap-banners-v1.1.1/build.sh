#!/bin/sh
set -eu
project=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
sdk=${DKR_SDK:?Set DKR_SDK to the official DKR-R modding directory}
export DKR_LAP_REAL_CLANG="${CLANG:-clang}"
python3 -B "$sdk/build.py" "$project" --output "${1:?provide a new output directory}" \
 --clang "$project/clang-aligned.sh" --lld "${LLD:-ld.lld}" \
 --mod-tool "${RECOMP_MOD_TOOL:?Set RECOMP_MOD_TOOL to RecompModTool}"
python3 -B "$project/tests/test_stack_abi.py" "$1/mod.elf"

#!/bin/sh
set -eu
project=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
sdk=${DKR_SDK:?Set DKR_SDK to the official DKR-R modding directory}
python3 -B "$sdk/build.py" "$project" --output "${1:?provide a new output directory}" \
 --clang "${CLANG:-clang}" --lld "${LLD:-ld.lld}" \
 --mod-tool "${RECOMP_MOD_TOOL:?Set RECOMP_MOD_TOOL to RecompModTool}"

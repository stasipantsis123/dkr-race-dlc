#!/bin/sh
# Transparent compiler option adapter for the official SDK's --clang input.
# The runtime native-call ABI is stricter than MIPS O32's default 8-byte stack.
# Apply 16-byte stack frames to every unit, including the SDK runtime unit.
set -eu
exec "${DKR_LAP_REAL_CLANG:?Set by build.sh to the real Clang executable}" -mstack-alignment=16 "$@"

#!/bin/sh
set -eu
project=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
sdk=${DKR_SDK:?Set DKR_SDK to the official DKR-R modding directory}
mkdir -p "$project/test-output"
for mode in plain sanitized; do
 flags="-O2"; [ "$mode" = plain ] || flags="-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer"
 cc -std=c11 -Wall -Wextra -Werror $flags -isystem "$sdk/include" "$project/tests/test_banner.c" -o "$project/test-output/test_banner_$mode"
 ASAN_OPTIONS=detect_leaks=0 "$project/test-output/test_banner_$mode"
done

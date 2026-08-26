#!/usr/bin/env bash
# SPDX-License-Identifier: Apache-2.0

set -eu

if test "$#" -ne 1; then
  printf 'Usage: %s /dev/ttyACM0\n' "$0" >&2
  exit 2
fi

repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
workspace_dir=$(dirname "$repo_dir")
port=$1

if ! test -f "$workspace_dir/nuttx/nuttx.bin"; then
  printf 'Missing %s/nuttx/nuttx.bin; build the firmware first.\n' "$workspace_dir" >&2
  exit 1
fi

cd "$workspace_dir/nuttx"
exec make flash ESPTOOL_PORT="$port" ESPTOOL_BINDIR=./

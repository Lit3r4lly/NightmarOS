#!/bin/sh

set -e # stops if there is error
. ./scripts/iso.sh # run iso.sh script, for creating iso file

# strip symbols from binary
objcopy --strip-debug "sysroot/boot/$PROJECT_NAME.kernel" "$PROJECT_NAME.sym"

# runs the iso file with qemu
qemu-system-"$(./scripts/target-triplet-to-arch.sh "$HOST")" -cdrom "$PROJECT_NAME.iso"
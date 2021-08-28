#!/bin/sh

set -e # stops if there is error
. ./scripts/iso.sh # run iso.sh script, for creating iso file

# strip symbols from binary
objcopy --strip-debug "sysroot/boot/$PROJECT_NAME.kernel" "$PROJECT_NAME.sym"

QEMU_ARGS=(
    # Disable default devices, QEMU by default enables a ton of devices which slow down boot.
    "-nodefaults"

    "-vga"
    "std" # Use a standard VGA for graphics

    "-no-reboot" # exit instead of rebooting

    # using this, the program can write to x86 I/O port 0xE9 and talk
    "-debugcon"
    "file:info.log" # if needed - change this file to "/dev/stdout", and the log will be written to file
)

# runs the iso file with qemu
echo "Executing: qemu-system-i386 " "${QEMU_ARGS[@]}"
qemu-system-"$(./scripts/target-triplet-to-arch.sh "$HOST")" -cdrom "$PROJECT_NAME.iso" "${QEMU_ARGS[@]}" -d int 2> interrupts.txt
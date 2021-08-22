#!/bin/sh

set -e # stops if there is error
. ./scripts/iso.sh # run iso.sh script, for creating iso file

# create symbols file for gdb
objcopy --only-keep-debug "sysroot/boot/$PROJECT_NAME.kernel" "$PROJECT_NAME.sym"

# runs the iso file with qemu with debugging option
qemu-system-"$(./scripts/target-triplet-to-arch.sh "$HOST")" -s -S "$PROJECT_NAME.iso"

##########################################################################
# .gdbinit - in the base directory in the project there is .gdbinit file
# this file has created for the initialize of gdb when starting debugging in the base directory with gdb
# so, all you have to do is run 'make gdb', open another terminal and type 'gdb', and you good to go
# Good luck!

# HINT: make sure the .gdbinit enabled by auto-load safe-path:
# add to your ~/.gdbinit file this line:
# add-auto-load-safe-path ~/**/NightmareOS/.gdbinit
##########################################################################


### If there is no .gdbinit file (shouldn't happen), follow these:
# you should open gdb in the base directory and type those:
# (gdb) target remote localhost:1234
# (gdb) symbol-file <$PROJECT_NAME.sym>
# (gdb) break *kernel_main
# ....
#... start debugging ...

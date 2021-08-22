#!/bin/bash

# Cleans all obj, bin, iso etc. files

set -e # stops if there is error
. ./scripts/configure.sh -silent-configuration # run configure.sh with silent configuration for configure env vars

# loop through each sub-project and clean the output files
for PROJECT in $SUB_PROJECTS; do
    cd "$PROJECT" && make clean && cd .. # cleans sub-project output files
done

# remove output directories and iso file
rm -rf sysroot
rm -rf isodir
rm -rf "$PROJECT_NAME.iso"
rm -rf "$PROJECT_NAME.sym"
rm -rf .gdb_history
#!/bin/sh

set -e # stops if there is error
. ./scripts/configure.sh -silent-configuration # run configure.sh with silent configuration for configure env vars

# creates fake sysroot directory for the os
mkdir -p "$SYSROOT"

# loop through the sub-project for copying the headers and install them
for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd "$PROJECT" && DESTDIR="$SYSROOT" make install-headers) # copies the headers to /usr/include fake sysroot
done
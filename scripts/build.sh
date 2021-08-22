#!/bin/bash

set -e # stops if there is error
. ./scripts/headers.sh # run headers.sh and copy the headers into destination fake sysroot /usr/include directory

# loop through each sub-project and build it
for PROJECT in $SUB_PROJECTS; do
  (cd "$PROJECT" && DESTDIR="$SYSROOT" make build) # cd sub-project, set destinstaion directory for fake sysroot and build it
done
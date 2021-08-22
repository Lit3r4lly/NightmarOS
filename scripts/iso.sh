#!/bin/sh

set -e # stops if there is error
. ./scripts/build.sh # run build.sh and build the sub-projects

# creates "isodir" directory for iso creation
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

# copies the kernel binary from fake /boot/ to isodir/boot/
cp "sysroot/boot/$PROJECT_NAME.kernel" "isodir/boot/$PROJECT_NAME.kernel"

# creates grub.cfg file for multibott configuration
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "$PROJECT_NAME" {
	multiboot /boot/$PROJECT_NAME.kernel
}
EOF

# creates the iso file using the isodir directory
grub-mkrescue -o "$PROJECT_NAME.iso" isodir
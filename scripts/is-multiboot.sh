#!/bin/bash

# checks if the binary file passed as argument is multiboot
if grub-file --is-x86-multiboot "$1"; then
    echo "[x] The file is multiboot"
else
    echo "[x] The file is not multiboot"
fi;
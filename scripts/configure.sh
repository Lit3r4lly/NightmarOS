#!/bin/bash

export PROJECT_NAME="NightmareOS" # insert here base dir name (NightmareOS)
export SUB_PROJECTS="libc kernel" # names of sub-projects directories
export SYSTEM_HEADER_PROJECTS="libc kernel" # ^^^

if [ ${PWD##*/} != $PROJECT_NAME ]; then # checks if the script run from the base directory
    echo "[!] The project name doesn't fit the base directory name"
    exit 1
fi

export ROOT_DIR=${PWD} # set up root directory path of the project
export ARCH=$(./scripts/default-arch.sh) # set up desired arch name
export TOOLS=$(./scripts/cross-toolchain.sh) # set up cross toolchain path
export HOST=$(./scripts/default-host.sh) # set up default host name

# set up the cross toolchain env
export EMU=qemu-system-${ARCH} # set emulator name for desired arch
export CC=${TOOLS}/${HOST}-g++ # set up cross compiler path
export AS=${TOOLS}/${HOST}-as # set up cross assembler path
export AR=${TOOLS}/${HOST}-ar # set up cross archive linker path

# set up include directories for the kernel and specific architecture
export K_INCLUDE_DIR=$ROOT_DIR/kernel/include/kernel
export A_INCLUDE_DIR=$ROOT_DIR/kernel/include/arch/$ARCH

# set some directories up
export PREFIX=/usr # prefix for user directory
export EXEC_PREFIX=$PREFIX # execution prefix
export BOOTDIR=/boot # boot directory
export LIBDIR=$EXEC_PREFIX/lib # libraries directory
export INCLUDEDIR=$PREFIX/include # include directory

# set some flags
export CFLAGS='-O2 -g'
export CPPFLAGS=''

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot" # desired fake sysroot
export CC="$CC --sysroot=$SYSROOT" # set up the fake sysroot
# enables the compiler and linker to understand where to search libs, headers, etc..

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR" # enable include from fake sysroot
fi

if [ "$1" != "-silent-configuration" ]; then # do not set up configuration silently
       echo " _   _ _       _     _                             ___  ____"
       echo "| \ | (_) __ _| |__ | |_ _ __ ___   __ _ _ __ ___ / _ \/ ___|"
       echo "|  \| | |/ _\` | '_ \| __| '_ \` _ \ / _\` | '__/ _ \ | | \___ \ "
       echo "| |\  | | (_| | | | | |_| | | | | | (_| | | |  __/ |_| |___) |"
       echo "|_| \_|_|\__, |_| |_|\__|_| |_| |_|\__,_|_|  \___|\___/|____/"
       echo "         |___/"
       echo ""

       # Print configuration
       echo "Configuration:"
       echo "[V] Arch:" "$ARCH"
       echo "[V] Host:" "$HOST"
       echo "[V] Toolchain path:" "$TOOLS"
       echo "[V] Cross-Compiler path:" "$CC"
       echo "[V] CXX flags:" "$CFLAGS $CPPFLAGS"
       echo ""
else
    echo "" # silent configuration
fi
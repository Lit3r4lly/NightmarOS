#!/bin/bash
# required: wget, make, bison, flex, gmp, mpc, mpfr, textinfo,

set -e # stops if there is error

mkdir $HOME/src
cd $HOME/src

export BINUTILS_V="binutils-2.36"
export GCC_V="gcc-11.2.0"

# Install the binutils source
wget https://ftp.gnu.org/gnu/binutils/$BINUTILS_V.tar.gz
tar -xf $BINUTILS_V.tar.gz
rm -r $BINUTILS_v.tar.gz

#Install the gcc source
wget https://ftp.gnu.org/gnu/gcc/$GCC_V/$GCC_V.tar.gz
tar -xf $GCC_V.tar.gz
rm -r $GCC_V.tar.gz

# Preperation for the cross-compiler build
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Build binutils in the target path with the target arch
cd $HOME/src

mkdir build-binutils
cd build-binutils
../$BINUTILS_V/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

# Build gcc in the target path with the target arch
cd $HOME/src

# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
../$GCC_V/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

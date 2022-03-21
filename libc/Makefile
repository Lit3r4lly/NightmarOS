# Libc sub-proj Makefile

PROJECT_NAME="NightmareOS"# set project name
DEFAULT_HOST!=../scripts/default-host.sh # set default host
HOST?=DEFAULT_HOST # set current host for the build
HOSTARCH!=../scripts/target-triplet-to-arch.sh $(HOST) # set arch name by the host name

# set default flags for the compiler
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?= # passed as argument when calling "make <X>" as "DESTDIR='<Y>' make <X>"
PREFIX?=/usr/local # prefix for user directory usgae
EXEC_PREFIX?=$(PREFIX) # execution prefix
INCLUDEDIR?=$(PREFIX)/include # include directory
INCLUDE_DIR=include/ # include directory for headers, used by the compiler
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -fno-rtti -fno-exceptions # disable some standard features
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -I$(INCLUDE_DIR) # I$(INCLUDE_DIR) - include the BASE_DIR/kernel/include/ dir as global lib
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

# architecture directory
ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config # include arch env-vars (arch objs list, etc..)

# set compiler flags
CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

# freestanding objects - meant for kernel programming
FREEOBJS=\
$(ARCH_FREEOBJS) \
libc/stdio/putchar.o \
libc/stdio/printf.o \
libc/stdio/getc.o \
libc/stdio/gets.o \
libc/stdio/geti.o \
libc/stdlib/abort.o \
libc/stdlib/atoi.o \
libc/stdlib/malloc.o \
libc/stdlib/calloc.o \
libc/stdlib/free.o \
libc/string/strlen.o \
libc/string/strcpy.o \
libc/string/memset.o \
libc/string/strncpy.o \
libc/string/strcmp.o \
libc/string/memcpy.o \
libc/wrappers/fmt/fmt.o \
# insert here freestanding objects (kernel libc objects)

# hosted objects - standard library enabled with user-space
HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

# combine all of the objects
OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

######
# libk - copy of libc, but meant only for kernel programming
# in other words - freestanding objects only.
# That means, when there will be user-mode, TODO: replace standard library to libc, withing syscalls and more
######
LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

# BINARIES=libc.a libk.a # Will be ready when user-mode will be implemented
BINARIES=libk.a # desired binary

.PHONY: all clean build install-headers install-libs # declare all of the targets
.SUFFIXES: .o .libk.o .cpp .s # declare all of the suffixes

# depend on $(BINARIES) objects, if doesn't exist - run the desired targets
all: $(BINARIES)

# will be in use when there will be user-mode
libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

# desired libk.a binary archive - depends on the $(LIBK_OBJS), if doesn't exist - run the desired rules
libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

# rule for .c file - output should be .o file
.cpp.o:
		$(CC) -MD -c $< -o $@ -std=gnu++20 $(CFLAGS) $(CPPFLAGS)

# rule for .s file - output should be .o file
.s.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

# rule for .cpp file - output shuld be .libk.o file
.cpp.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu++20 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

# rule for .s file - output should be .libk.o file
.s.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

# depend on install-headers and install-libs targets, in-other-words: run those targets
build: install-headers install-libs

# cleans output files (objects, dependency, etc)
clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

# copy the headers into the fake sysroot include directory
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

# copy the archive binary into the fake sysroot boot directory
# this meant for the compiler can know from where to link the library (i686-elf-ld -lk --verbose in the fake sysroot)
install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
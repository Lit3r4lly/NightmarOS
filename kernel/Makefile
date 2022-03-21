# Kernel sub-proj Makefile

PROJECT_NAME="NightmareOS"# set project name
DEFAULT_HOST!=../scripts/default-host.sh # set default host
HOST?=DEFAULT_HOST # set current host for the build
HOSTARCH!=../scripts/target-triplet-to-arch.sh $(HOST) # set arch name by the host name

DESTDIR?= # passed as argument when calling "make <X>" as "DESTDIR='<Y>' make <X>"
PREFIX?=/usr/local # prefix for user directory usgae
EXEC_PREFIX?=$(PREFIX) # execution prefix
BOOTDIR?=$(EXEC_PREFIX)/boot # boot directory
INCLUDEDIR?=$(PREFIX)/include # include directory
INCLUDE_DIR=include/ # include directory for headers, used by the compiler

# set default flags for the compiler
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -fno-rtti -fno-exceptions # disable some standard features
CPPFLAGS:=$(CPPFLAGS) -D_K_LOG -D__is_kernel -I$(INCLUDE_DIR) # I$(INCLUDE_DIR) - include the BASE_DIR/kernel/include/ dir as global lib
LDFLAGS:=$(LDFLAGS)											  # -D_K_LOG - define for create log file
LIBS:=$(LIBS) -nostdlib -lk -lgcc # lk - lib{lib_name}.a - libk.a - include from fake sysroot

# architecture directory
ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config # include arch env-vars (arch objs list, etc..)

# set compiler flags
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

# initialization objs
INIT_OBJS=\
$(ARCHDIR)/boot/boot.o \
$(ARCHDIR)/boot/crti.o \
$(ARCHDIR)/boot/crtbegin.o \

# finish objs
FINI_OBJS=\
$(ARCHDIR)/boot/crtend.o \
$(ARCHDIR)/boot/crtn.o \

# kernel objects list
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \
kernel/ports/ports.o \
kernel/logs/logs.o \
kernel/panic/panic.o \
kernel/keyboard/keyboard.o \
kernel/keyboard/ps2/ps2_keyboard.o \
kernel/cpp_support.o \
#  ---- insert here all kernel objects ----

# all of the objects for the build
OBJS=\
$(INIT_OBJS) \
$(KERNEL_OBJS) \
$(FINI_OBJS)

# linkage list used by the compiler
LINK_LIST=\
$(INIT_OBJS) \
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \
$(FINI_OBJS) \

.PHONY: all build clean install-headers install-kernel # declare all of the targets
.SUFFIXES: .o .cpp .s # declare all of the suffixes

# depend on $(PROJECT_NAME).kernel binary, if doesn't exist - run the desired target
all: $(PROJECT_NAME).kernel

# creates $(PROJECT_NAME).kernel file - depends on objs list and linker.ld file
$(PROJECT_NAME).kernel: $(OBJS) $(ARCHDIR)/boot/linker.ld
	$(CC) -T $(ARCHDIR)/boot/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	../scripts/is-multiboot.sh $(PROJECT_NAME).kernel

# create crt*.o object files used for enabling global constructors
$(ARCHDIR)/boot/crtbegin.o $(ARCHDIR)/boot/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

# rule for .cpp file - output should be .o file
.cpp.o:
	$(CC) -MD -c $< -o $@ -std=gnu++20 $(CFLAGS) $(CPPFLAGS)

# rule for .s file - output should be .o file
.s.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

# depend on install-headers and install-kernel targets, in-other-words: run those targets
build: install-headers install-kernel

# cleans output files (objects, dependency, etc)
clean:
	rm -f $(PROJECT_NAME).kernel
	rm -f $(OBJS) .o */.o //*.o
	rm -f $(OBJS:.o=.d) .d */.d //*.d

# copy the headers into the fake sysroot include directory
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

# copy the binary into the fake sysroot boot directory
install-kernel: $(PROJECT_NAME).kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(PROJECT_NAME).kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)

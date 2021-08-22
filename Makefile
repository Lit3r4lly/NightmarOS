# *Base directory Makefile*

build: # build the sub-projects (libc, kernel), output should be binary file for the kernel and .a for the libc
	./scripts/build.sh

clean: # Clean all output files (objects, iso, binaries...)
	./scripts/clean.sh

iso: # make iso file
	./scripts/iso.sh

run: # run the iso file with qemu
	./scripts/run.sh

debug: # debug the os using gdb
	./scripts/debug.sh
# NightmareOS

## About

NightmareOS is an operating system mainly designed as i386 Intel's architecture, which contains some sort of features
that you could find in many operating systems.  

For now this project is mainly introduced as study, research and hobby project which we as a final-year project in Magshimim.

## Kernel features

- i386 architectur (32-bit)
- Memory management (GDT, Paging, Heap allocator)
- Interrupts (IDT, PIC)
- PIT
- ext2 filesystem
- QEMU keyboard integration
- Etc...

## Libraries
- Libc
- libstdc++

## Userland features
- May god will be with us and we will get this far

## How do I read the documentation?
The documentation files availble at the ``documentation/`` directory

## How do I build and run this?
You can build NightmareOS after you have the cross-compiler which build with ``scripts/build-gcc.sh``  
After that you can simply use `make build` in the root project directory

To run NightmareOS you need to use `make run`  
To clean the output files you need to use `make clean`
To create iso file you need to use `make iso`  
To debug the OS using GDB you need to use `make debug`

(The make targets using `.sh` scripts built as inherited scripts - if you use `make run`, it will build, create iso and run the OS)

## Author
- **Ori Feldman** - [Github](https://github.com/Lit3r4lly)
- **Oshri Taub** - [Github](https://github.com/oshri22)
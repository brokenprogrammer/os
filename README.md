# os

Next generation operating system

## Setup

The main development environment used for this project is going to be Windows.
A normal Windows compiler cannot be used since it will compile into an executable
made to be run on the Windows platform. Hence a set of tools are needed before 
the initial development of this system.

* MinGW - Contains tools required for OS Development, such as GCC and binutils. For me I have mingw32-base, mingw32-gcc-g++ & mysys-base which is a part of the "Basic Setup". MinGW is also needed for GCC to function properly.
* i686-elf targeting GCC - Cross Compiler to target x86 instead of a specific platform such as Windows or Linux.
* QEMU - Emulator able to boot the resulting .bin file without us needing to convert it to a bootable ISO file.

_For the setup to work, the executables for the above three tools needs to be in your system path_

## Links

[Download for i686-elf](https://github.com/lordmilko/i686-elf-tools)

[Why do I need a Cross Compiler?](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler)

[OS Dev](https://wiki.osdev.org/Main_Page)

[System V ABI (Specification for calling conventions, obj file formats, exe formats etc..)](https://wiki.osdev.org/System_V_ABI)

[Interrupt Descriptor Table (IDT)](https://wiki.osdev.org/Interrupt_Descriptor_Table)

[Interrupt Service Routines (ISR)](https://wiki.osdev.org/Interrupt_Service_Routines)


## Coding conventions

This project uses a so-called "unity build" which aims to include all (most) of the source code in one (or a few) compilation unit(s). The reasoning behind this is to simplify the file structure and reduce build times, since it means the compiler has to do less compilation and linking. 

This has some implications though, that you as a contributor need to understand and follow.

1. declare types in header files
1. declare functions in source files 
1. include source files in - and only in - `kernel.c`, which is the entry point of the OS
    - source files that are added in `kernel.c` will be available in all source files of the same compilation unit

### Questions:

* When to use `static` / `internal`
* How to handle circular dependencies / forward declarations?
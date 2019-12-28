# os
Next generation operating system

# Setup
The main development environment used for this project is going to be Linux for now.
A normal C/C++ compiler cannot be used since it will compile into an executable
made to be run on the platform you're compiling on. Hence a a cross compiler together with a set of tools are needed before 
starting development of this system.

* Binutils - Collection of binary utility tools such as the gcc linker and the gcc assembler.
* Nasm - The Netwide Assembler, an 80x86 and x86-64 assembler (Imo better than GAS).
* i686-elf targeting GCC - Cross Compiler to target x86 instead of a specific platform such as Windows or Linux.
* QEMU - Emulator able to boot the resulting .bin file without us needing to convert it to a bootable ISO file.

For now to setup a development environment you are required to
download and build both binutils and gcc on your linux installation.
A guide on how to do that can be found [here.](https://wiki.osdev.org/GCC_Cross-Compiler)

## Create empty raw file before running build script
```bash
dd if=/dev/zero of=drive bs=512 count=<...>
```

# Links
[Download for i686-elf](https://github.com/lordmilko/i686-elf-tools)

[Why do I need a Cross Compiler?](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler)

[OS Dev](https://wiki.osdev.org/Main_Page)

[System V ABI (Specification for calling conventions, obj file formats, exe formats etc..)](https://wiki.osdev.org/System_V_ABI)

[Interrupt Descriptor Table (IDT)](https://wiki.osdev.org/Interrupt_Descriptor_Table)

[Interrupt Service Routines (ISR)](https://wiki.osdev.org/Interrupt_Service_Routines)
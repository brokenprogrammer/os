# os
Next generation operating system

# Setup
The main development environment used for this project is going to be Windows.
A normal Windows compiler cannot be used since it will compile into an executable
made to be run on the Windows platform. Hence a set of tools are needed before 
the initial development of this system.

* MinGW - Contains tools required for OS Development, such as GCC and binutils. For me I have mingw32-base, mingw32-gcc-g++ & mysys-base which is a part of the "Basic Setup". MinGW is also needed for GCC to function properly.
* i686-elf targeting GCC - Cross Compiler to target x86 instead of a specific platform such as Windows or Linux.
* QEMU - Emulator able to boot the resulting .bin file without us needing to convert it to a bootable ISO file.

# Links
[Download for i686-elf](https://github.com/lordmilko/i686-elf-tools)

[Why do I need a Cross Compiler?](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler)

[OS Dev](https://wiki.osdev.org/Main_Page)

[System V ABI (Specification for calling conventions, obj file formats, exe formats etc..)](https://wiki.osdev.org/System_V_ABI)

[Interrupt Descriptor Table (IDT)](https://wiki.osdev.org/Interrupt_Descriptor_Table)

[Interrupt Service Routines (ISR)](https://wiki.osdev.org/Interrupt_Service_Routines)
@echo off

SET "minGW=C:\MinGW\bin"
SET "gcc=D:\i686-elf\bin"
SET "qemu=D:\Program Files (x86)\qemu"

SET "PATH=%minGW%;%gcc%;%qemu%;%PATH%"

IF NOT EXIST /build mkdir build

i686-elf-as kernel/boot.s -o build/boot.o
i686-elf-as kernel/interrupt.s -o build/interrupt.o
i686-elf-gcc -c kernel/gdt.c -o build/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


pushd build
i686-elf-gcc -T ../linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o interrupt.o gdt.o kernel.o -lgcc
popd

qemu-system-i386 -kernel build/os.bin

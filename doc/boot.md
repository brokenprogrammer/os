# Boot Documentation

This document will contain information gathered regarding the operating system
bootloader. The idea behind it is for knowledge collected during development
to be formatted in a way which explains why the operating system is built
the way it is and how those parts work together.

## Bootloader
The ultimate goal for a bootloader is to load the kernel itself into memory
together with all the things the kernel needs to work correctly such as 
a propperly prepared environment and information regarding the system it is
run on. When this is done the bootloader will transfer controll to the kernel
itself.

### Bringing the kernel into memory
The kernel itself is a binary application located somewhere on disk. The question
is where on the disk? It can be a FAT-formatted floppy drive, a CD, USB drive
or simply pasted on to a partitioned hard-drive. All of the mentioned are
possibilities.

For just developing a kernel you can compile the entire thing into a binary file
bootloader together with the kernel and run it inside an emulator such as Qemu
with the `-kernel` flag but this is not how real computers work hence we will
avoid that.

Talking about the hard-drive option we can assume this is a MBR-partitioned hard
disk (We will talk more about MBR later) the BIOS loads and executes the Master
Boot Record (MBR), which is responsible for loading and executing the 
Volume Boot Record (VBR) for the active partition. The VBR then does some initial
checks before loading the stage 2 from the file system.

Taking a step back and looking at the MBR which is a bootsector for a hard disk.
What this means is that it is simply what BIOS loads then executes when it boots
the hard disk. It is the very first sector of the hard disk and contains a small
application called "MBR bootstrap" together with a partition table.

In our case currently the MBR simply reallocates itself away from address `0x7c00`
to address `0x0600`(Typical convention) and then scans through each of the partitions
of the drive to find a partition which has a bootable flag set to it (0x80).
Once it is found it loads the first section of that partition containing our
stage 1 bootloader.

### 2-Stage bootloader
A two-stage bootloader consists of two bootloaders after one another. The first
bootloader (stage 1) being small with its only purpose being to load the 2nd one.
The second bootloader (stage 2) can then contain all the code needed to prepare
and load the kernel itself. This is a way to get around the 512 byte limit on the
x86 for bootloaders. 

### Stage 1
As mentioned above the first bootloader only has one goal in mind which is to
find and load the 2nd bootloader. This can be a bit tricky since we need to
find the bootloader on our hard-disk. For this to work the hard-disk has to have
a filesystem which we can parse in order to navigate around it and find our files.
FAT is a simple enough file system to write code for but like most filesystems
it doesn't reserve much space for our stage 1 bootloader (Only one sector).
Ext2 is a little bit better in this regard reserving another sector right after
the VBR but requires a little bit more parsing. We will go for Ext2 for now.

### Stage 2
The second bootloader as mentioned above requires a little bit more work since 
it is not only loading files but preparing a complete environment for our kernel.
Here is a list of things which the stage 2 bootloader has to do:
* Check for PCI support
* Enable Video mode
* Check the upper & lower memory
* Enable the A20 flag
* Enter protected mode.
* Enable paging
* Load the GDT
* Load the kernel from disk into memory
* Read ELF headers
* Transfer execution to the kernel

I will go over each and one of theese as they are implemented by adding a section to this document describing its purpose and how to implement it.

## PCI


## Video Mode
## Upper & Lower Memory
## A20
## Protected Mode
## Paging
## GDT
## Loading a Kernel
## ELF headers

# References
[Bootloader](https://wiki.osdev.org/Bootloader)

[Rolling your own bootloader](https://wiki.osdev.org/Rolling_Your_Own_Bootloader)

[Bootloader FAQ](https://wiki.osdev.org/Bootloader_FAQ)

[MBR](https://wiki.osdev.org/MBR_(x86))

[FAT](https://wiki.osdev.org/FAT)

[Ext2](https://wiki.osdev.org/Ext2)

[Protected Mode](https://wiki.osdev.org/Protected_mode)


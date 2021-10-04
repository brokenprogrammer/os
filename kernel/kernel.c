#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../libc/itoa.c"
#include "../libc/memset.c"
#include "../libc/strlen.c"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

typedef float				r32;
typedef double				r64;
typedef unsigned char 		ubyte;
typedef unsigned int 		uint;
typedef int8_t 				s8;
typedef uint8_t 			u8;
typedef int16_t 			s16;
typedef uint16_t 			u16;
typedef int32_t 			s32;
typedef uint32_t 			u32;
typedef int64_t 			s64;
typedef uint64_t 			u64;
typedef s32 				b32;

#define internal 		static
#define local_persist 	static
#define global_variable static

#include "idt.c"
#include "terminal.c"
#include "interrupt.c"

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	
	idt_initialize();

	terminal_writestring("Welcome to Developer OS.\n");

	terminal_writestring("\n\n");

	terminal_writestring("This output is testing so that the terminal escape");
	terminal_writestring("This\nshould\nhandle\nthe\nnewline\ncharacter.\n");
  
	terminal_writestring("Tabbing\t like\t crazy.\t PS.\t switch\t is\t the\t best\t control\t flow\t operator\t in\t the\t C\t language\t.\n");

	terminal_writestring("A\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
	
	terminal_writestring("\n\n");

	terminal_writestring("This is an extra super long line and it should automatically break to a new row when it hits the end of the terminal row. If it doesn't, something is wrong! Since we're using the \"break row on word\" setting, these sentences shouldn't be broken in the middle of a word, but rather before / after a whole word. As a matter of fact, I can write a whole essay here, and it will still work as expected! Isn't that just awesome!\n\nI can aslo jump down a few lines. Look how this word does not get broken up: Omphaloskepsis");

	terminal_writestring("\n\n");

	terminal_writestring("Here is a number: ");

	terminal_writenumber(11230);

	terminal_writestring("\n\n");

	terminal_writestring("This works when seperated into another file as well! Yay. unity build!");

	terminal_writestring("\n\n");

	terminal_setcolor(VGA_COLOR_CYAN);

	terminal_writestring("Here is a message in the color cyan.");

	terminal_writestring("\n\n");

	terminal_setcolor(VGA_COLOR_LIGHT_GREY);

	asm volatile ("int $0x3"); // NOTE(Oskar): Triggers an ISR interrupt.
}
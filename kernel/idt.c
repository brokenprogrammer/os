#include "idt.h"

struct idt_entry idt[256];

// NOTE(Oskar): Using the LIDT assembly instruction to load the IDT.
void lidt(uintptr_t Base, size_t Limit)
{
    asm volatile ("subl $6, %%esp\n\t"
                "movw %w0, 0(%%esp)\n\t"
                "movl %1, 2(%%esp)\n\t"
                "lidt (%%esp)\n\t"
                "addl $6, %%esp" : : "rN"(Limit), "r"(Base));
}

// NOTE(Oskar): Initializes an entry from the global IDT array by
//              assigning it a type, and a handler.
internal void idt_format_normal_entry(struct idt_entry* Entry, void (*Handler)(void), u8 Type, u8 RPL)
{
    Entry->HandlerLow = (uintptr_t) Handler >> 0 & 0xFFFF;
    Entry->Selector = 0x08 /* Kernel Code Segment */;
    Entry->IST = 0;
    Entry->Flags = IDT_FLAG_PRESENT |
                   RPL << IDT_FLAG_DPL_SHIFT |
                   Type << IDT_FLAG_TYPE_SHIFT;
    Entry->HandlerHigh = (uintptr_t) Handler >> 16 & 0xFFFF;
}

internal void idt_initialize()
{
    memset(&idt, 0, sizeof(idt));

    idt_format_normal_entry(&idt[0], isr0, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[1], isr1, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[2], isr2, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[3], isr3, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[4], isr4, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[5], isr5, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[6], isr6, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[7], isr7, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[8], isr8, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[9], isr9, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[10], isr10, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[11], isr11, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[12], isr12, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[13], isr13, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[14], isr14, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[15], isr15, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[16], isr16, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[17], isr17, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[18], isr18, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[19], isr19, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[20], isr20, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[21], isr21, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[22], isr22, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[23], isr23, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[24], isr24, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[25], isr25, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[26], isr26, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[27], isr27, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[28], isr28, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[29], isr29, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[30], isr30, IDT_TYPE_INTERRUPT, 0x0);
    idt_format_normal_entry(&idt[31], isr31, IDT_TYPE_INTERRUPT, 0x0);	

    // TODO(Oskar): Support for IRQ's as well.

    lidt((uintptr_t) idt, sizeof(idt) - 1);
} 
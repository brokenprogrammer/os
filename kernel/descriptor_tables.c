#include "descriptor_tables.h"

extern void global_descriptor_table_flush(u32); // NOTE(Oskar): Defined in descriptor_tables.s
extern void interrupt_descriptor_table_flush(u32);

global_descriptor_table_entry GDTEntries[5];
global_descriptor_table_pointer GDTPointer;
idt_entry IDTEntries[256];
idt_ptr IDTPointer;

internal void gdt_set_gate(s32 Num, u32 Base, u32 Limit, u8 Access, u8 Gran)
{
    GDTEntries[Num].BaseLow    = (Base & 0xFFFF);
    GDTEntries[Num].BaseMiddle = (Base >> 16) & 0xFF;
    GDTEntries[Num].BaseHigh   = (Base >> 24) & 0xFF;

    GDTEntries[Num].LimitLow   = (Limit & 0xFFFF);
    GDTEntries[Num].Granularity = (Limit >> 16) & 0x0F;
    
    GDTEntries[Num].Granularity |= Gran & 0xF0;
    GDTEntries[Num].Access      = Access;
}

internal void idt_set_gate(u8 Num, u32 Base, u16 Sel, u8 Flags)
{
    IDTEntries[Num].BaseLow = Base & 0xFFFF;
    IDTEntries[Num].BaseHigh = (Base >> 16) & 0xFFFF;
    IDTEntries[Num].Sel     = Sel;
    IDTEntries[Num].Always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    IDTEntries[Num].Flags   = Flags /* | 0x60 */;
}

internal void initialize_gdt()
{
    GDTPointer.Limit = (sizeof(global_descriptor_table_entry) * 5) - 1;
    GDTPointer.Base = (u32)&GDTEntries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    global_descriptor_table_flush((u32)&GDTPointer);
}

internal void initialize_idt()
{
    IDTPointer.Limit = sizeof(idt_entry) * 256 -1;
    IDTPointer.Base  = (u32)&IDTEntries;

    memset(&IDTEntries, 0, sizeof(idt_entry)*256);

    idt_set_gate( 0, (u32)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (u32)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (u32)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (u32)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (u32)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (u32)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (u32)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (u32)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (u32)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (u32)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (u32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32)isr31, 0x08, 0x8E);

    interrupt_descriptor_table_flush((u32)&IDTPointer);
}
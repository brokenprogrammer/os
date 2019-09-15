#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

struct global_descriptor_table_entry_t
{
    u16 LimitLow;
    u16 BaseLow;
    u8 BaseMiddle;
    
    // NOTE(Oskar): Access flags, determine what ring this segment
    //              can be used in.
    //              Uses following format:
    //              7 | 6  5 | 4 | 3   0|
    //              P |  DPL | DT| TYPE |
    u8 Access;

    u8 Granularity;
    u8 BaseHigh;
} __attribute__((packed));
typedef struct global_descriptor_table_entry_t global_descriptor_table_entry;

struct global_descriptor_table_pointer_t
{
    u16 Limit;
    u32 Base;
} __attribute__((packed));
typedef struct global_descriptor_table_pointer_t global_descriptor_table_pointer;


struct idt_entry_t
{
    u16 BaseLow;             // The lower 16 bits of the address to jump to when this interrupt fires.
    u16 Sel;                 // Kernel segment selector.
    u8  Always0;             // This must always be zero.
    u8  Flags;               // More flags. See documentation.
    u16 BaseHigh;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_t idt_entry;

struct idt_ptr_t
{
    u16 Limit;
    u32 Base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_t idt_ptr;

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif // DESCRIPTOR_TABLES_H
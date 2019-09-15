#ifndef IDT_H
#define IDT_H

// NOTE(Oskar): Helper defines for IDT types.
#define IDT_TYPE_INTERRUPT 0xE
#define IDT_TYPE_TRAP 0xF

// NOTE(Oskar): IDT Flags helpers.
#define IDT_FLAG_PRESENT (1 << 7)
#define IDT_FLAG_DPL_SHIFT 5
#define IDT_FLAG_DPL_BITS 2
#define IDT_FLAG_TYPE_SHIFT 0
#define IDT_FLAG_TYPE_BITS 4

struct idt_entry
{
    u16 HandlerLow;     // NOTE(Oskar): Lower 16 bits of the handler to jump to when this interrupt is triggered.
    u16 Selector;       // NOTE(Oskar): Kernel segment selector.
    u8 IST;             // NOTE(Oskar): Must be zero.
    u8 Flags;           // NOTE(Oskar): Flags. TODO(Oskar): Add more info?
    u16 HandlerHigh;    // NOTE(Oskar): Upper 16 bits of the handler to jump to.
};

// NOTE(Oskar): Theese functions are defined in interrupt.s
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

#endif // IDT_H
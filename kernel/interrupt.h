#ifndef INTERRUPT_H
#define INTERRUPT_H

struct interrupt_context
{
    u32 cr2;
    u32 gs;
    u32 fs;
    u32 ds;
    u32 es;
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u32 int_no;
    u32 err_code;
    u32 cs;
    u32 eflags;
    u32 esp; /* If (cs & 0x3) != 0 */
    u32 ss;  /* If (cs & 0x3) != 0 */
};

#endif // INTERRUPT_H
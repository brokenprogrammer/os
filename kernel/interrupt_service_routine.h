#ifndef INTERRUPT_SERVICE_ROUTINE_H
#define INTERRUPT_SERVICE_ROUTINE_H

typedef struct registers
{
    u32 ds;                  // Data segment selector
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    u32 int_no, err_code;    // Interrupt number and error code (if applicable)
    u32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

#endif // INTERRUPT_SERVICE_ROUTINE_H
#include "interrupt.h"

void interrupt_handler(struct interrupt_context *Context)
{
    terminal_writestring("Interrupt occured.\n");
    if (Context->int_no < 32)
    {
        terminal_writestring("ISR Interrupt.\n");
    }

    // add check for IRQs (will not need to be added to interrupt_context)
}
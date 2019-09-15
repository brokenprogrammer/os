#include "interrupt_service_routine.h"

void isr_handler(registers_t regs)
{
    // TODO(Oskar): Output interrupt number.
    terminal_writestring("Interrupt occured.");
    asm volatile("cli");
}
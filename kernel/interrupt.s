# Macros to help define isr two types of ISR functions.
# One that pushes an error code and one who does not.

.macro isr id
    .global isr\id
    .type isr\id, @function
    isr\id:
        pushl $0
        pushl $\id
        jmp interrupt_handler_prepare
    .size isr\id, . - isr\id
.endm

.macro isr_error id index
    .global isr\id
    .type isr\id, @function
    isr\id:
        # pushl $0
        pushl $\id
        jmp interrupt_handler_prepare
    .size isr\id, . - isr\id
.endm

isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr_error 8
isr 9
isr_error 10
isr_error 11
isr_error 12
isr_error 13
isr_error 14
isr 15
isr 16
isr 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31
isr 32

.extern interrupt_handler

.type interrupt_handler_prepare, @function
interrupt_handler_prepare:
    pushl %eax
    pushl %ecx
    pushl %edx
    pushl %ebx
    pushl %ebp
    pushl %esi
    pushl %edi

    movl %ds, %ebp
    pushl %ebp
    movl %es, %ebp
    pushl %ebp
    movl %fs, %ebp
    pushl %ebp
    movl %gs, %ebp
    pushl %ebp

    movl $0x10 /* Kernel Data Segment */, %ebp
    movl %ebp, %ds
    movl %ebp, %es
    movl %ebp, %fs
    movl %ebp, %gs

    movl %cr2, %ebp
    pushl %ebp

    movl %esp, %ebx
    subl $4, %esp
    andl $0xFFFFFFF0, %esp /* 16-byte align stack */
    movl %ebx, (%esp)
    call interrupt_handler
    movl %ebx, %esp

    popl %ebp
    movl %ebp, %cr2

    popl %ebp
    movl %ebp, %gs
    popl %ebp
    movl %ebp, %fs
    popl %ebp
    movl %ebp, %es
    popl %ebp
    movl %ebp, %ds

    popl %edi
    popl %esi
    popl %ebp
    popl %ebx
    popl %edx
    popl %ecx
    popl %eax

    addl $8, %esp
    iret
.size interrupt_handler_prepare, . - interrupt_handler_prepare

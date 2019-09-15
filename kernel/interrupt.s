.intel_syntax
.macro ISR_NOERRCODE p
    .globl isr\p
    isr\p:
    cli
    push 0
    push \p
    jmp isr_common_stub
.endm

.macro ISR_ERRCODE p
    .globl isr\p
    isr\p:
        cli
        push \p
        jmp isr_common_stub
.endm

ISR_NOERRCODE p=0
ISR_NOERRCODE p=1
ISR_NOERRCODE p=2
ISR_NOERRCODE p=3
ISR_NOERRCODE p=4
ISR_NOERRCODE p=5
ISR_NOERRCODE p=6
ISR_NOERRCODE p=7
ISR_ERRCODE   p=8
ISR_NOERRCODE p=9
ISR_ERRCODE   p=10
ISR_ERRCODE   p=11
ISR_ERRCODE   p=12
ISR_ERRCODE   p=13
ISR_ERRCODE   p=14
ISR_NOERRCODE p=15
ISR_NOERRCODE p=16
ISR_NOERRCODE p=17
ISR_NOERRCODE p=18
ISR_NOERRCODE p=19
ISR_NOERRCODE p=20
ISR_NOERRCODE p=21
ISR_NOERRCODE p=22
ISR_NOERRCODE p=23
ISR_NOERRCODE p=24
ISR_NOERRCODE p=25
ISR_NOERRCODE p=26
ISR_NOERRCODE p=27
ISR_NOERRCODE p=28
ISR_NOERRCODE p=29
ISR_NOERRCODE p=30
ISR_NOERRCODE p=31

.extern isr_handler

isr_common_stub:
    pusha

    mov %ax, %ds
    push %eax

    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax

    call isr_handler

    pop %ebx
    mov %ds, %bx
    mov %es, %bx
    mov %fs, %bx
    mov %gs, %bx

    popa
    add %esp, 8
    sti
    iret

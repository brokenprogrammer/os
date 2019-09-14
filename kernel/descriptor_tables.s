.intel_syntax
.globl global_descriptor_table_flush
.globl interrupt_descriptor_table_flush

global_descriptor_table_flush:
    mov %eax, [%esp+4]
    lgdt [%eax]

    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    jmp 0x08:.flush
.flush:
    ret

interrupt_descriptor_table_flush:
    mov %eax, [%esp+4]
    lidt [%eax]
    ret

[bits 16]
[org 0x1000]

jmp start

Print:
			lodsb		; load next byte from string from SI to AL
			or	al, al	; Does AL=0?
			jz	PrintDone	; Yep, null terminator found-bail out
			mov	ah,	0eh	; Nope-Print the character
			int	10h
			jmp	Print	; Repeat until null terminator found
PrintDone:
			ret		; we are done, so return

start:
    mov si, msg
    call Print

    cmp dword [page_table_allocation_location], 0x2000
    je .set_stack

    .set_stack:
    mov esp,0x7C00

    ; Save Stage 1 boot information
    mov [drive_number],dl
    mov [partition_entry],si

; TODO(Oskar): PCI
; TODO(Oskar): Video Mode
; TODO(Oskar): Upper & Lower Memory
; TODO(Oskar): A20
; TODO(Oskar): Protected mode
; TODO(Oskar): Paging
; TODO(Oskar): GDT
; TODO(Oskar): Load Kernel


    cli
    hlt

drive_number: db 0
partition_entry: dw 0

page_table_allocation_location: dq 0x2000

msg:	db	"Starting stage 2 boot...",13,10,0

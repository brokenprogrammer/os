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

check_pci:
    ; Check if the computer has PCI available. "int 0x1A, AX=0xB101 (PCI BIOS presence check)"
    mov ax,0xB101
    xor	edi,edi ; NOTE(Oskar): Zero out EDI according to: http://www.ctyme.com/intr/rb-2371.htm
    int	0x1A
    mov	si,error_no_pci
    jc error
    or ah,ah
    jnz error

; TODO(Oskar): Video Mode
; TODO(Oskar): Upper & Lower Memory
; TODO(Oskar): A20
; TODO(Oskar): Protected mode
; TODO(Oskar): Paging
; TODO(Oskar): GDT
; TODO(Oskar): Load Kernel
    cli
    hlt

error:
	; Print an error message
	lodsb
	or	al,al
	jz	.break
	mov	ah,0xE
	int	0x10
	jmp	error

	; Break indefinitely
	.break:
	cli
	hlt

drive_number: db 0
partition_entry: dw 0

page_table_allocation_location: dq 0x2000

error_no_pci: db "Error: Could not find the PCI bus",0
msg:	db	"Starting stage 2 boot...",13,10,0

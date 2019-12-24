[bits 16]
[org 0x7C00]

%define superblock 0x8000
%define temporary_load_buffer 0x9000
%define block_group_descriptor_table 0x10000
%define directory_load_location 0x1000
%define stage2_load_location 0x1000
%define inode_table_load_buffer 0x20000
;%define magic_breakpoint xchg bx,bx
%define magic_breakpoint

start:
	; Setup segment registers
	cli
	mov	ax,0
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	mov	ss,ax
	mov	sp,0x7C00
	jmp	0x0:.continue
	.continue:
	sti

	; TODO(Oskar): Once MBR is implemented, Save MBR information
	; mov 	[drive_number],dl
	; mov 	[partition_entry],si

	; Print startup message
	mov	si,startup_message
	.loop:
	lodsb
	or	al,al
	jz	.end
	mov	ah,0xE
	int 0x10
	jmp .loop
	.end:
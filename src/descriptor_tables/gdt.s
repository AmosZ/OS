[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]
; Start to set ds,es,fs,gs,ss index into gdt
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
;Long jmp. Change cs and jmp
	jmp 0x08:.flush
.flush:
	ret


[GLOBAL idt_flush]
idt_flush:
	mov eax,[esp+4]
	lidt [eax]
	ret

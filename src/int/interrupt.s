[EXTERN isr_handler]
[GLOBAL isr_common_stub]
isr_common_stub:
	pusha		;push edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax,ds	;
	push eax
	
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	call isr_handler

	pop eax
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	popa
	add esp,8 ;cleans up the pushed error code and pushed ISR number
	sti
	iret	  ;pops 5 things at onces: CS,EIP(code segment),EFLAGS(CPU status),SS,ESP(stack segment)

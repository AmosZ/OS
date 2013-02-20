[GLOBAL isr0]
isr0:
	cli
	push byte 0
	push byte 0
	jmp isr_common_stub

/*
 *  linux/kernel/asm.s
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 * asm.s contains the low-level code for most hardware faults.
 * page_exception is handled by the mm, so that isn't here. This
 * file also handles (hopefully) fpu-exceptions due to TS-bit, as
 * the fpu must be properly saved/resored. This hasn't been tested.
 */

.globl divide_error,debug,nmi,int3,overflow,bounds,invalid_op
.globl double_fault,coprocessor_segment_overrun
.globl invalid_TSS,segment_not_present,stack_segment
.globl general_protection,coprocessor_error,irq13,reserved
/*
   This code describe what kernel does before calling ISA.
    _________________
   |		| old SS |<----- Priority Changes(From user to kernel )   
   |	 old ESP	 |<-----   
   |	 EFLAGS		 |
   |		| old CS |
   |	   EIP		 |
   |	 (Error)	 |
   .		.		 .
   .		.		 .
   .		.		 .
   At least 12bytes have been pushed by hardware automatically.
*/



divide_error:
	pushl $do_divide_error # Why we should pushl ISA address ?
						   # ISA address is an argument of ISA.
						   # (To print the address of error code)
no_error_code:
/*
   Here we backup all general registers and segment registers
*/
	xchgl %eax,(%esp)	# This is a convinent way to store $ISA in eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	pushl %edi
	pushl %esi
	pushl %ebp
	push %ds
	push %es
	push %fs			# No cs,ss? original ss,esp,eflags,cs,and eip have beeb										 pushed by CPU

	pushl $0			# "error code", argument2
	lea 44(%esp),%edx	# edx = esp0(esp when execute this code)
	pushl %edx			# Push interrupt return address
						# Yes, return address should be placed at the top of stack!
/*
   We set segment registers as 0x10
*/
	movl $0x10,%edx		# 0x10 is selector in GDT? Yes ,0x10 selector coorespond to data
						# segment. What is the value of CS? CS = 0x08?
	mov %dx,%ds
	mov %dx,%es
	mov %dx,%fs
	call *%eax			# What call instructor do ?
						/* 
						    For example , do_divide_error(long esp,long error_code)
							eax is the first argument. but error_code is located at esp-8.
							What is the call routine?
						*/
	addl $8,%esp
	pop %fs
	pop %es
	pop %ds
	popl %ebp
	popl %esi
	popl %edi
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	iret

debug:
	pushl $do_int3		# _do_debug
	jmp no_error_code

nmi:
	pushl $do_nmi
	jmp no_error_code

int3:
	pushl $do_int3
	jmp no_error_code

overflow:
	pushl $do_overflow
	jmp no_error_code

bounds:
	pushl $do_bounds
	jmp no_error_code

invalid_op:
	pushl $do_invalid_op
	jmp no_error_code

coprocessor_segment_overrun:
	pushl $do_coprocessor_segment_overrun
	jmp no_error_code

reserved:
	pushl $do_reserved
	jmp no_error_code

irq13:
	pushl %eax
	xorb %al,%al
	outb %al,$0xF0
	movb $0x20,%al
	outb %al,$0x20
	jmp 1f
1:	jmp 1f
1:	outb %al,$0xA0
	popl %eax
	jmp coprocessor_error

double_fault:
	pushl $do_double_fault
error_code:
	xchgl %eax,4(%esp)		# error code <-> %eax
	xchgl %ebx,(%esp)		# &function <-> %ebx
	pushl %ecx
	pushl %edx
	pushl %edi
	pushl %esi
	pushl %ebp
	push %ds
	push %es
	push %fs
	pushl %eax			# error code
	lea 44(%esp),%eax		# offset
	pushl %eax
	movl $0x10,%eax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%fs
	call *%ebx
	addl $8,%esp
	pop %fs
	pop %es
	pop %ds
	popl %ebp
	popl %esi
	popl %edi
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	iret

invalid_TSS:
	pushl $do_invalid_TSS
	jmp error_code

segment_not_present:
	pushl $do_segment_not_present
	jmp error_code

stack_segment:
	pushl $do_stack_segment
	jmp error_code

general_protection:
	pushl $do_general_protection
	jmp error_code


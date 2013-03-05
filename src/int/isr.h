#ifndef ISR_H
#define ISR_H
#include "common.h"
//Struct members are stored in the order they are declared. (This is required by the C99 standard)
typedef struct registers
{
	uint32 ds;//last push,lowest address
	uint32 edi,esi,ebp,esp,ebx,edx,ecx,eax;
	uint32 intNum,errorCode;
	uint32 eip,cs,eflags,useresp,ss;//first push,highest address
}registers_t;//32bits,no need for packed attribute



extern void isr_handler(registers_t regs);
extern void isr0();
//....interface service routine??
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif

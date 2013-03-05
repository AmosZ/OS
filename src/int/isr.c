#include "isr.h"
#include "common.h"
/*
x86 Processor Exceptions
Interrupt Number	Class			Description	Error 						Code
		0			Fault			Divide by 0								None
		1		Trap or Fault		Single step (Debugger)					None. Can be retrived from debug registers
		2			Unclassed		Non Maskable Interrupt (NMI) Pin		Not applicable
		3			Trap			Breakpoint (Debugger)					None
		4			Trap			Overflow								None
		5			Fault			Bounds check							None
		6			Fault			Unvalid OPCode							None
		7			Fault			Device not available					None
		8			Abort			Double Fault							Always 0
		9			Abort(Reserved	Coprocessor Segment Overrun				None
		10			Fault			Invalid Task State Segment (TSS)		See error code below
		11			Fault			Segment Not Present						See error code below
		12			Fault			Stack Fault Exception					See error code below
		13			Fault			General Protection Fault (GPF)			See error code below
		14			Fault			Page Fault								See error code below
		15	------------------	Unassigned	--------------------------------------------------
		16			Fault			x87 FPU Error							None. x87 FPU provides own error information
		17			Fault			Alignment Check (486+ Only)				Always 0
		18			Abort			Machine Check (Pentium/586+ Only)		None. Error information abtained from MSRs
		19			Fault			SIMD FPU Exception						None
		20-31	-	Reserved	-
		32-255	-	Avilable for software use	Not applicable
*/
void isr_handler(registers_t regs)
{
	monitor_write("recieved interrupt: ");
	monitor_write_dec(regs.intNum);
	monitor_put('\n');
}

void isr0()
{
	//No error code
	//interrupt num is 0
	__asm__ __volatile__("pushl $0;
						  pushl $0");
	isr_common_stub();

}
void isr1()
{
	__asm__ __volatile__("pushl $0;
						  pushl $1");
	isr_common_stub();

}
void isr2()
{
	__asm__ __volatile__("pushl $0;
						  pushl $2");
	isr_common_stub();

}
void isr3()
{
	__asm__ __volatile__("pushl $0;
						  pushl $3");
	isr_common_stub();

}
void isr4()
{
	__asm__ __volatile__("pushl $0;
						  pushl $4");
	isr_common_stub();

}
void isr5()
{
	__asm__ __volatile__("pushl $0;
						  pushl $5");
	isr_common_stub();

}
void isr6()
{
	__asm__ __volatile__("pushl $0;
						  pushl $6");
	isr_common_stub();

}
void isr7()
{
	__asm__ __volatile__("pushl $0;
						  pushl $7");
	isr_common_stub();

}
void isr8()
{
	__asm__ __volatile__("pushl $0;
						  pushl $8");
	isr_common_stub();

}
void isr9()
{
	__asm__ __volatile__("pushl $0;
						  pushl $9");
	isr_common_stub();

}
void isr10()
{
	__asm__ __volatile__("pushl $0;
						  pushl $10");
	isr_common_stub();

}
void isr11()
{
	__asm__ __volatile__("pushl $0;
						  pushl $11");
	isr_common_stub();

}
void isr12()
{
	__asm__ __volatile__("pushl $0;
						  pushl $12");
	isr_common_stub();

}
void isr13()
{
	__asm__ __volatile__("pushl $0;
						  pushl $13");
	isr_common_stub();

}
void isr14()
{
	__asm__ __volatile__("pushl $0;
						  pushl $14");
	isr_common_stub();

}
void isr15()
{
	__asm__ __volatile__("pushl $0;
						  pushl $15");
	isr_common_stub();

}
void isr16()
{
	__asm__ __volatile__("pushl $0;
						  pushl $16");
	isr_common_stub();

}
void isr17()
{
	__asm__ __volatile__("pushl $0;
						  pushl $17");
	isr_common_stub();

}
void isr18()
{
	__asm__ __volatile__("pushl $0;
						  pushl $18");
	isr_common_stub();

}
void isr19()
{
	__asm__ __volatile__("pushl $0;
						  pushl $19");
	isr_common_stub();

}
void isr20()
{
	__asm__ __volatile__("pushl $0;
						  pushl $20");
	isr_common_stub();

}
void isr21()
{
	__asm__ __volatile__("pushl $0;
						  pushl $21");
	isr_common_stub();

}
void isr22()
{
	__asm__ __volatile__("pushl $0;
						  pushl $22");
	isr_common_stub();

}
void isr23()
{
	__asm__ __volatile__("pushl $0;
						  pushl $23");
	isr_common_stub();

}
void isr24()
{
	__asm__ __volatile__("pushl $0;
						  pushl $24");
	isr_common_stub();

}
void isr25()
{
	__asm__ __volatile__("pushl $0;
						  pushl $25");
	isr_common_stub();

}
void isr26()
{
	__asm__ __volatile__("pushl $0;
						  pushl $26");
	isr_common_stub();

}
void isr27()
{
	__asm__ __volatile__("pushl $0;
						  pushl $27");
	isr_common_stub();

}
void isr28()
{
	__asm__ __volatile__("pushl $0;
						  pushl $28");
	isr_common_stub();

}
void isr29()
{
	__asm__ __volatile__("pushl $29;
						  pushl $30");
	isr_common_stub();

}
void isr30()
{
	__asm__ __volatile__("pushl $30;
						  pushl $0");
	isr_common_stub();

}
void isr31()
{
	__asm__ __volatile__("pushl $31;
						  pushl $0");
	isr_common_stub();

}




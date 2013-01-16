#include"common.h"
/*
asm ( assembler template 
           : output operands                   optional 
           : input operands                    optional 
           : list of clobbered registers       optional 
           );

If there are a total of n operands (both input and output inclusive), then the first output operand is numbered 0, continuing in increasing order, and the last input operand is numbered n-1.
	
	Output operand expressions must be lvalues.
	The input operands are not restricted like this. They may be expressions.
 */
void outb(u16int port,u8int value)
{
	//volatile : our assembly statement must execute where we put it,keep it from moving, deleting and all
	asm volatile ("outb %1,%0": : "dN"(port), "a" (value));
}

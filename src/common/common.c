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

1. Register operand constraint(r)
	+---+--------------------+
	| r |    Register(s)     |
	+---+--------------------+
	| a |   %eax, %ax, %al   |
	| b |   %ebx, %bx, %bl   |
	| c |   %ecx, %cx, %cl   |
	| d |   %edx, %dx, %dl   |
	| S |   %esi, %si        |
	| D |   %edi, %di        |
	+---+--------------------+
2. 
"m" : A memory operand is allowed, with any kind of address that the machine supports in general.
"o" : A memory operand is allowed, but only if the address is offsettable. ie, adding a small offset to the address gives a valid address.
"V" : A memory operand that is not offsettable. In other words, anything that would fit the `m’ constraint but not the `o’constraint.
"i" : An immediate integer operand (one with constant value) is allowed. This includes symbolic constants whose values will be known only at assembly time.
"n" : An immediate integer operand with a known numeric value is allowed. Many systems cannot support assembly-time constants for operands less than a word wide. Constraints for these operands should use ’n’ rather than ’i’.
"g" : Any register, memory or immediate integer operand is allowed, except for registers that are not general registers.

"I" : Constant in range 0 to 31 (for 32-bit shifts).
"J" : Constant in range 0 to 63 (for 64-bit shifts).
"K" : 0xff.
"L" : 0xffff.
"M" : 0, 1, 2, or 3 (shifts for lea instruction).
"N" : Constant in range 0 to 255 (for out instruction).
"f" : Floating point register
"t" : First (top of stack) floating point register
"u" : Second floating point register
"A" : Specifies the `a’ or `d’ registers. This is primarily useful for 64-bit integer values intended to be returned with the `d’ register holding the most significant bits and the `a’ register holding the least significant bits.
 */
void outb(uint16 port,uint8 value)
{
	//volatile : our assembly statement must execute where we put it,keep it from moving, deleting and all
	/*
		No output
		"dN(port)" : port is copied to register d  and Constant in range 0 to 255	   
		"a"(value) : value is copied to register a
	*/
	__asm__ __volatile__ ("outb %1,%0": : "dN"(port), "a" (value));
}

uint8 intb(uint16 port)
{
	uint8 ret;
	__asm__ __volatile__("inb %1,%0": "=a"(ret) : "dN"(port));
	return ret;
}

uint16 inw(uint16 port)
{
	uint16 ret;
	__asm__ __volatile__("inw %1,%0" : "=a"(ret):"dN"(port));
	return ret;
}


/*-------------memory operation---------------------------*/
void memset(uint8* addr,uint8 val,uint32 length)
{
	for(int i=0;i!=length;++i)
	{
		*(addr+i) = val;
	}
}


/*-----------------------math----------------------------*/
uint32 pow(uint32 a,uint32 b)
{
	if(b == 0)
		return 1;
	else if(b == 1)
		return a;
	else
	{
		for(int i=1;i!=b;++i)
		{
			a*=a;
		}
		return a;
	}
}









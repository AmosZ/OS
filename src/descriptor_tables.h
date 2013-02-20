#ifndef DESCRIPTOR_TABLE
#define DESCRIPTOR_TABLE
#include "common.h"
/*
   GDT entry
   ************************************************************
  Segment descriptor provide information of mapping logical address to 
  linear address
  Descrptor used for System Segments:
					Granularity					Access
  |31---------24 | 23 22 21 20 19---------16 | 15-------11-8| 7----------0 |
  | Base[31:24]  | G  D  O  AVL LIMIT[19:16] |  P DPL 1 Type|  Base[23:16] | 4 Bytes
  |          Base[15:0]						 |          Limit[15:0]        | 0 Bytes
 ********************************************************


   P :   Is segment present? (1 = Yes)
   DPL : Descriptor privilege level - Ring 0 - 3.
   DT :  Descriptor type
   Type Segment type - code segment / data segment.
   G : Granularity (0 = 1 byte, 1 = 1kbyte)
   D : Operand size (0 = 16bit, 1 = 32bit)
   0 : Should always be zero.
   Available : Available for system use (always zero).
*/
struct gdt_entry_struct//From low address to high?
{
	uint16 limit_low;	//the lower 16bits of the limit
	uint16 base_low;	//the lower 16 bits of the base;
	uint8  base_middle; //the middle 8 bits of the base;
	uint8  access;		//Access flags [P,DPL,]
	uint8 granularity;	
	uint8 base_high;	//the high 8 bits of the base
} __attribute__ ((packed));
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.

/*

IDT entry, Interrupt Gates
Name------- Bit----------Full Name-------------- Description
Offset 	| 48..63	|	 Offset 16..31	 |	Higher part of the offset.
P	   	|   47	 	|	 Present	 	 |	can be set to 0 for unused interrupts or for Paging.
DPL	   	| 45,46	 	|	 Descriptor 	 |	Privilege Level	 Gate call protection. 
										 |	Specifies which privilege Level the calling Descriptor minimum should have. 
										 |	So hardware and CPU interrupts can be protected from beeing called out of userspace.

S	   	|  44	 	|	 Storage Segment = 0 for interrupt gates.
Type   	| 40..43	| 	 Gate Type 0..3	 Possible IDT gate types :

	0b0101	 0x5	 5	 80386 32 bit Task gate
	0b0110	 0x6	 6	 80286 16-bit interrupt gate
	0b0111	 0x7	 7	 80286 16-bit trap gate
	0b1110	 0xE	 14	 80386 32-bit interrupt gate
	0b1111	 0xF	 15	 80386 32-bit trap gate

0	   	| 32..39	| 	 Unused 0..7	 |	Have to be 0.
Selector| 16..31	| 	 Selector 0..15  |	Selector of the interrupt function (to make sense - the kernel's selector). 
						 					The selector's descriptor's DPL field has to be 0.

Offset	| 0..15	 	|	 Offset 0..15	 |	Lower part of the interrupt function's offset address (also known as pointer).

*/

struct idt_entry_struct
{
	uint16 base_low;
	uint16 select;
	uint8  always0;
	uint8  access;
	uint16 base_high;
} __attribute__ ((packed));

typedef struct idt_entry_struct idt_entry_t;



struct gdt_ptr_struct
{
	uint16 limit;	//the upper 16bits of all selector limits(size of table minus one)
	uint32 base;	//the address of the first gdt_entry_t struct;
} __attribute__ ((packed));


struct idt_ptr_struct
{
	uint16 limit;
	uint32 base;
} __attribute__ ((packed));

typedef struct idt_ptr_struct idt_ptr_t;

typedef struct gdt_entry_struct gdt_entry_t;

typedef struct gdt_ptr_struct gdt_ptr_t;

void init_descript_table();

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

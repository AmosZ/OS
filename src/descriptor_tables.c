#include "descriptor_tables.h"
#include "common.h"
#include "monitor.h"

extern void gdt_flush(uint32);

static void init_gdt();
static void gdt_set_gate(sint32,uint32,uint32,uint8,uint8);

static void init_idt();
static void idt_set_gate(uint8,uint32,uint16,uint8);


gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;
idt_entry_t idt_entries[256];
idt_entry_t idt_ptr;

/*static void gdt_flush(uint32 address)
{
	__asm__ __volatile__ (
			"lgdt (%%eax);"
			"movw $0x10,%%ax;"
			"movw %%ax,%%ds;"
			"movw %%ax,%%es;"	
			"movw %%ax,%%fs;"
			"movw %%ax,%%gs;"	
			"movw %%ax,%%ss;"
			"ljmp $0x08,$FLUSH;"
		"FLUSH: ret;"
			: :"a"(address));
}*/



void init_descript_table()
{
	init_gdt();
	init_idt();
}


static void init_idt()
{
	idt_ptr.limit = sizeof(idt_entry_t)*256 - 1;
	idt_ptr.base = (uint32)&idt_entries;
	memset(&idt_entries,0,sizeof(idt_entry_t)*256);

	/*
	   Here are top 32 interrupt/expection handler.
	   How we distinguish among interrupt,fault,trap and abort???
	*/
	idt_set_gate(0,(uint32)isr0,0x08,0x8f); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(1,(uint32)isr1,0x08,0x8f); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(2,(uint32)isr2,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(3,(uint32)isr3,0x08,0x8f); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(4,(uint32)isr4,0x08,0x8f); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(5,(uint32)isr5,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(6,(uint32)isr6,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(7,(uint32)isr7,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(8,(uint32)isr8,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(9,(uint32)isr9,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(10,(uint32)isr10,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(11,(uint32)isr11,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(12,(uint32)isr12,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(13,(uint32)isr13,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(14,(uint32)isr14,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(15,(uint32)isr15,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(16,(uint32)isr16,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(17,(uint32)isr17,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(18,(uint32)isr18,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(19,(uint32)isr19,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(20,(uint32)isr20,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(21,(uint32)isr21,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(22,(uint32)isr22,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(23,(uint32)isr23,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(24,(uint32)isr24,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(25,(uint32)isr25,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(26,(uint32)isr26,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(27,(uint32)isr27,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(28,(uint32)isr28,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(29,(uint32)isr29,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(30,(uint32)isr30,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate
	idt_set_gate(31,(uint32)isr31,0x08,0x8e); //P = 1,DPL = 000     Type = e 80386 32-bit interrupt gate

	idt_flush((uint32)&idt_ptr);
}


static void init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32)&gdt_entries;

	gdt_set_gate(0,0,0,0,0);//first gdt entry is NULL.
	/*
	Access:
	   P = 1;
	   DPL = 001
	   1 = 1; //descrptor used for system segments
	   Type = 010; code segment
	Gran:
		G = 1 unit = 4KB
		X = 1
		0 = 0
		AVL = 0; availble for system use;
		
		0xffff is meanless;
	 */
	gdt_set_gate(1,0,0xffffffff,0x9A,0xCF);//Code segment 0x9A=b1001 1010 0xCF=b11001111.For kernel level application??? 
	gdt_set_gate(2,0,0xffffffff,0x92,0xCF);//Data segment

	gdt_set_gate(3,0,0xffffffff,0xFA,0xCF);//user mode code segment;
	gdt_set_gate(4,0,0xffffffff,0xF2,0xCF);

	gdt_flush((uint32)&gdt_ptr);

	
}

static void gdt_set_gate(sint32 num,uint32 base,uint32 limit,uint8 access,uint8 gran)
{
	gdt_entries[num].base_low = (base & 0xffff);
	gdt_entries[num].base_middle = ((base>>16) & 0xff);
	gdt_entries[num].base_high = (base>>24) & 0xff;

	gdt_entries[num].limit_low = (limit & 0xffff);
	gdt_entries[num].granularity = (limit>>16) & 0x0f; //limit[19:16]

	/*G,X,0,AVL*/
	gdt_entries[num].granularity |= gran & 0xf0;

	/*P,DPL,1,TYPE*/
	gdt_entries[num].access = access;
}

static void idt_set_gate(uint8 num,uint32 base,uint16 sel,uint8 access)
{
	idt_entries[num].base_low = base & 0xffff;
	idt_entries[num].base_high = (base>>16) & 0xffff;
	idt_entries[num].select = sel;
	idt_entries[num].access = access;
	idt_entries[num].always0 = 0;
}





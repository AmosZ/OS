#define move_to_user_mode() \
__asm__ ("movl %%esp,%%eax\n\t" \
	"pushl $0x17\n\t" \
	"pushl %%eax\n\t" \
	"pushfl\n\t" \
	"pushl $0x0f\n\t" \
	"pushl $1f\n\t" \
	"iret\n" \
	"1:\tmovl $0x17,%%eax\n\t" \
	"movw %%ax,%%ds\n\t" \
	"movw %%ax,%%es\n\t" \
	"movw %%ax,%%fs\n\t" \
	"movw %%ax,%%gs" \
	:::"ax")

#define sti() __asm__ ("sti"::)
#define cli() __asm__ ("cli"::)
#define nop() __asm__ ("nop"::)

#define iret() __asm__ ("iret"::)
/****************************************************
	Interrupt/Trap gate descriptor   
	|31----------16|  15 14-13 12--8  7-----------0 |
	|offset[31:16] |   P  DPL   Type  000 Reserved  | 4 Bytes
	|  Selector    |       Offset[15:0]             | 0 Bytes

	Interrupt  Gate: Type = B01110
	Trap Gate:       Type = B01111

*****************************************************/
// gate_addr = gate address
// addr = Interrupr handle address(offset)

// %1 == (*((char *) (gate_addr)))
// %2 == (*(4+(char *) (gate_addr)))
#define _set_gate(gate_addr,type,dpl,addr) \
	// dx == low 16 bits of addr
	// ax = dx
	// eax = 0x0008 low 16bits of addr
__asm__ ("movw %%dx,%%ax\n\t" \
	"movw %0,%%dx\n\t" \
	// dx == ((short) (0x8000+(dpl<<13)+(type<<8))) 
	// edx == top 16bits of addr ((short) (0x8000+(dpl<<13)+(type<<8)))
	"movl %%eax,%1\n\t" \
	//  gate_addr = 0x0008 low 16bits of addr
	"movl %%edx,%2" \
	// gate_addr + 4 = top 16bits of addr ((short) (0x8000+(dpl<<13)+(type<<8)))
	: \
	: "i" ((short) (0x8000+(dpl<<13)+(type<<8))), \
	"o" (*((char *) (gate_addr))), \
	"o" (*(4+(char *) (gate_addr))), \
	"d" ((char *) (addr)),\ 
	"a" (0x00080000)\)
// "i" : short for instant
// "o" : memory oprand and offset
// "d" : short for edx register


/**************************************************
  Privilege level 0 : kernel
  Privilege level 3 : application
***************************************************/
#define set_intr_gate(n,addr) \
	_set_gate(&idt[n],14,0,addr)

#define set_trap_gate(n,addr) \
	_set_gate(&idt[n],15,0,addr)

#define set_system_gate(n,addr) \
	_set_gate(&idt[n],15,3,addr)

/************************************************************
  Segment descriptor provide information of mapping logical address to 
  linear address
  |31---------24 | 23 22 21 20 19----16 | 15----------8| 7----------0 |
  | Base[31:24]	 | G  X  O  AVL LIMIT  	|  P DPL 1 Type|  Base[23:16] | 4 Bytes
  |          Base[15:0]                 |	       Limit[15:0]        | 0 Bytes
 ********************************************************/

//gate_addr: descript address
#define _set_seg_desc(gate_addr,type,dpl,base,limit) {\
	*((gate_addr)+1) = ((base) & 0xff000000) | \
		(((base) & 0x00ff0000)>>16) | \
		((limit) & 0xf0000) | \
		((dpl)<<13) | \
		(0x00408000) | \
		((type)<<8); \
	*(gate_addr) = (((base) & 0x0000ffff)<<16) | \
		((limit) & 0x0ffff); }						 




#define _set_tssldt_desc(n,addr,type) \
__asm__ ("movw $104,%1\n\t" \
	"movw %%ax,%2\n\t" \
	"rorl $16,%%eax\n\t" \
	"movb %%al,%3\n\t" \
	"movb $" type ",%4\n\t" \
	"movb $0x00,%5\n\t" \
	"movb %%ah,%6\n\t" \
	"rorl $16,%%eax" \
	::"a" (addr), "m" (*(n)), "m" (*(n+2)), "m" (*(n+4)), \
	 "m" (*(n+5)), "m" (*(n+6)), "m" (*(n+7)) \
	)

#define set_tss_desc(n,addr) _set_tssldt_desc(((char *) (n)),((int)(addr)),"0x89")
#define set_ldt_desc(n,addr) _set_tssldt_desc(((char *) (n)),((int)(addr)),"0x82")


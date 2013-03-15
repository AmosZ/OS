# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.
vpath common.% common
vpath monitor.% monitor
vpath descriptor_tables.% descriptor_tables
vpath gdt.% descriptor_tables
vpath isr.% int
vpath interrupt.% int

SOURCES=boot.o main.o monitor.o common.o descriptor_tables.o gdt.o isr.o interrupt.o 

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=c99 -Icommon/
#-nostdlib: Do not use the standard system startup files or libraries when linking. 
#-nostdinc: Do not search the standard system directories for header files.
#-fno-builtin: Don't recognize built-in functions that do not begin with __builtin_ as prefix.
#-fno-stack-protector: Don't  emit extra code to check for buffer overflows, such as stack smashing attacks.

LDFLAGS=-Tlink.ld 
ASFLAGS=-felf

all: $(SOURCES) link 

boot.o:boot.s
	nasm -o boot.o $(ASFLAGS) boot.s
main.o:main.c
	gcc -o main.o $(CFLAGS) -Imonitor/ -c main.c

monitor.o:monitor.h monitor.c
	gcc -o monitor.o $(CFLAGS) -c monitor/monitor.c

common.o:common.c common.h
	gcc -o common.o $(CFLAGS) -c common/common.c

descriptor_tables.o:descriptor_tables.h descriptor_tables.c
	gcc -o descriptor_tables.o $(CFLAGS) -Iint -c descriptor_tables/descriptor_tables.c

gdt.o:gdt.s
	nasm -o gdt.o $(ASFLAGS) descriptor_tables/gdt.s

interrupt.o:interrupt.s
	nasm -o interrupt.o $(ASFLAGS) int/interrupt.s

isr.o:isr.c isr.h
	gcc -o isr.o $(CFLAGS) -Imonitor -c int/isr.c

clean:
	-rm *.o kernel

link:link.ld
	ld $(LDFLAGS) -o kernel $(SOURCES)

#.s.o:
#	nasm $(ASFLAGS) $<

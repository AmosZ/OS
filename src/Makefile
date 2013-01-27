# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o monitor.o common.o descriptor_tables.o gdt.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=c99
#-nostdlib: Do not use the standard system startup files or libraries when linking. 
#-nostdinc: Do not search the standard system directories for header files.
#-fno-builtin: Don't recognize built-in functions that do not begin with __builtin_ as prefix.
#-fno-stack-protector: Don't  emit extra code to check for buffer overflows, such as stack smashing attacks.


LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link 

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

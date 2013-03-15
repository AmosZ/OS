#include "monitor.h"
int main(struct multiboot *mboot_ptr)
{
	monitor_clear();
	monitor_write("Hello world");	
	__asm__ __volatile__ ("int $0x3");
	__asm__ __volatile__ ("int $0x4");
	return 0;
}

#ifndef COMMON_H
#define COMMON_H
typedef unsigned int uint32;
typedef			 int sint32;
typedef unsigned short uint16;
typedef			 short sint16;
typedef unsigned char  uint8;
typedef			 char  sint8;

/*port operation*/
void outb(uint16 port,uint8 value);//output some value on port
uint8 inb(uint16 port);//read value from port
uint16 inw(uint16 port);

/*memory operation*/
void memset(uint8*,uint8,uint32);

/*math*/
uint32 pow(uint32 a,uint32 b);
#endif

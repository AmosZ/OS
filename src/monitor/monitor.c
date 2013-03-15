#include "monitor.h"

void monitor_put(char c)
{
	uint8 backColor = 0;//black
	uint8 foreColor = 15;//white;

	uint8 attributeByte = (backColor << 4) | (foreColor & 0x0F);
	uint16 attribute = attributeByte << 8;
	uint16 *location;

	if(c == 0x08 && cursor_x)//backspace
	{
		cursor_x--;
	}
	else if(c == 0x09)//tab
	{
		cursor_x = (cursor_x + 8) & ~(8-1);//!!good!, adapte to cursor's type!
	}
	else if(c == '\r')
	{
		cursor_x = 0;
	}
	else if(c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	else if(c >= ' ')
	{
		location = video_memory + (cursor_y*80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	if(cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y++;
	}
	scroll();
	move_cursor();
	
}

void monitor_clear()
{
	uint8 attributeByte = (0<<4 | 15&0x0F);
	uint16 blank = 0x20/*space*/ | (attributeByte << 8);
	for(int i=0;i!=80*25;++i)
	{
		video_memory[i] = blank;
	}
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void monitor_write(char* c)
{
	int i = 0;
	while(c[i])
	{
		monitor_put(c[i++]);
	}
}

void monitor_write_dec(uint32 value)
{
	uint8 digit = 0;
	while(value/=10)
		digit++;
	
	while(digit)
	{
		monitor_put(value/pow(10,digit));
		value -= pow(10,digit);
		digit--;
	}

}




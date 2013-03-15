#ifndef MONITOR_H
#define MONITOR_H
#include "common.h"

static uint16 cursor_x,cursor_y;
static uint16 *video_memory = (uint16*)0xB8000;

//Write a single character out to the screen
void monitor_put(char c);

//Clear rhe screen to all black
void monitor_clear();

//Output a null-terminated ASCII string to the monitor
void monitor_write(char* c);
//Output a uint32 
void monitor_write_dec(uint32);
//Update the hardware cursor
/*
	Update the hardware cursor
	Parameter:
		x : column number
		y : row number
	Return	NONE
	
	VGA command port : 0x3D4.	
		command 14: tell it we are sending the high byte
		command 15: we are sending the low byte				
	VGA data port : 0x3D5
*/
static void move_cursor()
{
	uint16 cursorLocation = cursor_y*80 + cursor_x;
	outb(0x3D4,14);
	outb(0x3D5,cursorLocation >> 8);
	outb(0x3D4,15);
	outb(0x3D5,cursorLocation);
}

//Scroll the text on the screen up by one line
static void scroll()
{
	uint8 attributeByte = (0 << 4)/*black*/ | (15 & 0x0F)/*white*/;
	uint16 blank = 0x20 | (attributeByte << 8);
	if(cursor_y >= 25)
	{
		int i=0;
		for(i=0*80;i!= 24*80;i++)
		{
			video_memory[i] = video_memory[i+80];
		}
		for(i = 24*80; i< 25*80; i++)
		{
			video_memory[i] = blank;
		}
		cursor_y = 24;
	}
	
}









#endif

#include "DIO.h"
#define COMMON_CATHODE

void seven_segment_init(unsigned char portname)
{
	DIO_setPORTDir(portname,0xff);
}
void seven_segment_write(unsigned char portname,unsigned char counter)
{
	#ifdef COMMON_CATHODE
	unsigned char numbers[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f};
	#else
	unsigned char numbers[]={~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x47,~0x7f,~0x6f};
	#endif
	DIO_writePORT(portname,numbers[counter]);
}
void seven_segment_init_bcd(unsigned char portname,unsigned char nibble)
{
	switch(nibble)
	{
		case 'L':
		case 'l':
		DIO_setPINDir(portname,0,1);
		DIO_setPINDir(portname,1,1);
		DIO_setPINDir(portname,2,1);
		DIO_setPINDir(portname,3,1);
		break;
		case 'H':
		case 'h':
		DIO_setPINDir(portname,4,1);
		DIO_setPINDir(portname,5,1);
		DIO_setPINDir(portname,6,1);
		DIO_setPINDir(portname,7,1);
		break;
	}
}
void seven_segment_write_bcd(unsigned char portname,unsigned char nibble,unsigned char val)
{
	switch(nibble)
	{
		case 'L':
		case 'l':
		DIO_write_low_nibble(portname,val);
		break;
		case 'H':
		case 'h':
		DIO_write_high_nibble(portname,val);
		break;
	}
}
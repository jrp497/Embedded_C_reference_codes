#include <REG51F.H>
#include<intrins.h>
sbit sda=P1^7;		//serial data line
sbit scl=P1^6;		//serial clk line
sbit a7=ACC^7;		//define acc in bits
sbit a6=ACC^6;
sbit a5=ACC^5;
sbit a4=ACC^4;
sbit a3=ACC^3;
sbit a2=ACC^2;
sbit a1=ACC^1;
sbit a0=ACC^0;
bit c=0,i;
bit b,flag1;
// i2c protocal routine
void start();
void stop();
void shout(unsigned char);
void shin();
void nak();
void ack();
void write_port();
unsigned char at;
/*--------------------------------*/
void main(void)
{
	ACC=0x00;
	write_port();
	while(1)
	{
	}
}//end main
//--------------------------------------------------------------------------------
//write data in accumulator to the PCF8574 PORT.
//carry set to indicate error.
//spoils a and psw.
void write_port()
{
		B=ACC;
		start();
	if(c)
		{
		goto x31;
		}	
	//	at=0x40;
		shout(0x40);
	if(c)
		{
		goto x32;
		}
		at=B;

	shout(at);
	P0=at;
		if(c)
		{
			goto x32;
		}
		c=0;
		
x32:
	stop();
x31:
	b=1;
//	P0=0x0f;
}		
 
/*----------------------------------*/

/*------------------------------------*/
void start()
{

	sda=1;
	scl=1;
		if(!sda)
			goto x40;
		if(!scl)
			goto x40;
		_nop_();
			sda=0;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
			scl=0;
			c=0;
		goto x41;	

x40:
	c=1;
	
x41:
	b=0;

} 
/*----------------------------------*/
void stop()
{
	sda=0;
		_nop_();	
		_nop_();
	scl=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	sda=1;
}//end stop
/*----------------------------------*/
void shout(unsigned char at)
{
	unsigned char k,j=0x80;
	for(k=0;k<8;k++)
	{
		sda=(at & j);
		j=j>>1;
		scl=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		scl=0;
	}
	sda=1;
	scl=1;
	_nop_();
	_nop_();
	c=sda;
	_nop_();
	_nop_();
	scl=0;
}

/*------------------------------------*/
void shin()
{
	unsigned char j, value=0x00,i=0x80;
	sda=1;

	for(j=0;j<8;j++)
	{
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	flag1=sda;
	if (flag1)
	value=(value|i);
	i=i>>1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	scl=0;
	}
	at=value;
}
/*----------------------------------*/

/*-----------------------------------------*/
// Clock out an acknowledge bit (low).
//SCL expected low on entry. Return with SCL, SDA low.

void ack()
{

	
		sda=0;		// ACK bit
		_nop_();			// enforce SCL low and data setup
		_nop_();			 
		scl=1;		// raise clock
		_nop_();			// enforce SCL high
		_nop_();			
		_nop_();		
		_nop_();			
		scl=0;		// drop clock
		 _nop_();
}

//----------------------------------------------------------------------
//Clock out a negative acknowledge bit (high).
//SCL expected low on entry. Return with SCL low, SDA high.
void nak()
{
		sda=1;			// NAK bit
		_nop_();			// enforce SCL low and data setup
		_nop_();		
		scl=1;	// raise clock
		_nop_();				// enforce SCL high
		_nop_();
		_nop_();
		_nop_();
		_nop_();			
		scl=0;				// drop clock
		_nop_();
}
//-------------------------------------


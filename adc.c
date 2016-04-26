#include <REG51F.H>
#include<INTRINS.H>

unsigned int count,a,b,i;
bit c;

sbit scl=P1^6;
sbit sda=P1^7;

void start();
void stop();

void ack_read();
void ack_write();
void nak();
void sh_out(unsigned int);
unsigned int shin();
void delay(unsigned char);

void main()
{
		while(1)
	{
	start();
	sh_out(0x90);

	sh_out(0x00);
	

	
	start();
	sh_out(0x91);
	a=shin();
	ack_write();
	b=shin();
	nak();
	stop();
	P0=b;
	
	}
}

void start()
{
	sda=1;
	_nop_();
	scl=1;
	_nop_();

	sda=0;
	_nop_();
	scl=0;
	_nop_();
}

void stop()
{
	sda=0;
	_nop_();
	scl=1;
	_nop_();

	sda=1;
	_nop_();
	scl=0;
	_nop_();
}

void sh_out(unsigned int a)
{
	unsigned int w;
	scl=0;
	_nop_();
	for(i=0;i<8;i++)
	{
		
		w=a;
		w=w&0x80;
		if(w==0x80)
		{
			sda=1;
		}
		else
		{
			sda=0;
		}
		scl=1;
		_nop_();
		scl=0;
		//_nop_();
		a=a<<1;
	}
	ack_read();
}

void ack_read()
{
	scl=1;
	_nop_();
	c=sda;
	_nop_();
	scl=0;
}

unsigned int shin()
{
	unsigned char d;
	sda=1;
	for(i=0;i<8;i++)
	{
		scl=1;
		d=d<<1;
		if(sda==1)
		{
			d=d|0x01;
		}
		else
		{
			d=d&0xfe;
		}
		scl=0;
	}
	return(d);
}

void ack_write()
{
	sda=0;
	scl=1;
	_nop_();
	scl=0;
}
void nak()
{
	sda=scl=1;
	_nop_();
	scl=0;
}

void delay(unsigned char t)
{
	unsigned char i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<120;j++);
	}
}

#include <REG51F.H>
#include<INTRINS.H>

unsigned int count,a,b,i,ds1,ds2;
code unsigned char arr1[]={"0123456789ABCDEF"};
bit c;

sbit scl=P1^6;
sbit sda=P1^7;

sbit b1=P0^0;
sbit rs=P0^1;
sbit rw=P0^2;
sbit e=P0^3;

sbit d4=P0^4;
sbit d5=P0^5;
sbit d6=P0^6;
sbit d7=P0^7;

sbit a4=B^4;
sbit a5=B^5;
sbit a6=B^6;
sbit a7=B^7;

void start();
void stop();
void ack_read();
void ack_write();
void nak();
void sh_out(unsigned int);
unsigned int shin();

void map1();

void init_lcd();
void init_disp();
void disp();
void cw();
void dw1();
void toggle();
void busy();
void map();
void delay(unsigned char);

void main()
{
	init_lcd();
	init_disp();
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

	B=b;
	map1();
	disp();
	delay(2000);
	clr_scr();
	
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

void init_lcd()
{
	b1=0;
	delay(15);
	B=0x03;
	cw();
	delay(5) ;
	B=0x03;
	cw();
	delay(5) ;
	B=0x03;
	cw();
	delay(5);
	B=0x02;
	cw();
	delay(5);
	B=0x28;
	cw();
	delay(5);
	B=0x0f;
	cw();
	delay(5);
	B=0x06;
	cw();
	delay(5);
	B=0x10;
	cw();
	delay(5);
	B=0x01;
	cw();
	delay(5);
}

void cw()
{
	//busy();
	rs=rw=0;
	map();
	toggle();
	B=B<<4;
	map();
	toggle();
}


void dw1()
{
	//busy();
	rs=1;
	rw=0;
	map();
	toggle();
	B=B<<4;
	map();
	toggle();
}

void toggle()
{
	e=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	e=0;
	_nop_();
	_nop_();
	_nop_();
}

void busy()
{
	d7=rw=e=1;
	rs=0;
	_nop_();
	_nop_();
	c=d7;
	_nop_();
	_nop_();
	e=0;
	toggle();
	if(c==1)
	{
		busy();
	}
}

void map()
{
	d4=a4;
	d5=a5;
	d6=a6;
	d7=a7;
}

void map1()
{
	ds1=B&0x0f;
	ds2=B&0xf0;
	ds2=ds2>>4;
	ds1=arr1[ds1];
	ds2=arr1[ds2];
}

void init_disp()
{
	ds1=ds2='0';
	disp();
	delay(15);
}

void disp()
{
	B=0x81;
	cw();
	delay(5);
	B=ds1;
	dw1();
	delay(5);

	B=0x80;
	cw();
	delay(5);
	B=ds2;
	dw1();
	delay(5);

}

void delay(unsigned char t)
{
	unsigned char i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<120;j++);
	}
}

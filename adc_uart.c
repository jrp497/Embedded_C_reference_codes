#include <REG51F.H>
#include<INTRINS.H>

unsigned int count,a,b,i,ds1,ds2,d,e;
char low_nib,high_nib;
bit c;
unsigned char arr[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,
					0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e,0x00,0xff};
code unsigned char arr1[]={"0123456789ABCDEF"};

sbit scl=P1^6;
sbit sda=P1^7;

void start();
void stop();
void ack_read();
void ack_write();
void nak();
void sh_out(unsigned int);
unsigned int shin();

void init_uart();
void clr_scr();
void tx();
void rx();
void delay(unsigned char);
void map1();

void main()
{
	init_uart();
	clr_scr();
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
	B=b;
	map1();
	B=ds2;
	tx();
	delay(20);
	B=ds1;
	tx();
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

void map1()
{
	ds1=B&0x0f;
	ds2=B&0xf0;
	ds2=ds2>>4;
	ds1=arr1[ds1];
	ds2=arr1[ds2];
}

void init_uart()
{
	SCON=0x52;
	TMOD=0x20;
	TH1=0xfd;
	TR1=1;
}

void clr_scr()
{
	B=0x1b;
	tx();
	B='[';
	tx();
	B='2';
	tx();
	B='J';
	tx();
}

void tx()
{
	while(TI==0);
	SBUF=B;
	TI=0;
}

void rx()
{
	while(RI==0);
	B=SBUF;
	RI=0;
}

void delay(unsigned char t)
{
	unsigned char i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<120;j++);
	}
}

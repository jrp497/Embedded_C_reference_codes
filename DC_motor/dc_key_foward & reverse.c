#include <REG51F.H>
#include<stdio.h>
sbit	en12=P1^0;		//enable pin
sbit	en34=P1^5;		//enable pin
sbit	inp1=P1^1;		//inp1 for mtr 1
sbit	inp2=P1^2;		//inp2 for mtr 1
sbit	inp3=P1^3;		//inp1 for mtr 2
sbit	inp4=P1^4;		//inp2 for mtr 2
void 	delay(unsigned int);
void	rx();
void	tx();
void init_timer1();
void init_uart();

void	main()
{
	en12=1;
	en34=1;
	init_timer1();
	init_uart();
	printf("\n welcome to dcmotor program\n");
	printf("\n enter F key to FORWARD DIRECTION the dc motor\n");
	printf("\n enter R key to REVERSE DIRECTION the dc motor\n");
	printf("\n enter any key to stop the dc motor\n");

	while(1)
	{
	
	rx();
	tx();
		if(ACC=='F')
		{
		inp1=1;		 //rotate forward
		inp2=0;
		delay(1000);
		}
		else
		{
			if(ACC=='R')
			{
			inp1=0;		//rotate reverse
			inp2=1;
			delay(1000);
			}
			else
			{
				en12=0;
			}
		}
	}	
	
}
void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
	{
	j++;
	}
//	for(j=0;j<1275;j++);
}
void	tx()
{
	while(!TI)
	{
	}
	TI=0;
	ACC=SBUF;
}
void	rx()
{
	while(!RI)
	{
	}
	RI=0;
	SBUF=ACC;
} 
void	init_timer1()
{
TMOD|=0x20;
TH1=0XFD;
TL1=0XFD;
TR1=1;
}
void	init_uart()
{
SCON=0X52;
}



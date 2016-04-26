#include <REG51F.H>

sbit	stm1=P3^4;	//stepper mtr winding1
sbit	stm2=P3^5;	//stepper mtr winding2
sbit	stm3=P3^6;	//stepper mtr winding3
sbit	stm4=P3^7;	//stepper mtr winding4


unsigned char sdelay,csdelay;
unsigned char step_cnt=0;		//half step(0-8)

/*----Defining look up tables here step sequence in half step---------------*/
code unsigned char step_arr[8]={0x80,0xC0,0x40,0x60,0x20,0x30,0x10,0x90};
/*---------------------------------------------------------------------------*/

/*----------------------Function declaration---------------------------------*/							
void init_timer0();
void step_drv();
/*---------------------------------------------------------------------------*/
/* ISR for Timer0--------------------*/
void timer0_ISR (void) interrupt 1 using 2
{
		init_timer0();			//initalise timer0 for 1ms
		step_drv();				//driver prg for stepper mtr
		
	}	
/*-----------------------------------*/
	
/*---------------------------------------------------------------------------*/
void main()
{		
	init_timer0();			//initialise timer0 for 1ms 
	EA=1;
	csdelay=sdelay=2;
	while(1)				//infinite loop 
		{
		}
		
}
/*---------------------------------------------------------------------------*/

/*-----------------------------------*/
void init_timer0()
{
	TMOD|=0x01;					//Timer0 in mode 1
	
	TH0=0xfc;					//count for 1msec
	TL0=0x66;
	TR0=1;
	ET0=1;
}
/*-----------------------------------*/
/*-----------------------------------*/
void step_drv()
{
	csdelay--;
	    if(csdelay==0)
	       {
	          csdelay=sdelay;
	           P3=((P3 & 0x0f)|step_arr[step_cnt]);		//move step pattern frm look up table to port3
	           //P3=step_arr[step_cnt];
	           step_cnt++;
	             if(step_cnt==8)
	                { 
	                	step_cnt=0;
	                }
	       }
}
/*-----------------------------------*/


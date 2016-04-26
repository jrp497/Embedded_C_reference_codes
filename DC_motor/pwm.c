#include <REG51F.H>
#include<stdio.h>

sbit en12=P1^0;
sbit en34=P1^5;
sbit inp1=P1^1;
sbit inp2=P1^2;

void init_timer1();
void uart();
void init_timer0();
void timer_isr();

bit start;
bit b=1;
int ton,toff;
int init_on=0x19,init_off=0x4b ;



 void timer0_isr()interrupt 1 using 2
 {
	init_timer0();
	timer_isr ();
 }

  void main()
  {	 
  	ton=0x0a;
  	toff=0x5a;
  	 init_timer1();
	 uart();
	 init_timer0();
	 EA=1;
	 start=1;
	 while(1)
	 {
	 inp1=0;
	 inp2=1;
	 }

  }


  void init_timer0()
  {
	  TMOD=0x01;
	   TH0=0xfc;
	   TL0=0x66;
	   TR0=1;
	   ET0=1;
 }
  void init_timer1()
      {
       TMOD=0x20;
	   TH1=0xfd;
	   TR1=1;
      } 

void uart()
        {
         SCON=0x52;
		 }
void timer_isr()
 {
if (start)
			{
				if(ton==0x00)
					 {
					 	if(toff==0x00)
					 		{
								ton=init_on;
								toff=init_off;
								goto out;
							}
					 	else
					 		{
					 			toff--;
								en12=0;
								en34=0;
								goto out;
					 		}
					 }
			   else
			   		{
					ton--;
					en12=1;
					en34=0;
					goto out;
					}   	
		}
 else
	   {
	   	en12=0;
		en34=0;
		goto out;
	   }

 out:
 b=~b;
 }



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
void tx();
void rx();

bit start;
bit b=1;
unsigned char x,y,z;
int ton,toff;
int init_on,init_off=0x4b ;



 void timer0_isr()interrupt 1 using 2
 {
	init_timer0();
	init_on=z;
	timer_isr();
 }

  void main()
  {	 
  	ton=0x55;
  	toff=0xaa;
  	 init_timer1();
	 uart();
	 printf("\n\t\t\t WELCOME TO PWM GENERATION FOR DC MOTOR \t\t\t\n\n");
	 init_timer0();
	 EA=1;
	 start=1;
	 
	rx();    				 
    tx();
 /*   x=ACC;   				 
    rx();   				 
    tx();
    y=ACC;   					

    x=x-'0';                 	
    y=y-'0';					
   	

    z=(x*10)+y; 
	printf("\n%d\n",z);           	 */
    
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


void tx()
      {
       while(!TI)
       {
		}
        SBUF=ACC;
		TI=0;
	   }

void rx()
      {
       while(!RI)
       {
        }
        ACC=SBUF;
        RI=0;
       }
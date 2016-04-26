#include <REG51F.H>
#include <stdio.h>
#include <math.h>

sbit en1=P1^0;
sbit en2=P1^0;
sbit en3=P1^5;
sbit en4=P1^5;

sbit ip1=P3^4;    //declaring the varialble for the o/p pins  of the stepper motor. 
sbit ip2=P3^5;
sbit ip3=P3^6;
sbit ip4=P3^7;

unsigned int i,j,k;
unsigned char x,y,z;

void init_timer1();
void uart();
void tx();
void rx();


void main()
{	
	
   	en1=en2=en3=en4=1;
    init_timer1();
	uart();
	printf("\n\t\t\t WELCOME TO STEPPER MOTOR\t\t\t\n");
	 while(1)
	 {
	 
	printf("\nEnter any two number between 0 to 9\n");

    rx();    				 //for receiving the first number entered from the keyboard.
    tx();
    x=ACC;   				 //storing the  received number from the keyboard in accumulator as variable 'x'.

    rx();   				 //for receiving the second number entered from the keyboard.
    tx();
    y=ACC;   					//storing the entered no in accumulator as variable 'y'.

    x=x-'0';                 	//converting the received value of 'x'(ascii) into decimal.
    //printf("\n l=%x\n",l);
  
    y=y -'0';					//converting the received value of 'y'(ascii) into decimal.
   	//printf("\n m=%x\n",m); 

    z=(x*10)+y;            	 //converting the received value of 'z'(ascii) into decimal.
    //printf("\n k=%d\n",k); 
  
  
	for(i=0;i<=z;i++)

{
  
	for(j=0;j<=1500;j++);

    ip1=1;
    ip2=ip3=ip4=0;
    
	 for(j=0;j<=1500;j++);
	
	
  	ip2=1;
    ip1=ip3=ip4=0;
	
	for(j=0;j<=1500;j++);
	
   
	ip3=1;
    ip2=ip1=ip4=0;
	
	for(j=0;j<=1500;j++);
	
   	
	ip4=1;
    ip2=ip3=ip1=0;
	
	for(j=0;j<=1500;j++);	
	
}
}

/*	for(i=0;i<=k;i++)

	{
 	 ip1=1;
   	 ip2=ip3=ip4=0;
    
	 for(j=0;j<=1500;j++);
	
	ip4=1;
    ip2=ip3=ip1=0;
	for(j=0;j<=1500;j++);
	
	ip3=1;
    ip2=ip1=ip4=0;
	for(j=0;j<=1500;j++);

  	ip2=1;
    ip1=ip3=ip4=0;
	
	for(j=0;j<=1500;j++);

	ip1=1;
    ip2=ip3=ip4=0;
    for(j=0;j<=1500;j++);
	
	}*/  
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

/*program to ON and OFF the dc motor*/
#include <REG51F.H>

#include<stdio.h>

sbit en12=P1^0;		//Enable pin for dc motor
sbit inp1=P1^1;		//Input pin 1 for dc motor
sbit inp2=P1^2;		//Input pin 2 for dc motor

void init_timer1();	 //Timer1 used for baud rate 
void uart();		 // Init the uart
char ch;

void main()
{	 
  inp1=1;		
  inp2=0;
  init_timer1();
  uart();
	 	printf("\n\t WELCOME TO DC MOTOR PROGRAM \t\t\t\n\n");
  		printf("\n\tEnter A key to start and B key  for stop\t\t\t\n");
        scanf("%c",&ch);

switch(ch)
	{
		case 'A':
			en12=1;
			
			break;

		case 'B':
			en12=0;
			
			break;

		default:
			printf("\n\n\nU R PRESSING A WRONG KEY\n");
			break;
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

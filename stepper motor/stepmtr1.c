#include <REG51F.H>

sbit	stm1=P3^4;	//stepper mtr winding1
sbit	stm2=P3^5;	//stepper mtr winding2
sbit	stm3=P3^6;	//stepper mtr winding3
sbit	stm4=P3^7;	//stepper mtr winding4
void MSDelay(unsigned int);

void main()
{
	while(1)
		{
			stm1=1;
			stm2=0;
			stm3=0;
			stm4=0;
			MSDelay(500);

			stm1=1;
			stm2=1;
			stm3=0;
			stm4=0;
			MSDelay(500);
				
			stm1=0;
			stm2=1;
			stm3=0;
			stm4=0;
			MSDelay(500);

			stm1=0;
			stm2=1;
			stm3=1;
			stm4=0;
			MSDelay(500);
			
			stm1=0;
			stm2=0;
			stm3=1;
			stm4=0;
			MSDelay(500);
			
			stm1=0;
			stm2=0;
			stm3=1;
			stm4=1;
			MSDelay(500);
			
			stm1=0;
			stm2=0;
			stm3=0;
			stm4=1;
			MSDelay(500);

			stm1=1;
			stm2=0;
			stm3=0;
			stm4=1;
			MSDelay(500);
		}
}

void MSDelay(unsigned int itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
	{
	j++;
	}
}

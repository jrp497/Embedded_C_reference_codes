#include <Philips\8xC31-51-80C51Fx-80C51Rx+.h>
#include <stdio.h>
#include <standard.h>

unsigned int i;
/*---------------------------------------------------------------------------*/
BIT svm P1.6				//servo mtr is connected in port1.6
/*---------------------------------------------------------------------------*/
void main()
{	
		

	while(1)				//infinite loop 
		{
			for(i=0;i<50;i++)
			{
				svm=1;				//generating 1ms pulse repeatedly
				delay(1000);
				svm=0;
				delay_ms(20);
			}
				
			for(i=0;i<50;i++)
			{
				svm=1;				//generating 2ms pulse repeatedly
				delay(2000);
				svm=0;
				delay_ms(20);
			}
				
			
		}
		
}
/*---------------------------------------------------------------------------*/

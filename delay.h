#ifndef __delay_h__
#define __delay_h__

void delay (unsigned int t);
void delay(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<120;j++);
}
#endif
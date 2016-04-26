#ifndef __display_h__
#define __display_h__

sbit w=P2^0;
sbit x=P2^1;
sbit y=P2^2;
sbit z=P2^3;
unsigned int ds0,ds1,ds2,ds3;

void display();
void display()
{
  P2=0xff;
  w=0;
  P0=ds0;
  delay(2);
  
  w=1;
  x=0;
  P0=ds1;
  delay(2);

  x=1;
  y=0;
  P0=ds2;
  delay(2);

  y=1;
  z=0;
  P0=ds3;
  delay(2);

}
#endif	
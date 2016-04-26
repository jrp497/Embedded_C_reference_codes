#ifndef __display_h__
#define __display_h__

sbit w=P2^0;
sbit x=P2^1;
sbit y=P2^2;
sbit z=P2^3;


unsigned int ds0,ds1,ds2,ds3;



unsigned int p[]={0x0fc,0x60,0x0da,0x0f2,0x66,0x0b6,0x0be,0x0e0,0x0fe,0x0f6};



void display1();
void display1()
{
  P2=0xff;
  w=0;
  P0=p[ds0];
  delay(2);
  
  w=1;
  x=0;
  P0=p[ds1];
  delay(2);

  x=1;
  y=0;
  P0=p[ds2];
  delay(2);

  y=1;
  z=0;
  P0=p[ds3];
  delay(2);

}
#endif	
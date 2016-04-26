#include <REG51F.H>
#include <INTRINS.H>
void start();
void shout(unsigned char);
unsigned char shin();
void delay(unsigned int);
void stop();
void epromw();
void epromrd();
void read_ack();
void write_ack();
void noack();
unsigned int a,c,ch,r,b;
bit s;
sbit SDA=P1^7;
sbit SCL=P1^6;
void main()
{

epromw();
delay(200);
epromrd();
}

void epromw()
{
start();
shout(0xA0);
/*if(c==1)
{
P0=0x01;
} */
shout(0x00);
shout(0x00);
shout(0x09);
//delay(1000);
shout(0x02);
stop();
//delay(1000);
}
void epromrd()
{
start();
shout(0xA0);
/*if(c==1)
{
P0=0x01;
} */
shout(0x00);
shout(0x00);
start();
shout(0xA1);
a=shin();
write_ack();
b=shin();
noack();
stop();
P0=a;
delay(1000);
P0=b;
}
void start()
{
SDA=1;
_nop_();
SCL=1;
_nop_();
SDA=0;
_nop_();
SCL=0;
_nop_();
}
void stop()
{
SDA=0;
_nop_();
SCL=1;
_nop_();
SDA=1;
_nop_();
SCL=0;
_nop_();
}

void shout(unsigned char ch)
{
unsigned char g;
SCL=0;
_nop_();

for(r=0;r<8;r++)
{
g=ch;
g=g&0x80;
if(g==0x80)
{
SDA=1;
}
else if(g!=0x80) 
{
SDA=0;

}
SCL=1;
_nop_();
SCL=0;
_nop_();
ch=ch<<1;
_nop_();
}
 read_ack();
 }
void read_ack()
{
SCL=1;
_nop_();
s=SDA;
 _nop_();
 SCL=0;
 _nop_();
}
void write_ack()
{
SDA=0;
SCL=1;
_nop_();
SCL=0;
}

 
void noack()
{
SDA=1;
SCL=1;
_nop_();
SCL=0;
}
unsigned char shin(d)
{
SDA=1;
_nop_();
for(r=0;r<8;r++)
{ 
SCL=1;
_nop_();
d=d<<1;

if(SDA==1)
{
d=d|0x01;
}
else
{
d=d&0xfe;

}

SCL=0;
}
return(d);
}
void delay(unsigned int m)
{
unsigned int w,e;
for(w=0;w<m;w++)
{
for(e=0;e<120;e++);
}
}
		 
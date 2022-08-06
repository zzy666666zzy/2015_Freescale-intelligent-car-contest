#include "lcd5110.h"
#include "font_4_5110.h"
#include "stdio.h"

/*--------------------------------------------------------------*/
//wByte:	the value need to write in
//datOrCmd:	1-data, 0-order
void writebyte5110(unsigned char wByte, unsigned char datOrCmd)
{
    unsigned char i;    
    CS5110_L;                   //Enable
    if(datOrCmd)
      DC5110_H;
    else
      DC5110_L;
    for(i = 8; i; i--)	
    {
        if(wByte & 0x80)
            DIN5110_H;
        else
            DIN5110_L;
        CLK5110_L;
        wByte <<= 1;
        CLK5110_H; 	        //Write in when there is a lift signal
    }
    CS5110_H;   		//Disable
}

//clear5110 the LCD
void clear5110()
{
    unsigned int i;
    writecmd5110(0x80);
    writecmd5110(0x40);
    for(i = 504; i; i--)
        writedat5110(0x00);         //Write 0x00 mean to wipe out
}

//Set the position to write in
//x: 0 - 83
//y: 0 - 5
void moveto5110(unsigned char x, unsigned char y)
{
    writecmd5110(x|0x80);
    writecmd5110(y|0x40);
}

/////////////////////////////////////////////////
//LCD show big part
//x:0~9
//y:0~2
void writechar5110_big(unsigned char x, unsigned char y, unsigned char c) 
{
    unsigned char i, j;
    c -= 32;
    x <<= 3;		
    y <<= 1;		
    for(j = 0; j < 2; j++)
    {
        moveto5110(x, (y + j));
        for(i = 0; i < 8; i++)
            writedat5110(font_4_5110_16x8[c][8 * j + i]);
    }
}

//x:0~9
//y:0~2
void writestring5110_big(unsigned char x, unsigned char y,char *str)
{
    while(*str && x < 10)
    {
        writechar5110_big(x++, y, *str);
        str++;
    }
}

//x:0~9
//y:0~2
void writesfloat5110_big(unsigned char x, unsigned char y, int f)
{
    char tt[10];
    sprintf(tt,"%d",f);
    writestring5110_big(x,y,tt);
}
//end
/////////////////////////////////////////////////
//LCD small part
void writechar5110(unsigned char x, unsigned char y, unsigned char c) 
{
    unsigned char line;
    unsigned int cout ;
    
    cout =  c ;
    if((cout < 32)||((cout > 126)))
         cout = 0;

    cout -= 32;                       //The line num
    cout = cout*5 ;

    for (line=0; line<5; line++)
    {
      writedat5110(font_4_5110_5x8[cout]);
      cout ++ ;
    }
    
//    unsigned char i, j;
//    c -= 32;
//    x <<= 3;		
//    y <<= 1;		
//    for(j = 0; j < 2; j++)
//    {
//        moveto5110(x, (y + j));
//        for(i = 0; i < 8; i++)
//            writedat5110(font_4_5110_5x8[c][8 * j + i]);
//    }
}

//x:0~9
//y:0~2
void writestring5110(unsigned char x, unsigned char y,char *str)
{
    moveto5110(x,y);
    while(*str)
    {
        writechar5110(x, y, *str);
        str++;
    }
}

//x:0~9
//y:0~2
void writesfloat5110(unsigned char x, unsigned char y, int f)
{
    char tt[10];
    sprintf(tt,"%d",f);
    writestring5110(x,y,tt);
}
//end

#if (defined(KL2X))
void init_5110port_4_kl2x(void)
{
   gpio_init (PTB18, GPO, 1);
   gpio_init (PTB10, GPO, 1);
   gpio_init (PTB16, GPO, 1);
   gpio_init (PTC16, GPO, 1);
   gpio_init (PTC17, GPO, 1);
}

#endif

void lcd5110init(void)
{
#if (defined(KL2X))
    init_5110port_4_kl2x();
#endif
    RST5110_L; 
    RST5110_H;                  //Reset the 5110

    writecmd5110(0x21);		//工作模式, 水平寻址, 扩展指令
    writecmd5110(0x07);		//VLCD温度系数,设置0x04~0x07,越小越黑
    writecmd5110(0x13);	        //设置偏置系统(BSx) 1:48,设置为0x10~0x17	
    writecmd5110(128+65);       //设置电压VLCD = 3.06 + 0.06*Vop, 
                                //对比度调整,设置为0x80~0xff;128+(0~127)

    writecmd5110(0x20);		//工作模式, 水平寻址, 常规指令
    writecmd5110(0x0c);		//普通模式
    writecmd5110(0x80);	 	//起始页地址0
    writecmd5110(0x40);		//起始列地址0
    clear5110();		//清全屏
}

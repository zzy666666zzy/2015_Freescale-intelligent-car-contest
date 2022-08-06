#ifndef _LCD5110_H
#define _LCD5110_H

#define KL2X

#if (defined(STC51))
#include <reg51.h>
sbit RST = P0^3;     //LCD��λ��		//�͵�ƽ��λ
sbit CS5110  = P0^4;     //Ƭѡʹ��			//�͵�ƽ��Ч
sbit DC  = P0^5;     //����ָ����ƶ�	//�ߵ�ƽ���ݣ��͵�ƽָ��
sbit DIN = P0^6;     //������������		//�ȸߺ��
sbit CLK = P0^7;     //����ʱ��			//������д������
//sbit LCD_VCC = P2^5;
//sbit LED = P2^6;	//����ƿ��ƶ�      //�ߵ�ƽ��LED
//sbit LCD_GND = P2^7;
#elif (defined(KL2X))

#include "common.h"
#include "include.h"

#define RST5110_H			(PTB16_OUT=1)
#define RST5110_L			(PTB16_OUT=0)
#define CS5110_H			(PTB18_OUT=1)
#define CS5110_L			(PTB18_OUT=0)
#define DC5110_H			(PTC17_OUT=1)
#define DC5110_L			(PTC17_OUT=0)
#define DIN5110_H			(PTB10_OUT=1)
#define DIN5110_L			(PTB10_OUT=0)
#define CLK5110_H			(PTC16_OUT=1)
#define CLK5110_L			(PTC16_OUT=0)

#endif

#define writecmd5110(cmd)	writebyte5110(cmd, 0)	//д��ָ��
#define writedat5110(dat)	writebyte5110(dat, 1)	//д������

#define showBlank()		writecmd5110(0x08)		//��ʾ�հ�
#define showNormal()	writecmd5110(0x0c)		//������ʾ
#define showBlack()		writecmd5110(0x09)		//��ʾȫ��
#define showReverse() 	writecmd5110(0x0d)		//��ɫ��ʾ

extern void writebyte5110(unsigned char wByte, unsigned char datOrCmd);
extern void clear51105110();//����
extern void moveto5110(unsigned char x, unsigned char y);
extern void writechar5110(unsigned char x, unsigned char y, unsigned char c);
extern void writestring5110_big(unsigned char x, unsigned char y,char *str);
extern void writesfloat5110_big(unsigned char x, unsigned char y, int f);
extern void writestring5110(unsigned char x, unsigned char y,char *str);
extern void writesfloat5110(unsigned char x, unsigned char y, int f);
extern void lcd5110init(void);

#endif
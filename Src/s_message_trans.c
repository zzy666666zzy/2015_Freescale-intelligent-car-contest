#include "s_message_trans.h"
#include "h_nrf24l01.h"         //NRF24L01
#include "s_value_trans.h"
#include "s_global_value.h"

#include "control_direction.h"
#include "control_speed.h"
#include "control_up_right.h"


#include "common.h"
#include "include.h"
#include "ahjzu_include.h"

//When it sets to 1 it means you will receive a num
//1 for up-p
//2 for up-i
//3 for up-d
//4 for di-p
//5 for di-i
//6 dor di-d
//7 for sp-p
//8 for sp-i
//9 for sp-d

//10 for acc_val
//11 for gyr_val
//12 for DEFAULT_SPEED
//13 for angle-wanna
//14 for speed_normalization

//15 for direction_integral_limit       --direction -i
//16 for direction_threshold
unsigned char ready_4_num = 0;  
//End


void printf_2(unsigned char *s1 ,unsigned char *s2)
{
  trans_nrf_buf_2((unsigned char *)txbuf,s1,s2);
  printf((char *)txbuf);
}

void printf_3(unsigned char *s1,unsigned char *s2,unsigned char *s3)
{
  trans_nrf_buf_3((unsigned char *)txbuf,s1,s2,s3);
  printf((char *)txbuf);
}
//I use them blow
void printf_end(unsigned char *s1)
{
  trans_nrf_buf_2((unsigned char *)txbuf,s1,"\n");
  printf((char *)txbuf);
}

void printf_2_end(unsigned char *s1 ,unsigned char *s2)
{
  trans_nrf_buf_3((unsigned char *)txbuf,s1,s2,"\n");
  printf((char *)txbuf);
}

#define trans_by_wireless 			printf_end//printf//nrf_just_send
#define trans_by_wireless_2 		        printf_2_end//printf_2//nrf_just_send_2

void message_trans(void)
{
  nrf_just_send_2("ACC:",float_2_char(MMA7361,5));
  nrf_just_send_2("GY:",float_2_char(ENC03,5));
  
  nrf_just_send_2("ANG:",float_2_char(g_fCarAngle,5));
  
  nrf_just_send_2("ADL:",float_2_char(adc_once(ADC0_SE5a, ADC_12bit),5));////adc_once(ADC0_SE5a, ADC_12bit),5));
  nrf_just_send_2("ADR:",float_2_char(adc_once(ADC0_SE1, ADC_12bit),5));////adc_once(ADC0_SE1, ADC_12bit),5));
  
//  nrf_just_send_2("dir:",float_2_char(adc_once(ADC0_SE1, ADC_12bit),5));
  
  nrf_just_send_2("SPL:",float_2_char(encoder[0],5));
  nrf_just_send_2("SPR:",float_2_char(encoder[1],5));
  
//  nrf_just_send("tets.");
}

void mesage_get(void)
{
//  printf("Message to get.");
  //Clear all the values
//  float a = char_2_float(rxbuf);
//  printf(float_2_char(-12356.5,5));
//  printf("%d\n",(int)a);
//  if(rxbuf[0]== ':')// && rxbuf[5]=='8')
//  {
//    uart_putstr(UART0,rxbuf);
//  }
//  else
//  {
//    uart_putstr(UART0,"aald\n");
//  }
//--------------------------------------
  if(rxbuf[0] == ':')
  {
    if(ready_4_num == 0)
    {
      //You should tell computer what to set
      trans_by_wireless("You should set first.");
    }
    //Up-right
    else if(ready_4_num == 1)
    {
      angle_p = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(angle_p,5));
    }
    else if(ready_4_num == 2)
    {
      angle_i = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(angle_i,5));
    }
    else if(ready_4_num == 3)
    {
      angle_d = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(angle_d,5));
    }
    //Direction
    else if(ready_4_num == 4)
    {
      DIRECTION_CONTROL_P = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(DIRECTION_CONTROL_P,5));
    }
    else if(ready_4_num == 5)
    {
      DIRECTION_CONTROL_I = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(DIRECTION_CONTROL_I,5));
    }
    else if(ready_4_num == 6)
    {
      DIRECTION_CONTROL_D = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(DIRECTION_CONTROL_D,5));
    }
    //Speed
    else if(ready_4_num == 7)
    {
      speed_p = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(speed_p,5));
    }
    else if(ready_4_num == 8)
    {
      speed_i = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(speed_i,5));
    }
    else if(ready_4_num == 9)
    {
      speed_d = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(speed_d,5));
    }
    //acc
    else if(ready_4_num == 10)
    {
      Accel_val = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(Accel_val,5));
    }
    //gyro
    else if(ready_4_num == 11)
    {
      Gyro_val = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(Gyro_val,5));
    }
    //speed-wanna
    else if(ready_4_num == 12)
    {
      DEFAULT_SPEED = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(DEFAULT_SPEED,5));
    }
    //angle-wanna
    else if(ready_4_num == 13)
    {
      ang_wanna = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(ang_wanna,5));
    }
    //speed_normalization
    else if(ready_4_num == 14)
    {
      speed_normalization = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(speed_normalization,5));
    }
    //direction_integral_limit
    else if(ready_4_num == 15)
    {
      direction_integral_limit = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(direction_integral_limit,5));
    }
    //direction_threshold
    else if(ready_4_num == 16)
    {
      direction_threshold = char_2_float_with_char((unsigned char *)rxbuf,':','\n');
      trans_by_wireless_2("Set:",float_2_char(direction_threshold,5));
    }
  }
  else if(rxbuf[0] == 'A' && rxbuf[1] == 'L' && rxbuf[2] == 'L')
  {
    //up-right
    if(rxbuf[3] == 'U' && rxbuf[4] == 'R')
    {
      //Do something
      trans_by_wireless("Reset all UR");
      angle_p = default_angle_p;
      angle_i = default_angle_i;
      angle_d = default_angle_d;
    }
    //up-right
    else if(rxbuf[3] == 'D' && rxbuf[4] == 'I')
    {
      //Do something
      trans_by_wireless("Reset all DI");
      DIRECTION_CONTROL_P = DEFAULT_DIRECTION_CONTROL_P;
      DIRECTION_CONTROL_D = DEFAULT_DIRECTION_CONTROL_D;
      DIRECTION_CONTROL_I = DEFAULT_DIRECTION_CONTROL_I;
    }
    else if(rxbuf[3] == 'S' && rxbuf[4] == 'P')
    {
      trans_by_wireless("Reset all SP");
      speed_p = default_speed_p;
      speed_d = default_speed_d;
      speed_i = default_speed_i;
    }
    else if(rxbuf[3] == 'A' && rxbuf[4] == 'C' && rxbuf[5] == 'C')
    {
      trans_by_wireless_2("ACC:",float_2_char(Accel_val,5));
      ready_4_num = 10;
    }
    else if(rxbuf[3] == 'G' && rxbuf[4] == 'Y' && rxbuf[5] == 'R')
    {
      trans_by_wireless_2("ACC:",float_2_char(Gyro_val,5));
      ready_4_num = 11;
    }
    
  }
  //------------------------------------------
  //Set the up-right values
  else if(rxbuf[0] == 'U' && rxbuf[1] == 'R')
  {
     //P
    if(rxbuf[2] == 'P')
    {
//      trans_by_wireless("Ready for URp");
      trans_by_wireless_2("URP:",float_2_char(angle_p,5));
      ready_4_num = 1;
    }
    //I
    else if(rxbuf[2] == 'I')
    {
//      trans_by_wireless("Ready for URi");
      trans_by_wireless_2("URI:",float_2_char(angle_i,5));
      ready_4_num = 2;
    }
    //D
    else if(rxbuf[2] == 'D')
    {
//      trans_by_wireless("Ready for URd");
      trans_by_wireless_2("URD:",float_2_char(angle_d,5));
      ready_4_num = 3;
    }  
  }
  //------------------------------------------
  //Set the direction values
  else if(rxbuf[0] == 'D' && rxbuf[1] == 'I')
  {
     //P
    if(rxbuf[2] == 'P')
    {
//      trans_by_wireless("Ready for DIp");
      trans_by_wireless_2("DIP:",float_2_char(DIRECTION_CONTROL_P,5));
      ready_4_num = 4;
    }
    //I
    else if(rxbuf[2] == 'I')
    {
//      trans_by_wireless("Ready for DIi");
      trans_by_wireless_2("DII:",float_2_char(DIRECTION_CONTROL_I,5));
      ready_4_num = 5;
    }
    //D
    else if(rxbuf[2] == 'D')
    {
//      trans_by_wireless("Ready for DId");
      trans_by_wireless_2("DID:",float_2_char(DIRECTION_CONTROL_D,5));
      ready_4_num = 6;
    }  
    //direction_integral_limit
    else if(rxbuf[2] == 'L')
    {
//      trans_by_wireless("Ready for DId");
      trans_by_wireless_2("DIL:",float_2_char(direction_integral_limit,5));
      ready_4_num = 15;
    }  
    //direction_threshold
    else if(rxbuf[2] == 'T')
    {
//      trans_by_wireless("Ready for DId");
      trans_by_wireless_2("DIT:",float_2_char(direction_threshold,5));
      ready_4_num = 16;
    }  
  }
  //------------------------------------------
  //Set the speed values
  else if(rxbuf[0] == 'S' && rxbuf[1] == 'P')
  {
     //P
    if(rxbuf[2] == 'P')
    {
//      trans_by_wireless("Ready for SPp");
      trans_by_wireless_2("SPP:",float_2_char(speed_p,5));
      ready_4_num = 7;
    }
    //I
    else if(rxbuf[2] == 'I')
    {
//      trans_by_wireless("Ready for SPi");
      trans_by_wireless_2("SPI:",float_2_char(speed_i,5));
      ready_4_num = 8;
    }
    //D
    else if(rxbuf[2] == 'D')
    {
//      trans_by_wireless("Ready for SPd");
      trans_by_wireless_2("SPD:",float_2_char(speed_d,5));
      ready_4_num = 9;
    }  
    else if(rxbuf[2] == 'E' && rxbuf[3] == 'E' && rxbuf[4] == 'D' )
    {
      trans_by_wireless_2("Speed:",float_2_char(DEFAULT_SPEED,5));
      ready_4_num = 12;
    }
  }
//  else if(rxbuf[0] == 'S' && rxbuf[1] == 'P' && rxbuf[2] == 'E' && rxbuf[3] == 'E' && rxbuf[4] == 'D' )
//  {
//    trans_by_wireless_2("Speed:",float_2_char(speed_wanna,5));
//    ready_4_num = 12;
//  }
  else if(rxbuf[0] == 'A' && rxbuf[1] == 'N' && rxbuf[2] == 'G' && rxbuf[3] == 'L' && rxbuf[4] == 'E' )
  {
    trans_by_wireless_2("Angle:",float_2_char(ang_wanna,5));
    ready_4_num = 13;
  }
  else if(rxbuf[0] == 'S' && rxbuf[1] == 'P' && rxbuf[2] == 'K' )
  {
    trans_by_wireless_2("SPEEDK:",float_2_char(speed_normalization,5));
    ready_4_num = 14;
  }
  ///////////////////////////////////////////////
  else
  {
    trans_by_wireless("Wrong message");
  }
}

//#include <stdlib.h>

//Not support anymore
//2016.7.21 Thursday
////Get rid of the '\n'
//unsigned char * nrf_put_off_line_end(unsigned char *s)
//{
//  static unsigned char rx_temp[50];
//  int i = 0;
//  while((*s != '\n')&&(*s != '\0'))
//  {
//    rx_temp[i] = *s;
//    i ++;
//    s ++;
//  }
//  rx_temp[i] = '\0';
//  return rx_temp;
//}
//
//void nrf_rx_to_num(unsigned char *s)
//{
//  float f = 0.0;
//  
//  f = char_2_float(nrf_put_off_line_end(s));
//  printf(float_2_char(f,5));
////  unsigned char rx_num[50];
////  int i = 0;
////  float f = 0.0;
////  while(*s != '\0' || *s != '\n')
////  {
////    rx_num[i++] = *s; 
////    s++;
////  }
////  rx_num[i] = '\0';
////  f = char_2_float(rx_num);
//  //printf();
//}
//
//
//void due_message_get(void)
//{
////  nrf_rx_to_num(RxBuf);
//  nrf_rx_to_num(RxBuf);
////  printf(nrf_put_off_line_end(RxBuf));
//        
//        
////  char *s="1.1";
////  float f;
////  f=atof(s);
//  //sprintf(a,".2%f",b);
//  
//  
//  iniT_nrf_buf(RxBuf);
////  nrf_just_send(a);
////  int num=atoi(tem);
////  printf("num:%d\n",num);
//}

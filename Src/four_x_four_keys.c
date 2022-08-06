#include "four_x_four_keys.h"


void keys_4x4_delay(uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

#if (defined(KL2X))
void init_4x4_port_4_kl2x(void)
{
  gpio_init(PTB0,GPO,1);
  gpio_init(PTB2,GPO,1);
  gpio_init(PTB7,GPO,1);
  gpio_init(PTB9,GPO,1);
  
  gpio_init(PTB11,GPI,0); 
  port_init_NoALT(PTB11,PULLUP);
  gpio_init(PTB17,GPI,0); 
  port_init_NoALT(PTB17,PULLUP);
  gpio_init(PTB19,GPI,0); 
  port_init_NoALT(PTB19,PULLUP);
  gpio_init(PTB21,GPI,0); 
  port_init_NoALT(PTB21,PULLUP);
//  //Init port's clock
//  SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;
//  //Init ports
//  PORTB_PCR1 = PORT_PCR_MUX(1);
//  PORTB_PCR3 = PORT_PCR_MUX(1);
//  PORTB_PCR8 = PORT_PCR_MUX(1);
//  PORTB_PCR10 = PORT_PCR_MUX(1);
//  PORTB_PCR16 = PORT_PCR_MUX(1);
//  PORTB_PCR18 = PORT_PCR_MUX(1);
//  PORTB_PCR20 = PORT_PCR_MUX(1);
//  PORTB_PCR22 = PORT_PCR_MUX(1);
//  
//  
//  //Set dir
//  LINE1_OUT;
//  LINE2_OUT;
//  LINE3_OUT;
//  LINE4_OUT;
//  
//  LINE5_IN;
//  LINE6_IN;
//  LINE7_IN;
//  LINE8_IN;
//  
////  port_init(PTB16,PULLDOWN);
////  port_init(PTB18,PULLDOWN);
////  port_init(PTB20,PULLDOWN);
////  port_init(PTB22,PULLDOWN);
//  
//  LINE1_H;
//  LINE2_H;
//  LINE3_H;
//  LINE4_H;
}
#endif
void init_4x4_port(void)
{
#if (defined(KL2X))
  init_4x4_port_4_kl2x();
#endif
}

int keys_scan_4x4(void)
{
  char key_num;
  //1
  LINE1_L;
  LINE2_H;
  LINE3_H;
  LINE4_H;
  if(LINE5_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE5_READ == 0)
    {
      key_num = 1;//'1';
      return key_num;
    }
  }
  if(LINE6_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE6_READ == 0)
    {
      key_num = 2;//'2';
      return key_num;
    }
  }
  if(LINE7_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE7_READ == 0)
    {
      key_num = 3;//'3';
      return key_num;
    }
  }
  if(LINE8_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE8_READ == 0)
    {
      key_num = 4;//'A';
      return key_num;
    }
  }
  //end 1
  ////////////////////////////////
  //2
  LINE1_H;
  LINE2_L;
  LINE3_H;
  LINE4_H;
  if(LINE5_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE5_READ == 0)
    {
      key_num = 5;//'4';
      return key_num;
    }
  }
  if(LINE6_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE6_READ == 0)
    {
      key_num = 6;//'5';
      return key_num;
    }
  }
  if(LINE7_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE7_READ == 0)
    {
      key_num = 7;//'6';
      return key_num;
    }
  }
  if(LINE8_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE8_READ == 0)
    {
      key_num = 8;//'B';
      return key_num;
    }
  }
  //end 2
  ////////////////////////////////
  //3
  LINE1_H;
  LINE2_H;
  LINE3_L;
  LINE4_H;
  if(LINE5_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE5_READ == 0)
    {
      key_num = 9;//'7';
      return key_num;
    }
  }
  if(LINE6_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE6_READ == 0)
    {
      key_num = 10;//'8';
      return key_num;
    }
  }
  if(LINE7_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE7_READ == 0)
    {
      key_num = 11;//'9';
      return key_num;
    }
  }
  if(LINE8_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE8_READ == 0)
    {
      key_num = 12;//'C';
      return key_num;
    }
  }
  //end 3
  /////////////////////////////
  //4
  LINE1_H;
  LINE2_H;
  LINE3_H;
  LINE4_L;
  if(LINE5_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE5_READ == 0)
    {
      key_num = 13;//'*';
//      printf("++++++++++++++++++");
      return key_num;
    }
  }
  if(LINE6_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE6_READ == 0)
    {
      key_num = 14;//'0';
      return key_num;
    }
  }
  if(LINE7_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE7_READ == 0)
    {
      key_num = 15;//'#';
      return key_num;
    }
  }
  if(LINE8_READ == 0)
  {
    keys_4x4_delay(200000);
    if(LINE8_READ == 0)
    {
      key_num = 16;//'D';
      return key_num;
    }
  }
  //end 4
  return 0;
}



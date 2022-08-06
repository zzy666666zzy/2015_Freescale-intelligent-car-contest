//Here,I will put all global value
#include "s_global_value.h"

float global_temp_values = 0;

float ang_wanna = 0;//-100;//10;//
//float speed_wanna = 100;//1700;//3000;  //The speed you need

//speed
float direction_threshold = DEFAULT_DIRECTION_THRESHOLD;
float DEFAULT_SPEED = SETTING_SPEED;

char rxbuf[rxbuf_len];
char txbuf[txbuf_len];
char enable_get_message = 0;    //Default 0 for disable and 1 for enable message_deal
void init_uart0_rxbuf(void)
{
  unsigned char i = 0;
  for(;i < rxbuf_len && rxbuf[i] != '\0';i++)
  {
    rxbuf[i] = '\0';
  }
}
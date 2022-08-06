#include "control_direction.h"
#include "common.h"
#include "include.h"
#include "ahjzu_include.h"
#include "s_global_value.h"


#define GET_AD_E_TIME   20

//PD
float DIRECTION_CONTROL_P = DEFAULT_DIRECTION_CONTROL_P;//550;//150
float DIRECTION_CONTROL_D = DEFAULT_DIRECTION_CONTROL_D;//-0.1;
float DIRECTION_CONTROL_I = DEFAULT_DIRECTION_CONTROL_I;//0.1;
float Gyro_val_in_direction = 0;//

float direction_integral = 0;

float direction_integral_limit = 750;

//Global value
float direction_base_last,direction_base;
float direction_out;

//The count time of get ad_e
float DIRECTION_CONTROL_COUNT = 3;
float LEFT_RIGHT_MINIMUM = 10;          //The min add value of left and right
//AD values of electrically-induced
int AD_EL1 = 0,AD_ER1 = 0;
int direction_counter = 0;
float nleft,nright;

//speed limit define
float direction_define_4_speed = 0;
float direction_define_4_speed_last = 0;


void limit_direction_integral(void)
{
	direction_integral = (direction_integral>direction_integral_limit)?direction_integral_limit:direction_integral;
	direction_integral = (direction_integral<(-direction_integral_limit))?(-direction_integral_limit):direction_integral;
}

void init_ad_x_gyro(void)
{
  int i = 0;
  for(i = 0;i < 20;i++)
  {
    Gyro_val_in_direction += adc_once(ADC0_SE2, ADC_12bit);
  }
  Gyro_val_in_direction /= 20;
}
//////////////////////////////////////////////
void get_electrically_ads(void)
{
  int i =0;
  for(i = 0;i < GET_AD_E_TIME;i++)
  {
    AD_ER1 += adc_once(ADC0_SE5a, ADC_12bit);
    AD_EL1 += adc_once(ADC0_SE1, ADC_12bit); 
  }
  AD_ER1 /= GET_AD_E_TIME;
  AD_EL1 /= GET_AD_E_TIME;
}

void control_direction(void)
{

  float fLeftRightAdd,fLeftRightSub;
  int i;
  float ad_temp;
  float ad_p,ad_i;
  
  nleft =  AD_EL1 / DIRECTION_CONTROL_COUNT;                     //Warning!!
  nright = AD_ER1 / DIRECTION_CONTROL_COUNT;                    //Warning!!
  
  AD_ER1 = 0;
  AD_EL1 = 0;
  
  fLeftRightAdd = nleft + nright;
  fLeftRightSub = nleft - nright;
  
  //speed limit
  direction_define_4_speed_last = direction_define_4_speed;
  direction_define_4_speed = fLeftRightSub / fLeftRightAdd;
  
  direction_base_last = direction_base;
  
  if(fLeftRightAdd < LEFT_RIGHT_MINIMUM)
  {
    
    direction_base = 0;
  }
  else
  {
    ad_p = fLeftRightSub * DIRECTION_CONTROL_P /fLeftRightAdd;
    ad_i = fLeftRightSub * DIRECTION_CONTROL_I /fLeftRightAdd;
    direction_integral += ad_i;
    direction_base = ad_p + ad_i;
//    direction_base = fLeftRightSub * DIRECTION_CONTROL_P /fLeftRightAdd; 
    for(i = 0;i < 20;i++)
    {
      ad_temp += adc_once(ADC0_SE2, ADC_12bit);     
    }
    ad_temp /= 20;
    
    direction_base += (ad_temp - Gyro_val_in_direction)*DIRECTION_CONTROL_D;

  }
}

void get_direction_out(void)
{
  float out_sub;
//  direction_counter++;
  out_sub = direction_base - direction_base_last;
  direction_out = out_sub * (direction_counter + 1.0)/2 + direction_base_last;
  direction_counter = 0;
}
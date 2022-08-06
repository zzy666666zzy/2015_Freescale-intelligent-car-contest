#include "control_speed.h"
#include "calculate_encoder.h"
#include "s_global_value.h"
#include "control_direction.h"

//The normalization of speed,but you can change
//the speed_out by change PID values.
float speed_normalization = 2;

//PID
float speed_p = default_speed_p;
float speed_d = default_speed_d;
float speed_i = default_speed_i;



float speed_integral = 0;	//To save the 'I' value
float speed_integral_limit = 750;

//must be global value
float speed_base,speed_base_old;
float speed_out;

float speed_counter = 0;

float speed_calcu = 0;
float speed_wanna = SETTING_SPEED;//1700;//3000;  //The speed you need

float temp_speed = 0;



void limit_speed_integral(void)
{
	speed_integral = (speed_integral>speed_integral_limit)?speed_integral_limit:speed_integral;
	speed_integral = (speed_integral<(-speed_integral_limit))?(-speed_integral_limit):speed_integral;
}
/*
void speed_calculate_base(void)
{

  float temp_p = 0,temp_i = 0;
  float temp_speed = 0;
  get_encoder();
  speed_calcu = (encoder[0] + encoder[1])/2;
  //Reset the encoder value
//  encoder[0] = 0;
//  encoder[1] = 0;
  
  speed_calcu *= speed_normalization;
  
  temp_speed = speed_wanna - speed_calcu;
  
//  temp_p = temp_speed * speed_p;
//  temp_i = temp_speed * speed_i;
//
//  //Mayne you need to limit this num
////  speed_integral += temp_i;
//  /////////////////////////////
//
//  speed_base_old = speed_base;
  speed_base = temp_speed * speed_p ;//temp_p + speed_integral;

  
}

void get_speed_out(void)
{
//  float s_value;
//  s_value = speed_base - speed_base_old;
  speed_out = speed_base ;//= s_value * (speed_counter + 1)/2 + speed_base_old;
  speed_counter = 0;
}

*/

void get_speed_wanna_out(void)
{
  if(direction_define_4_speed > direction_threshold)//&& (direction_define_4_speed_last < direction_threshold))
  {
    speed_wanna = DEFAULT_SPEED;
//    if(speed_calcu > DEFAULT_SPEED)
//    {
//      speed_wanna *= DEFAULT_SPEED*0.8;
//    }
  }
  else
  {
    speed_wanna = DEFAULT_SPEED * 0.8;
  }
}

void speed_calculate_base(void)
{

  float temp_p = 0,temp_i = 0;
  
  get_encoder();
  speed_calcu = (encoder[0] + encoder[1])/2;
  //Reset the encoder value
//  encoder[0] = 0;
//  encoder[1] = 0;
  
  speed_calcu *= speed_normalization;
  
  //Get speed wanna
//  get_speed_wanna_out();
  speed_wanna = DEFAULT_SPEED;
  
  temp_speed = speed_wanna - speed_calcu;
  
  temp_p = temp_speed * speed_p;
  temp_i = temp_speed * speed_i;

  //Mayne you need to limit this num
  speed_integral += temp_i;
  limit_speed_integral();
  /////////////////////////////

  speed_base_old = speed_base;
  speed_base = temp_p + speed_integral;

  
}

void get_speed_out(void)
{
  float s_value;
  s_value = speed_base - speed_base_old;
  
  speed_out = s_value * (speed_counter + 1)/2 + speed_base_old;
  
//  global_temp_values = speed_out;
  
  speed_counter = 0;
}

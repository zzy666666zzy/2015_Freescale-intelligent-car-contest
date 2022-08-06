#include "control_up_right.h"
#include "ahjzu_include.h"
#include "s_global_value.h"
#include "common.h"
#include "include.h"

#define GET_STATE_TIME          20
#define START_INIT_TIME         100
/////////////////////////////////////////////////
//The value may change by user
float Gyro_val = 0;//2020;//2200;          //The middle value of gyro
float Accel_val = 0;//02700;         //The middle value of accel

int GRAVITY_ADJUST_TIME_CONSTANT = 4;   //The filter's time coefficient
float GYRO_DT = 0.0025;

//PID
float angle_p = default_angle_p;
float angle_i = default_angle_i;//0.5;
float angle_d = default_angle_d;//-0.7;

/////////////////////////////////////////////////
//State value
volatile int MMA7361 = 0,ENC03=0;
float g_fGyroscopeAngleIntegral = 0;
float g_fCarAngle = 0;
float g_fCarAngle_middle = 7600;
//Must be a global value for this project
float angle_base = 0;
float angle_base_1 = 0;
float Gyro_Now,Gyro_Now_back;
float Accel_Now;
float Gyro_Now_1,Gyro_Now_back_1;
float Accel_Now_1;
volatile int MMA7361_1 = 0,ENC03_1=0;

void init_gyro_and_accel(void)
{
  int i = 0;
  for(i = 0;i < START_INIT_TIME;i++)
  {
    ENC03 += adc_once(ADC0_DM0, ADC_12bit);
    MMA7361+= adc_once(ADC0_SE3, ADC_12bit);
  }
  ENC03 /= START_INIT_TIME;
  Gyro_val = Default_Gyro;//ENC03;
  MMA7361 /= START_INIT_TIME;
  Accel_val = Default_Accel;//MMA7361;
//  global_temp_values = Accel_val;
}
/////////////////////////////////////////////////
//Filter of Qinghua 
void qinghua_filter(float gyro_a,float gyro)
{
  float fDeltaValue;
  g_fCarAngle = g_fGyroscopeAngleIntegral;      //Get the final angle
  fDeltaValue = (gyro_a - g_fCarAngle)/GRAVITY_ADJUST_TIME_CONSTANT;
  g_fGyroscopeAngleIntegral += (gyro + fDeltaValue)*GYRO_DT;    //
}
//Get the up-right base value
void get_state_analog_mode(void)
{
  int i = 0;
  
  //Get the values
  for(i = 0;i < GET_STATE_TIME;i++)
  {
    ENC03 += adc_once(ADC0_DM0, ADC_12bit);
    MMA7361+= adc_once(ADC0_SE3, ADC_12bit);
    ENC03_1+= adc_once(ADC0_SE11, ADC_12bit);
    MMA7361_1+= adc_once(ADC0_SE9, ADC_12bit);
  }
  ENC03 /= GET_STATE_TIME;
  MMA7361 /= GET_STATE_TIME;
  ENC03_1 /= GET_STATE_TIME;
  MMA7361_1 /= GET_STATE_TIME;
  //End get values
  //--------------------------------------
  //Values' normalization
  //Angle acceleration
  Gyro_Now_1 = (Gyro_val - ENC03_1)*(-0.20);
  Gyro_Now_back_1 = Gyro_Now_1;
  
  Gyro_Now = (Gyro_val - ENC03)*(-0.20);
  Gyro_Now_back = Gyro_Now;
  //Acceleration
  Accel_Now = (Accel_val - MMA7361)*(0.75);
   Accel_Now_1 = (Accel_val - MMA7361_1)*(0.75);
  //End normalization
  //--------------------------------------
  //Filter
  qinghua_filter(Accel_Now,Gyro_Now);
  qinghua_filter(Accel_Now_1,Gyro_Now_1);
  angle_base = g_fCarAngle*angle_p + Gyro_Now*angle_d + (Gyro_Now - Gyro_Now_back)*angle_i ;
  angle_base_1 = g_fCarAngle*angle_p + Gyro_Now_1*angle_d + (Gyro_Now_1 - Gyro_Now_back_1)*angle_i ;
}

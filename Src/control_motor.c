#include "control_motor.h"
#include "common.h"
#include "include.h"
#include "h_nrf24l01.h"

float PWM_LIMIT = 4500;
float O_PWM_LIMIT = -4500;

extern float angle_base;
extern float angle_base_1;
extern float direction_out;
extern float speed_out;

unsigned char motor_state_l = 1;
unsigned char motor_state_r = 1;
void motor_out(void)
{
  float speed_f1,speed_b1,speed_f2,speed_b2;
//  float speed_temp;
//  speed_f1 = angle_base + direction_out;
//  speed_b1 = angle_base - direction_out;
  speed_f1 =200 + angle_base ;
  speed_b1 =200 - angle_base ;
  speed_f2 =200 + angle_base_1;
  speed_b2 =200 - angle_base_1;
//  speed_f1 =   speed_out*motor_state_l;
//  speed_b1 =   speed_out*motor_state_r;
//  speed_f1 = -speed_out;
//  speed_b1 = -speed_out;
  //PWM limit
  if(speed_f1 > PWM_LIMIT)
  {
    speed_f1 = PWM_LIMIT;
  }

//  if(speed_f1 < -PWM_LIMIT)
//  {
//    speed_f1 = -PWM_LIMIT;
//
//  }
  
  //
  if(speed_b1 > PWM_LIMIT)
  {
    speed_b1 = PWM_LIMIT;
    
  }
  
//  if(speed_b1 < -PWM_LIMIT)
//  {
//    speed_b1 = -PWM_LIMIT;
//    
//  }
 
  //Real control
  if(speed_f1 >= 0)    //angle大于0，向前，小于0，向后
  {
      motor_state_l = 1;
      tpm_pwm_duty(TPM0,TPM_CH1,0);
      tpm_pwm_duty(TPM0,TPM_CH0,(int)speed_f1);    //加入死区电压
  }
  
    if(speed_b1 >= 0)    
  {
      motor_state_l = 1;
      tpm_pwm_duty(TPM0,TPM_CH1,0);
      tpm_pwm_duty(TPM0,TPM_CH1,(int)speed_b1);    //加入死区电压
  }
  
//  else
//  {
//       motor_state_l = -1;
//       tpm_pwm_duty(TPM0,TPM_CH0,0);
//       tpm_pwm_duty(TPM0,TPM_CH1,(int)-speed_f1);    //加入死区电压
//  }

  if(speed_f2 >= 0)    //angle大于0，向前，小于0，向后
  {
      motor_state_r = 1;
      tpm_pwm_duty(TPM0,TPM_CH2,0);
      tpm_pwm_duty(TPM0,TPM_CH2,(int)speed_f2);    //加入死区电压
  }
  
    if(speed_b2 >= 0)    
  {
      motor_state_l = 1;
      tpm_pwm_duty(TPM0,TPM_CH1,0);
      tpm_pwm_duty(TPM0,TPM_CH3,(int)speed_b2);    //加入死区电压
  }
//  else
//  {
//      motor_state_r = -1;
//     tpm_pwm_duty(TPM0,TPM_CH3,0);
//     tpm_pwm_duty(TPM0,TPM_CH2,(int)(-speed_b1));   //加入死区电压
//  }
  
//  if(1)//speed_f1 >= 0)    //angle大于0，向前，小于0，向后
//  {
//      motor_state_l = 1;
//      tpm_pwm_duty(TPM0,TPM_CH1,0);
//      tpm_pwm_duty(TPM0,TPM_CH0,(int)PWM_LIMIT);    //加入死区电压
//  }
//  else
//  {
//       motor_state_l = -1;
//       tpm_pwm_duty(TPM0,TPM_CH0,0);
//       tpm_pwm_duty(TPM0,TPM_CH1,(int)PWM_LIMIT);    //加入死区电压
//  }
//
//  if(1)//speed_b1 >= 0)    //angle大于0，向前，小于0，向后
//  {
//      motor_state_r = 1;
//      tpm_pwm_duty(TPM0,TPM_CH2,0);
//      tpm_pwm_duty(TPM0,TPM_CH3,(int)PWM_LIMIT);    //加入死区电压
//  }
//  else
//  {
//      motor_state_r = -1;
//     tpm_pwm_duty(TPM0,TPM_CH3,0);
//     tpm_pwm_duty(TPM0,TPM_CH2,(int)(PWM_LIMIT));   //加入死区电压
//  }
}
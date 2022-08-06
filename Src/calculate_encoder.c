#include "calculate_encoder.h"
#include "common.h"
#include "include.h"

unsigned int encoder[2] = {0,0};

void init_encoder(void)
{
//  //初始化 PWM，管脚是 TPM0_CH0_PIN
//  tpm_pwm_init(TPM1, TPM_CH0,1000,50);
  //初始化 TPM2 为脉冲累加，输入管脚为 TPM_CLKIN0_PIN ，分频系数为 1
  tpm_pulse_init(TPM1,TPM_CLKIN0,TPM_PS_1);     //PTC12
  //初始化 TPM2 为脉冲累加，输入管脚为 TPM_CLKIN0_PIN ，分频系数为 1
  tpm_pulse_init(TPM2,TPM_CLKIN1,TPM_PS_1); //PTC13        
}

void get_encoder(void)
{
//  encoder_1 = 
  encoder[0] = tpm_pulse_get(TPM1);
  encoder[1] = tpm_pulse_get(TPM2);
  tpm_pulse_clean(TPM1); 
  tpm_pulse_clean(TPM2); 
}

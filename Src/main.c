//This is the MAIN file edited by AHJZU,Elctronic Team
//Author: ZangZhenYa,Hemingway
//Time: 2016.7.9 Saturday

#include "common.h"
#include "include.h"

#include "ahjzu_include.h"

float main_temp = 0;

//Keys scan
void key_dule(void)
{
  char key = 0;
  key = keys_scan_4x4();
  switch(key)
  {
    case 1:
      Accel_val += 1;
      break;
    case 2:
      Accel_val -= 1;
      break;
    case 3 :
      Accel_val += 5;
      break;
    case 4:
      Accel_val -= 5;
    case 5:
      Accel_val += 10;
      break;
    case 6:
      Accel_val -= 10;
    case 7:
      Accel_val += 100;
      break;
    case 8:
      Accel_val -= 100;
      break;
    default:
      break;
  }
}
//System init
void system_init(void)
{
  DisableInterrupts;
  /////////////////////////////////////////
  //Init NRF24l01
  init_24l01();
#ifndef DEBUG_MODE
  while(nrf24l01_check())
  {
    printf("NRF24L01 check failed\n");
    DELAY_MS(500);
    init_nrf();
  }
#endif
  ////////////////////////////////////////
  //KEYs Scan
  init_4x4_port();
  /////////////////////////////////////////
  //Init the D4 --LED on the board
  //And set it off first
  gpio_init (PTB23, GPO,1);
  //////////////////////////////////////////
  //TPM module init
  //Init them to creat PWM
  tpm_pwm_init(TPM0,TPM_CH0,10000,1000);
  tpm_pwm_init(TPM0,TPM_CH1,10000,2000);
  tpm_pwm_init(TPM0,TPM_CH2,10000,3000);
  tpm_pwm_init(TPM0,TPM_CH3,10000,4000);
  //Init them to calculate the speed
  //Not support,because I wanna to try the DMA mode
//  tpm_pulse_init(TPM1, TPM_CLKIN1,TPM_PS_2);
//  tpm_pulse_init(TPM2, TPM_CLKIN0,TPM_PS_2);
  //Init Encoder count
  init_encoder();
  //////////////////////////////////////////
  //Init the ADC module
  //Posture
  adc_init(ADC0_SE3);//PTE22         MMA7361 Y轴
  adc_init(ADC0_DM0); //PTE21        ENC03角速度 
  adc_init(ADC0_SE2); //PTE18        转动陀螺仪时变量
  //L
  adc_init(ADC0_SE5a);   // PTE17 电磁采集  
  adc_init(ADC0_SE1);   // PTE16 电磁采集
  adc_init(ADC0_SE8);
  adc_init(ADC0_SE11);
  //////////////////////////////////////////
  //Init LCD
  lcd5110init();
  //////////////////////////////////////////
  init_gyro_and_accel();
  init_ad_x_gyro();
  //////////////////////////////////////////
  set_vector_handler(UART0_VECTORn,uart0_handler);
  set_irq_priority(UART0_IRQn,0);
  uart_rx_irq_en (UART0); 
  //////////////////////////////////////////
  //Init PIT
  pit_init_ms(PIT0, 2);                                //初始化PIT0，定时时间为： 1000ms
  set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);       //设置PIT0的中断服务函数为 PIT_IRQHandler
  set_irq_priority(PIT_IRQn,1);
  enable_irq (PIT_IRQn);                                 //使能PIT0中断
  //////////////////////////////////////////
  //LPTM
//  lptmr_timing_ms(10);                                  //初始化LPTMR，定时时间为： 1000ms
//  set_vector_handler(LPTMR_VECTORn ,LPTMR_IRQHandler);    //设置LPTMR的中断服务函数为 LPTMR_IRQHandler
//  set_irq_priority(LPTMR_IRQn,3);
//  enable_irq (LPTMR_IRQn);
  //////////////////////////////////////////
  //Init PIT
  pit_init_ms(PIT0, 2);                                //初始化PIT0，定时时间为： 1000ms
  set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);       //设置PIT0的中断服务函数为 PIT_IRQHandler
  enable_irq (PIT_IRQn);                                 //使能PIT0中断
  //////////////////////////////////////////
  
//  //UART0 receive interrupt
//  set_vector_handler(UART0_VECTORn,uart0_handler);
//  uart_rx_irq_en (UART0); 
  EnableInterrupts;
}

int main(void)
{

 int main_count = 0;
  
  printf("Starting the cars init function.\n");
  system_init();
  printf("Success,let's go,go,go!\n");
  
//  writestring5110(0,0,"AHJZU");
//  writestring5110(0,1,"BMQ1:");
//  writestring5110(0,2,"BMQ1:");
//  due_message_get();
  

  while(1)
  {
//    if(enable_get_message == 1)
//    {
//      enable_get_message = 0;
//      mesage_get();
//    }
//    nrf_just_send_2("ACC:",float_2_char(MMA7361,5));
//    nrf_just_send_2("GY:",float_2_char(ENC03,5));
//    
//    nrf_just_send_2("ANG:",float_2_char(g_fCarAngle,5));
//    
//    nrf_just_send_2("ADL:",float_2_char(adc_once(ADC0_SE5a, ADC_12bit),5));////adc_once(ADC0_SE5a, ADC_12bit),5));
//    nrf_just_send_2("ADR:",float_2_char(adc_once(ADC0_SE1, ADC_12bit),5));////adc_once(ADC0_SE1, ADC_12bit),5));
    
//    nrf_just_send_2("dir:",float_2_char(adc_once(ADC0_SE1, ADC_12bit),5));
    
//    direction_integral = 0;
//    nrf_just_send_2("dil:",float_2_char(direction_integral,5));
    
    
//    nrf_just_send_2("dil:",float_2_char(speed_calcu,5));
//    nrf_just_send_2("dil:",float_2_char(direction_integral,5));
//    
//    
//    nrf_just_send_2("SPL:",float_2_char(encoder[0],5));
//    nrf_just_send_2("SPR:",float_2_char(encoder[1],5));
    
    
    
    
//    nrf_just_send_2("global_value:",float_2_char(global_temp_values,5));
//    nrf_just_send_2("dir:",float_2_char(direction_base,5));
//    nrf_just_send_2("AHSUB:",float_2_char(adc_once(ADC0_SE5a, ADC_12bit) - adc_once(ADC0_SE1, ADC_12bit),5));
//    if(motor_state_l == '-')
//    {
//      nrf_just_send("Zheng");
//    }
//    else
//    {
//      nrf_just_send("Fan");
//    }
    
//    nrf_just_send_2(motor_state_l,motor_state_r);//g_fCarAngle,5));
//    if(!(main_count % 10))
//    {
//      nrf_just_send_2("ACC:",float_2_char(adc_once(ADC0_SE3, ADC_12bit),8));
//    }
////    if(main_count % 15)
////    {
////      
////      if(nrf_just_get())
////      {
////        nrf_just_send("IGT");
////        printf(RxBuf);
////        iniT_nrf_buf(RxBuf);
////        //due_message_get();
////      }
////      nrf_just_send("This is a test");
////    
////    }
////    else
////    {
//////      printf("!\n");
////      nrf_just_send_2("ACC:",float_2_char(adc_once(ADC0_SE3, ADC_12bit),8));
////    }
//    if((main_count ++) > 200)
//    {
//      main_count = 0;
//    }
    
    //nrf_just_send("ACC:");
    //nrf_just_send(float_2_char(adc_once(ADC0_SE3, ADC_12bit),8));
    //nrf_just_send("5");
//    DELAY_MS(5);
//    if(nrf_just_get())
//    {
//      printf(RxBuf);
//      //due_message_get();
//    }
    
//    nrf_just_send("This is a test!\n");
//    if(main_temp < MMA7361)
//    {
//      main_temp = MMA7361;
//    }
//    tpm_pwm_duty(TPM0,TPM_CH1,500);
//    writesfloat5110(0,0,50);

//    if(nrf_just_get())
//    {
////            printf("Get get\n");
//      printf(RxBuf);
//    }
//    showBlack();
//    get_encoder();
//    writestring5110(0,1,"      ");
//    writesfloat5110(0,1,encoder[0]);
//    writestring5110(0,2,"      ");
//    writesfloat5110(0,2,encoder[1]);
//    writestring5110(0,3,"      ");
//    writesfloat5110(0,3,(int)MMA7361);
//    writestring5110(0,4,"      ");
//    writesfloat5110(0,4,(int)Accel_val);
//    key_dule();
//    printf("angle:%d\n",(int)angle_base);
//    printf("angel_base:%d\n",(int)angle_base);                     //打印计数值
//    printf("key:%d\n",keys_scan_4x4());
//    if(LINE5_READ)
//    {
//      printf("hh\n");
//    }
//    else
//    {
//      printf("ll\n");
//    }
//    printf("值:%d\n",(int)main_temp);                     //打印计数值
//    DELAY_MS(1000); 
  }
}

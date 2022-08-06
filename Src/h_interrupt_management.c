#include "h_interrupt_management.h"
#include "common.h"
#include "include.h"

#include "ahjzu_include.h"

//PIT module
int PIT0_counter = 0;

void uart0_handler(void)
{  
    uart_rx_irq_dis(UART0);
    if(uart_query    (UART0) == 1)   //接收数据寄存器满
    {
        //用户需要处理接收数据
        uart_querystr(UART0,rxbuf,rxbuf_len);
//        enable_get_message = 0;
//        nrf_just_send_2("rxbuf:",rxbuf);
//        if(rxbuf[0]== '5' && rxbuf[5]=='8')
//        {
//          uart_putstr(UART0,rxbuf);
//        }
//        else
//        {
//          uart_putstr(UART0,"aald\n");
//        }
        mesage_get();
        init_uart0_rxbuf();
////        uart_getchar   (UART0, &ch);                    //无限等待接受1个字节
////        uart_putchar   (UART0 , ch);                    //发送字符串
    }
    uart_rx_irq_en (UART0);
//      gpio_turn(PTB23); 
//    uart_rx_irq_dis(UART0);
//    if(uart_query    (UART0) == 1)   //接收数据寄存器满
//    {
//        //用户需要处理接收数据
//        uart_querystr(UART0,rxbuf,rxbuf_len);
////        enable_get_message = 1;
//        if(rxbuf[0]== '5' && rxbuf[5]=='8')
//        {
//          uart_putstr(UART0,rxbuf);
//        }
//        else
//        {
//          uart_putstr(UART0,"aald\n");
//        }
////        mesage_get();
//        init_uart0_rxbuf();
//////        uart_getchar   (UART0, &ch);                    //无限等待接受1个字节
//////        uart_putchar   (UART0 , ch);                    //发送字符串
//    }
//    uart_rx_irq_en (UART0); 
}

void PIT_IRQHandler(void)
{
  static int pit0_time = 0;
  if(PIT_TFLG(PIT0) == 1 )       
  {  
    //Flag add to set the values more averagable
    speed_counter ++;
    direction_counter++;
    //////////////////////////////
    
    //Set different flag to deal with different situation
    PIT0_counter++;
    //////////////////////////////
    if(!(PIT0_counter%1))
    {
      get_state_analog_mode();
    }
    if(!(PIT0_counter%2))
    {
      get_electrically_ads();

    }
  //  speed_out = 0;
    if(!(PIT0_counter%4))
    {

    }
    motor_out();
  //  if(!(PIT0_counter%5))
  //  {
  //      if(nrf_just_get())
  //      {
  //        nrf_just_send("IGT");
  //        printf(RxBuf);
  //        iniT_nrf_buf(RxBuf);
  //        //due_message_get();
  //      }
  //  }
    
    if(PIT0_counter >= 400)
    {
      PIT0_counter = 0;
    }
    if(pit0_time++ >= 200)
    {
      pit0_time = 0;
      //Turn over the LED on the board
      gpio_turn(PTB23); 
    }
//    gpio_turn(PTB23); 

      PIT_Flag_Clear(PIT0);       
  }
//  PIT_Flag_Clear(PIT0);
//  static int pit0_time = 0;
//  PIT_Flag_Clear(PIT0);
//
//  //Flag add to set the values more averagable
//  speed_counter ++;
//  direction_counter++;
//  //////////////////////////////
//  
//  //Set different flag to deal with different situation
//  PIT0_counter++;
//  //////////////////////////////
//  if(!(PIT0_counter%1))
//  {
//    get_state_analog_mode();
//  }
//  if(!(PIT0_counter%2))
//  {
//    get_electrically_ads();
//    control_direction();
//    get_direction_out();
//  }
////  speed_out = 0;
//  if(!(PIT0_counter%4))
//  {
//    speed_calculate_base();
//    get_speed_out();
//  }
//  motor_out();
////  if(!(PIT0_counter%5))
////  {
////      if(nrf_just_get())
////      {
////        nrf_just_send("IGT");
////        printf(RxBuf);
////        iniT_nrf_buf(RxBuf);
////        //due_message_get();
////      }
////  }
//  
//  if(PIT0_counter >= 400)
//  {
//    PIT0_counter = 0;
//  }
//  if(pit0_time++ >= 200)
//  {
//    pit0_time = 0;
//    //Turn over the LED on the board
//    gpio_turn(PTB23); 
//  }
  
}
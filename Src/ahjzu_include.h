#ifndef _AHJZU_INCLUDE_H_
#define _AHJZU_INCLUDE_H_

#include "four_x_four_keys.h"   //4x4 keys
#include "s_global_value.h"     //Global values put in here
#include "lcd5110.h"            //LCD5110      
#include "h_interrupt_management.h"     //Interrupts collection
#include "calculate_encoder.h"  //Encoder contain

//Control part
#include "control_up_right.h"   //Up-right
#include "control_direction.h"  //Direction
#include "control_motor.h"      //Motor and speed
#include "h_nrf24l01.h"         //NRF24L01
#include "s_message_trans.h"    //Message trans
#include "s_value_trans.h"      //Translate the value format
#include "control_speed.h"      //Speed control

#endif

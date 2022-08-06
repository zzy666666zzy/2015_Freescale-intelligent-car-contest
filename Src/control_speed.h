#ifndef _CONTROL_SPEED_H_
#define _CONTROL_SPEED_H_

//PID
extern float speed_p;
extern float speed_d;
extern float speed_i;

//Speed
extern float speed_base,speed_base_old;
extern float speed_out;
extern float speed_counter;
extern float speed_wanna;
extern float speed_calcu;
extern float temp_speed;
extern float speed_normalization;

//Function
extern void speed_calculate_base(void);
extern void get_speed_out(void);

#endif

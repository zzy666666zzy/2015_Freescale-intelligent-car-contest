#ifndef _CONTROL_UP_RIGHT_H_
#define _CONTROL_UP_RIGHT_H_

///////////////////////////////////////
//Middle values
extern float Gyro_val;          //The middle value of gyro
extern float Accel_val;         //The middle value of accel
//Fliter
extern int GRAVITY_ADJUST_TIME_CONSTANT;   //The filter's time coefficient
extern float GYRO_DT;
//PID
extern float angle_p;
extern float angle_i;
extern float angle_d;
///////////////////////////////////////
extern float angle_base;
extern volatile int MMA7361,ENC03;
extern float g_fCarAngle;
extern float Gyro_Now,Gyro_Now_back;
extern float Accel_Now;
///////////////////////////////////////
extern void init_gyro_and_accel(void);
extern void get_state_analog_mode(void);

#endif

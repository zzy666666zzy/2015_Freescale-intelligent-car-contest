#ifndef _CONTROL_DIRECTION_H_
#define _CONTROL_DIRECTION_H_

extern float nleft,nright;
extern float Gyro_val_in_direction;
extern int direction_counter;
extern float direction_integral;
extern float direction_integral_limit;
//PID
extern float DIRECTION_CONTROL_P;
extern float DIRECTION_CONTROL_D;
extern float DIRECTION_CONTROL_I;
//End
extern float direction_base_last,direction_base;
extern float direction_out;

//speed limit
extern float direction_define_4_speed;
extern float direction_define_4_speed_last;

extern void init_ad_x_gyro(void);
extern void get_electrically_ads(void);
extern void control_direction(void);
extern void get_direction_out(void);
#endif

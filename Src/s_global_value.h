#ifndef S_GLOBAL_VALUE_H_
#define S_GLOBAL_VALUE_H_
#define DEBUG_MODE

//Global
extern float global_temp_values;

//Global rxbuf
#define rxbuf_len 128
extern char enable_get_message;
extern char rxbuf[rxbuf_len];
extern void init_uart0_rxbuf(void);

#define txbuf_len rxbuf_len
extern char txbuf[txbuf_len];

//Direction
#define DEFAULT_DIRECTION_CONTROL_P  2300//500//550;//150
#define DEFAULT_DIRECTION_CONTROL_D  1.67//0//0.62//-0.1;
#define DEFAULT_DIRECTION_CONTROL_I  0//0.1;

//Speed
#define default_speed_p  1.0//1.75//2//1//6//0.15
#define default_speed_d  0
#define default_speed_i  0//0.01

//Up-right
#define default_angle_p 370//500
#define default_angle_i 0//0.5;
#define default_angle_d 10//-0.7;

//Accel                 //2680 is in Jidian,and 2700 is in Home
#define Default_Accel   2700//2680//2700//2682//2720//2600//2595//2662
#define Default_Gyro    2025//1950//2025//2040

//Angel wanna
extern float ang_wanna;

//speed
#define DEFAULT_DIRECTION_THRESHOLD     0.4     //When get this means turning around now
#define SETTING_SPEED   15000//12000//2000              //The old version is DEFAULT_SPEED
extern float direction_threshold;
extern float DEFAULT_SPEED;


#endif

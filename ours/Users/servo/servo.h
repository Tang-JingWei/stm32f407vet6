#ifndef SERVO
#define SERVO

#include "main.h"


/* 舵机代号 */
typedef enum
{
	down_servo = 0,
	up_servo
}servo_code;




/* 舵机PWM 定时器相关 */
#define Up_Servo_Interrrupt       htim4
#define Up_Servo_Channel          TIM_CHANNEL_1

#define Down_Servo_Interrrupt     htim4
#define Down_Servo_Channel        TIM_CHANNEL_2


void Servo_Move(servo_code code, float angle);
void Servos_Relocate(void);
void Servos_Enable(void);



#endif


#include "servo.h"

float servo_angle = 0;

/**
 * @brief  舵机转向控制
 * @param  channel 通道, angle 角度(+-)
 * @retval 无
 */
void Servo_Move(servo_code code, float angle)
{
	uint16_t pwm;

	/* 限幅 */
	if (angle > 180)
		angle = 180;
	if (angle < 0)
		angle = 0;

	if (code == down_servo) /* 下舵机 左右 */
	{
		if (angle < 0)
		{
			pwm = (-1) * angle * 11.11 + 500; /* 角度换算成pwm */
		}
		else
		{
			pwm = angle * 11.11 + 500; /* 角度换算成pwm */
		}
		
		__HAL_TIM_SetCompare(&Down_Servo_Interrrupt, Down_Servo_Channel, pwm);
	}

	else if (code == up_servo) /* 上舵机 上下 */
	{
		if (angle < 0)
		{
			pwm = (-1) * angle * 11.11 + 500; /* 角度换算成pwm */
		}
		else
		{
			pwm = angle * 11.11 + 500; /* 角度换算成pwm */
		}
		
		__HAL_TIM_SetCompare(&Up_Servo_Interrrupt, Up_Servo_Channel, pwm);
	}
}

/**
 * @brief  上下舵机归位
 * @param  无
 * @retval 无
 */
void Servos_Relocate()
{
	/* pwm信号 */
}

/**
 * @brief  上下舵机使能
 * @param  无
 * @retval 无
 */
void Servos_Enable()
{
	HAL_TIM_PWM_Start(&Up_Servo_Interrrupt, Up_Servo_Channel);
	HAL_TIM_PWM_Start(&Down_Servo_Interrrupt, Down_Servo_Channel);
}

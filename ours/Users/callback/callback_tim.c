#include "callback_tim.h"


/**
 * @brief  定时器更新事件回调函数
 * @param  无
 * @retval 无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* 电机任务 TIM6 20ms间隔*/
	if (htim->Instance == TIM6)
	{
		/* 可获得当前速度once 和 累计脉冲total */
		GetMotorPulse();
		
		/* 循迹环pwm补偿 加速*/
		Gray_Search();
		
		/* Openmv 循迹补偿 */
		//Openmv_Search();
		
		/* 陀螺仪数据 */
		now_car_yaw = Mpu_Read_Yaw();
		
		/* 直走 */
		if (Line_flag == 1)
		{
			/*  使能状态下才控制  */
			if (left_en_flag == 1 || right_en_flag == 1)
			{
				/* 经过pid控制器输出控制pwm信号 */
				YunSu_Pid_Control();
				
				/* 循迹补偿 所乘系数使得循迹补偿不会过大，导致低速时过调 */
				Now_Left_Pwm += (Search_Buchang * (float)(Now_Left_Pwm / 800.0));
				Now_Right_Pwm -= (Search_Buchang * (float)(Now_Left_Pwm / 800.0));
				
				Motors_Control(Now_Left_Dir, Now_Left_Pwm, Now_Right_Dir, Now_Right_Pwm);
				
				/* 定点位置在误差允许范围判断 左右轮同时判断*/
//				if (
//							((Left_Total_Pulse <= (LineGo_Target_Maichong + 100)) && (Left_Total_Pulse >= (LineGo_Target_Maichong - 100))) ||
//							((Right_Total_Pulse <= (LineGo_Target_Maichong + 100)) && (Right_Total_Pulse >= (LineGo_Target_Maichong - 100)))
//					 )
//				{
//					stop_count++; //摆动次数
//					if (stop_count == 5)
//					{
//						Line_flag = 0;	//直走完成，到目标点了
//						Stop_flag = 1;	//小车处于停止状态
//						stop_count = 0; //置位计数

//						Motor_L_stop(); //小车停止，stop
//						Motor_R_stop();
//					}
//				}
				
			}
		}

		/* 转弯 */
		if (Turn_flag == 1)
		{
			/*  使能状态下才控制  */
			if (left_en_flag == 1 || right_en_flag == 1)
			{
				float delt_yaw;	//角度差值
				delt_yaw = now_car_yaw - last_car_yaw;
				
				/* 陀螺仪控制转弯 */	
				if((delt_yaw <= (target_yaw+2)) && (delt_yaw >= (target_yaw-2)))
				{
					/*spin_count控制最长转弯时间--200*10(中断间隔)=2000ms 2s */
					spin_count++;
					if (spin_count == 2)
					{
						Turn_flag = 0;	
						spin_succeed_flag = 1;//转弯完成
						Stop_flag = 1;	//停止位 置1
						spin_count = 0; //计数归0
	
						Motor_L_stop(); //小车停止，stop
						Motor_R_stop();
					}
				}
					
			}
		}
	}
}




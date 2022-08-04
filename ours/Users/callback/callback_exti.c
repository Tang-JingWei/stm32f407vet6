/*************************外部中断 回调*****************************/
#include "callback_exti.h"

/**
 * @brief  外部中断回调函数
 * @param  无
 * @retval 无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/*  光电传感器 外部中断 双边沿触发  */
	if (GPIO_Pin == GuangDian_Pin)
	{
		/* 利用电平状态为1 判断是上升沿 */
		if(HAL_GPIO_ReadPin(GuangDian_GPIO_Port,GuangDian_Pin) == 1)
		{
			LoadOrNot = 1;
			RedLed_off();
			GreenLed_off();
		}
		else	//下降沿
		{
			RedLed_off();
			if(LoadOrNot == 1) LoadOrNot = 0;
		}
		
	}
}



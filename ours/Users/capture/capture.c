#include "capture.h"


/*

	定时器输入捕获 回调函数

*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  static uint32_t capture_buf[2]={0,0}; //计数器缓存
  static uint8_t  capture_cnt=0;  		  //循环次数
  static uint32_t high_time;    			  //高电平时间，超声波来回一次的时间，us
  
  UNUSED(htim);
	//需要发送完触发信号后先开启上升沿捕获
	if(TIM3== htim->Instance)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
		{
		  switch(capture_cnt)
			{
			  case 0://捕获到上升沿，记录下来当前时间
				capture_buf[0]= __HAL_TIM_GET_COMPARE(htim,TIM_CHANNEL_3);
			    __HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_3,TIM_INPUTCHANNELPOLARITY_FALLING); //开启捕获下降沿
				  capture_cnt++;
			 break;
			 case 1://捕获到下降沿，记录下此刻时间
				  capture_buf[1]= __HAL_TIM_GET_COMPARE(htim,TIM_CHANNEL_3); 
				  capture_cnt=0;
				  HAL_TIM_IC_Stop_IT(htim,TIM_CHANNEL_3); //停止捕获 
				  high_time = capture_buf[1]- capture_buf[0];
//				  if(capture_buf[1]>capture_buf[0])
//						printf("DIST = %.1fCM\r\n",17.0*high_time/1000); 
		     break;				 
		     default: break;
			}		
			
			HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_3);  //开启输入捕获中断
		}	
				
		
	}	
}





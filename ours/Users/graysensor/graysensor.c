#include "graysensor.h"


/*  传感器标志位  */
uint8_t L2_flag, L1_flag, MID_flag, R1_flag, R2_flag;

/*  巡线补偿变量  */
float Search_Buchang = 0;


/*  
灰度传感器循迹 返回0/1  

灰度值较高（黑）：引脚置高	flag = 1
灰度值较低（白）：引脚置低	flag = 0

*/
void Gray_Search(void)  
{
	
	if(HAL_GPIO_ReadPin(GRAY_L1_GPIO_Port, GRAY_L1_Pin) == GPIO_PIN_SET){L2_flag = 1;} else {L2_flag = 0;}
	if(HAL_GPIO_ReadPin(GRAY_L2_GPIO_Port, GRAY_L2_Pin) == GPIO_PIN_SET){L1_flag = 1;} else {L1_flag = 0;}
	if(HAL_GPIO_ReadPin(GRAY_MID_GPIO_Port,GRAY_MID_Pin) == GPIO_PIN_SET){MID_flag = 1;} else {MID_flag = 0;}
	if(HAL_GPIO_ReadPin(GRAY_R1_GPIO_Port, GRAY_R1_Pin) == GPIO_PIN_SET){R1_flag = 1;} else {R1_flag = 0;}
	if(HAL_GPIO_ReadPin(GRAY_R2_GPIO_Port, GRAY_R2_Pin) == GPIO_PIN_SET){R2_flag = 1;} else {R2_flag = 0;}
	
	/*  寻线脉冲补偿  */
	if(L1_flag == 0 &&  MID_flag == 1 && R1_flag == 0) Search_Buchang =  0;
	else if(L1_flag == 0 &&  MID_flag == 1 && R1_flag == 1) Search_Buchang =  700;
	else if(L1_flag == 0 &&  MID_flag == 0 && R1_flag == 1) Search_Buchang =  600;
	else if(L1_flag == 1 &&  MID_flag == 0 && R1_flag == 0) Search_Buchang = -600;   
  else if(L1_flag == 1 &&  MID_flag == 1 && R1_flag == 0) Search_Buchang = -700;	
	else if(L2_flag == 1 &&  L1_flag == 0 &&  MID_flag == 0 && R1_flag == 0 && R2_flag == 0) Search_Buchang = -1000;	
  else if(L2_flag == 0 &&  L1_flag == 0 &&  MID_flag == 0 && R1_flag == 0 && R2_flag == 1) Search_Buchang = 1000;
	else if(L2_flag == 0 &&  L1_flag == 0 &&  MID_flag == 0 && R1_flag == 0 && R2_flag == 0) Search_Buchang = 0;	
	else Search_Buchang =  0;
	
	
}







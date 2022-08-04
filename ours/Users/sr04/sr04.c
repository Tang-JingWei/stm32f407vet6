#include "sr04.h"
#include "tim.h"
#include "usart.h"
extern int a;
static float distance_temp=0;
static float distance_last=0;
static float distance_result;



void UltrasonicWave_StartMeasure(void){
//	HAL_GPIO_WritePin(SR04T_GPIO_Port,SR04T_Pin,GPIO_PIN_SET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(SR04T_GPIO_Port,SR04T_Pin,GPIO_PIN_RESET);
	
}

float UltrasonicWave_Measure(void) //
{
//	uint16_t time_node1;
//  uint16_t time_node2;
//  uint16_t measure;
//	UltrasonicWave_StartMeasure(); //启动超声波   
//	__HAL_TIM_DISABLE(&htim4); 	
//	//while(HAL_GPIO_ReadPin(SR04R_GPIO_Port,SR04R_Pin) == 0)
//		//printf("2");//等待 echo的高电平到来 
//		
//	__HAL_TIM_SET_COUNTER(&htim4,0);
//	__HAL_TIM_ENABLE(&htim4); 
//	time_node1=TIM4->CNT;
//	//while(HAL_GPIO_ReadPin(SR04R_GPIO_Port,SR04R_Pin)  == 1)
//		//printf("3");//等待 echo的高电平结束
//	time_node2=TIM4->CNT;
//	//printf("%d",TIM4->CNT);
//	measure=time_node2-time_node1;
//	return measure*17/1000;    //此处单位转换为cm
	
}


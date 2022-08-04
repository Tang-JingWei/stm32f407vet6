#ifndef LED_H
#define LED_H


/* ºìµÆ */
#define RedLed_on()  			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_RESET)
#define RedLed_off() 			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_SET)
	
	
/* ÂÌµÆ */	
#define GreenLed_on()  		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET)
#define GreenLed_off() 		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_SET)
	
	
/* À¶µÆ */	
#define BlueLed_on()  		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,GPIO_PIN_RESET)
#define BlueLed_off() 		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,GPIO_PIN_SET)


/** ·´×ª **/
#define RedLed_Tog() 			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
#define GreenLed_Tog() 		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)
#define BlueLed_Tog() 		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin)






#endif




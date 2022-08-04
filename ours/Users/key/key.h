#ifndef _KEY_H
#define _KEY_H


#include "main.h"


/* °´¼üÉ¨Ãè */
#define KEY1_SCAN() 	HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define KEY2_SCAN() 	HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
#define KEY3_SCAN() 	HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define KEY4_SCAN() 	HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)


extern uint8_t key_count;



void KeyScan();




#endif



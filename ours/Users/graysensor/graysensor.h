#ifndef _GRAYSENSOR_
#define _GRAYSENSOR_

#include "main.h"

/*  传感器标志位  */
extern uint8_t L2_flag, L1_flag, MID_flag, R1_flag, R2_flag;

/*  巡线补偿变量  */
extern float Search_Buchang;



void Gray_Search(void);




#endif



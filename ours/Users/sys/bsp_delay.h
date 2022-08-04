#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H 			   
#include "bsp_sys.h"  


void delay_init(uint8_t SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#endif






























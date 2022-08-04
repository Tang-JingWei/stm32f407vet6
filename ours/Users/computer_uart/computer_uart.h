/*************************串口 上位机 通信*****************************/

#ifndef COMPUTER_UART_H
#define COMPUTER_UART_H


#include "main.h"

//上位机----协议定义数据种类长度、单个数据长度、传输数据类型
#define COMPUTER_MAX_LENGTH       4
#define COMPUTER_MAX_DATA_BYTE    4
#define COMPUTER_ASCII 			    	1

//上位机串口宏定义
#define ComputerUsart          USART6   
#define ComputerInterrupt      huart6   

extern uint8_t Computer_Rxstate;						        //接收状态
extern uint8_t Computer_Rxcount;						        //接收次数
extern uint8_t Computer_Rxbuffer;							      //接收缓存
extern uint16_t Computer_Rxbuff[200];   			        //缓冲区
extern uint16_t Computer_Data[COMPUTER_MAX_LENGTH];	//解析出的真实数据


/* 上位机-接收数据 */
void Computer_Receive_Data();

/* 上位机-数据处理 */
void Computer_Data_Handle();

#endif


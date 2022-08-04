/*************************串口 蓝牙 通信*****************************/
#ifndef BLE
#define BLE

#include "main.h"

//蓝牙----协议定义数据种类长度、单个数据长度、传输数据类型
#define BLE_MAX_LENGTH       2
#define BLE_MAX_DATA_BYTE    1
#define BLE_ASCII 					 1

//蓝牙串口宏定义
#define BleUsart          USART2   
#define BleInterrupt      huart2   

extern uint8_t Ble_Rxstate;						  	//接收状态
extern uint8_t Ble_Rxcount;						  	//接收次数
extern uint8_t Ble_Rxbuffer;							//接收缓存
extern uint16_t Ble_Rxbuff[200];   			  //缓冲区
extern uint16_t Ble_Data[BLE_MAX_LENGTH];	//解析出的真实数据


/* 蓝牙接收数据 */
void Ble_Receive_Data(void);

/* 蓝牙数据处理 */
void Ble_Data_Handle(void);

/* 发送数据给蓝牙 */
void SendDataToBle();

#endif


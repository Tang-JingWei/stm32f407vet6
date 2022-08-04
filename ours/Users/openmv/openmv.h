#ifndef OPENMV
#define OPENMV


#include "main.h"


//协议定义数据种类长度、单个数据长度、传输数据类型
#define OPENMV_MAX_LENGTH          6
#define OPENMV_MAX_DATA_BYTE       2
#define OPENMV_ASCII 				       1

//openmv串口宏定义
#define OpenmvUsart      USART1   
#define OpenmvInterrupt  huart1   

extern uint8_t  Openmv_Rxstate;							      //接收状态
extern uint8_t  Openmv_Rxcount;							      //接收次数
extern uint8_t  Openmv_Rxbuffer;						      //接收缓存
extern uint16_t  Openmv_Rxbuff[200];   		        //缓冲区
extern uint16_t  Openmv_Data[OPENMV_MAX_LENGTH];	  //解析出的真实数据

/* 循迹变量 */
extern uint8_t err_dir;
extern uint8_t err_dir2;
extern uint8_t err_data_angel;
extern uint8_t err_data_dis;

/* openmv 接收  */
void Openmv_Recive_Data(void);

/* openmv 接收数据处理 */
void Openmv_Data_Handle(void);

/* openmv 循迹 */
void Openmv_Search(void);


#endif




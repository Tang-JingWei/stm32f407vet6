/*************************串口 蓝牙 通信*****************************/
#include "ble.h"

uint8_t Ble_Rxstate = 0;							  //接收状态
uint8_t Ble_Rxcount = 0;							  //接收次数
uint8_t Ble_Rxbuffer = 0;							  //接收缓存
uint16_t Ble_Rxbuff[200] = {0};   			  //缓冲区
uint16_t Ble_Data[BLE_MAX_LENGTH] = {0};	//解析出的真实数据



void Ble_Receive_Data()
{
  static uint16_t  Ble_Data_temp = 0; //暂时存放计算数据
	static uint8_t  Ble_Split_count = 0; //分隔的每个数据单元计数
		
		if(Ble_Rxstate == 0 && Ble_Rxbuffer == '#')			//帧头
		{
				Ble_Rxstate = 1;	//帧开始
				memset(Ble_Rxbuff, 0, sizeof(200));
		}
		else if(Ble_Rxstate == 1 && Ble_Rxbuffer == '$')		//帧尾
		{	
				if(Ble_Rxcount == (BLE_MAX_LENGTH * BLE_MAX_DATA_BYTE))		//接收完成(MAX_LENGTH * MAX_DATA_BYTE)位数据
				{
					for(int i=0;i<BLE_MAX_LENGTH;i++)
					{
						for(int j=0;j<BLE_MAX_DATA_BYTE;j++)
						{
								#if(BLE_ASCII == 1)	//字符传输
								Ble_Data_temp += (Ble_Rxbuff[i * BLE_MAX_DATA_BYTE + j] - '0') * pow(10,(BLE_MAX_DATA_BYTE-1 - j));
								#else						//数据传输
								Ble_Data_temp += (Ble_Rxbuff[i * BLE_MAX_DATA_BYTE + j]) * pow(10,(BLE_MAX_DATA_BYTE-1 - j));
								#endif
						}
						Ble_Data[i] = Ble_Data_temp;
						Ble_Data_temp = 0;
					}
					//printf("%d %d %d %d\r\n",Ble_Data[0],Ble_Data[1],Ble_Data[2],Ble_Data[3]); //测试数据
					Ble_Data_Handle();
					Ble_Rxstate = 0;			//帧结束		
					Ble_Rxcount = 0;					
					Ble_Rxbuffer = 0;				  
					memset(Ble_Rxbuff, 0, sizeof(200));  
				}
				else
				{
					//非正确协议
				}
		}
		else if(Ble_Rxstate == 1 && Ble_Rxbuffer == ',')		//‘&’是协议的连接符，无意义，算法处理时跳过
		{
				if(Ble_Split_count != BLE_MAX_DATA_BYTE)   //每个数据都要是MAX_DATA_BYTE位才正确
				{
					//非正确协议
					Ble_Rxstate = 0;					
					Ble_Rxcount = 0;					
					Ble_Rxbuffer = 0;				  
					memset(Ble_Rxbuff, 0, sizeof(200)); 
				}
				Ble_Split_count = 0;	//重置计数
				
		}
		else if(Ble_Rxstate == 1)				//Ble_Rxstate == 1表示正在接收数据
		{
				Ble_Rxbuff[Ble_Rxcount++] = Ble_Rxbuffer; 
				Ble_Split_count++;
		}
				
		HAL_UART_Receive_IT(&BleInterrupt,(uint8_t *)&Ble_Rxbuffer,1);	//开中断


}


/*  改变电机控制变量  */
void Ble_Data_Handle()
{
	
	Car_Task = Ble_Data[0]; 
	switch(Car_Task)
	{
		case 1:
			task1_dir = Ble_Data[1];
		break;
		case 2:
			task2_dir = Ble_Data[1];
		break;
	}
//	Now_Left_Dir = Ble_Data[0];
//	Now_Left_Pwm = Ble_Data[1];
//	
//	Now_Right_Dir = Ble_Data[2];
//	Now_Right_Pwm = Ble_Data[3];
	
	//Motors_Control(Now_Left_Dir, Now_Left_Pwm, Now_Right_Dir, Now_Right_Pwm);
}


/* 发送数据给蓝牙 */
void SendDataToBle()
{
	uint8_t sendBuff[6];
	
//	sprintf((char *)sendBuff, "*%d%d&", TASK, TargetNum);
	HAL_UART_Transmit(&BleInterrupt, sendBuff, sizeof(sendBuff), 1000);

}


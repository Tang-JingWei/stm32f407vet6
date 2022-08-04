#include "openmv.h"

uint8_t  Openmv_Rxstate;							      //接收状态
uint8_t  Openmv_Rxcount;							      //接收次数
uint8_t  Openmv_Rxbuffer;						        //接收缓存
uint16_t  Openmv_Rxbuff[200];   		        //缓冲区
uint16_t  Openmv_Data[OPENMV_MAX_LENGTH];	  //解析出的真实数据

/* 循迹变量 */
uint8_t err_dir = 0;
uint8_t err_dir2 = 0;
uint8_t err_data_angel = 0;
uint8_t err_data_dis = 0;
         

/* openmv 接收  */
void Openmv_Recive_Data()
{
	//printf("%c",Openmv_Rxbuffer);
  static uint16_t  Openmv_Data_temp = 0; //暂时存放计算数据
	static uint8_t  Openmv_Split_count = 0; //分隔的每个数据单元计数
		
		if(Openmv_Rxstate == 0 && Openmv_Rxbuffer == '#')			//帧头
		{
			//printf("开始\r\n");
				Openmv_Rxstate = 1;	//帧开始
				memset(Openmv_Rxbuff, 0, sizeof(200));
		}
		else if(Openmv_Rxstate == 1 && Openmv_Rxbuffer == '$')		//帧尾
		{	
				if(Openmv_Rxcount == (OPENMV_MAX_LENGTH * OPENMV_MAX_DATA_BYTE))		//接收完成(MAX_LENGTH * MAX_DATA_BYTE)位数据
				{
					for(int i=0;i<OPENMV_MAX_LENGTH;i++)
					{
						for(int j=0;j<OPENMV_MAX_DATA_BYTE;j++)
						{
								//printf("%c\r\n",Computer_Rxbuff[i*4+j]); //测试
								#if(OPENMV_ASCII == 1)	//字符传输
								Openmv_Data_temp += (Openmv_Rxbuff[i * OPENMV_MAX_DATA_BYTE + j] - '0') * pow(10,(OPENMV_MAX_DATA_BYTE-1 - j));
								#else										//数据传输
								Openmv_Data_temp += (Openmv_Rxbuff[i * OPENMV_MAX_DATA_BYTE + j]) * pow(10,(OPENMV_MAX_DATA_BYTE-1 - j));
								#endif
						}
						Openmv_Data[i] = Openmv_Data_temp;
						Openmv_Data_temp = 0;
					}
					//printf("%d %d %d %d\r\n",Openmv_Data[0],Openmv_Data[1],Openmv_Data[2],Openmv_Data[3]); //测试数据
					Openmv_Data_Handle();
					Openmv_Rxstate = 0;			//帧结束		
					Openmv_Rxcount = 0;					
					Openmv_Rxbuffer = 0;				  
					memset(Openmv_Rxbuff, 0, sizeof(200));  
				}
				else
				{
					//printf("错误\r\n");
					//非正确协议
				}
		}
		else if(Openmv_Rxstate == 1 && Openmv_Rxbuffer == ',')		//‘&’是协议的连接符，无意义，算法处理时跳过
		{
				if(Openmv_Split_count != OPENMV_MAX_DATA_BYTE)   //每个数据都要是MAX_DATA_BYTE位才正确
				{
					//非正确协议
					Openmv_Rxstate = 0;					
					Openmv_Rxcount = 0;					
					Openmv_Rxbuffer = 0;				  
					memset(Openmv_Rxbuff, 0, sizeof(200)); 
				}
				Openmv_Split_count = 0;	//重置计数
				
		}
		else if(Openmv_Rxstate == 1)				//Openmv_Rxstate == 1表示正在接收数据
		{
				Openmv_Rxbuff[Openmv_Rxcount++] = Openmv_Rxbuffer; 
				Openmv_Split_count++;
		}
				
		HAL_UART_Receive_IT(&OpenmvInterrupt,(uint8_t *)&Openmv_Rxbuffer,1);	//开中断


}

/* 
	帧格式：

	#__DIR__,__ERR__,$ 

*/

/* openmv 接收数据处理 */
void Openmv_Data_Handle()
{
	//printf("%d %d\r\n",Openmv_Data[0], Openmv_Data[1]);
	
	/* 传回来的是 控制指令 */
	if(Openmv_Data[0] == 1)
	{
		if(Openmv_Data[1])
		{
			Line_flag = Openmv_Data[1];
		}
		if(Openmv_Data[2])
		{
			Turn_flag = Openmv_Data[2];
		}
		if(Openmv_Data[3])
		{
			Stop_flag = Openmv_Data[3];
		}
		
		Car_Task = Openmv_Data[4];
		task_dir = Openmv_Data[5];
	}
	
	/* 传回来的是 误差量 */
	else if(Openmv_Data[0] == 2)
	{
		err_dir = Openmv_Data[1]; 
		err_data_angel = Openmv_Data[2];	//偏差角
		
		err_dir2 = Openmv_Data[3]; 
		err_data_dis = Openmv_Data[4];		//偏差距离
		// Openmv_Data[5];
	}
	
}


/*
	帧格式：

	#__TASK__,__DIR__,$ 

*/
void SendDataToOpenmv()
{
	uint8_t sendBuff[4];
	
//	sprintf((char *)sendBuff, "*%d%d&", TASK, TargetNum);
//	HAL_UART_Transmit(&OpenmvInterrupt, sendBuff, sizeof(sendBuff), 1000);
	
}


void Openmv_Search()
{
	switch(err_dir2)
	{
		case 1:	//左偏 z
			Search_Buchang = err_data_dis * 15 * (-1);
		break;
		
		case 2:	//右偏 y
			Search_Buchang = err_data_dis * 15;
		break;
	}
}

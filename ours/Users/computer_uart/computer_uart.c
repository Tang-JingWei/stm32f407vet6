/*************************串口 上位机 通信*****************************/
#include "computer_uart.h"

uint8_t Computer_Rxstate = 0;							        //接收状态
uint8_t Computer_Rxcount = 0;							        //接收次数
uint8_t Computer_Rxbuffer = 0;							      //接收缓存
uint16_t Computer_Rxbuff[200] = {0};   			      //缓冲区
uint16_t Computer_Data[COMPUTER_MAX_LENGTH] = {0};	//解析出的真实数据


/* 上位机接收 */
void Computer_Receive_Data()
{
		static uint16_t Computer_Data_temp = 0; //暂时存放计算数据
		static uint8_t Computer_Split_count = 0; //分隔的每个数据单元计数
		
		if(Computer_Rxstate == 0 && Computer_Rxbuffer == '#')			//帧头
		{
				Computer_Rxstate = 1;	//帧开始
				memset(Computer_Rxbuff, 0, sizeof(200));
		}
		else if(Computer_Rxstate == 1 && Computer_Rxbuffer == '$')		//帧尾
		{	
				if(Computer_Rxcount == (COMPUTER_MAX_LENGTH * COMPUTER_MAX_DATA_BYTE))		//接收完成(MAX_LENGTH * MAX_DATA_BYTE)位数据
				{
					for(int i=0;i<COMPUTER_MAX_LENGTH;i++)
					{
						for(int j=0;j<COMPUTER_MAX_DATA_BYTE;j++)
						{
              	//printf("%c\r\n",Computer_Rxbuff[i*4+j]); //测试
								#if(COMPUTER_ASCII == 1)	//字符传输
								Computer_Data_temp += (Computer_Rxbuff[i * COMPUTER_MAX_DATA_BYTE + j] - '0') * pow(10,(COMPUTER_MAX_DATA_BYTE-1 - j));
								#else						//数据传输
								Computer_Data_temp += (Computer_Rxbuff[i * COMPUTER_MAX_DATA_BYTE + j]) * pow(10,(COMPUTER_MAX_DATA_BYTE-1 - j));
								#endif
						}
						Computer_Data[i] = Computer_Data_temp;
						Computer_Data_temp = 0;
					}
					//printf("%d %d %d %d\r\n",Computer_Data[0],Computer_Data[1],Computer_Data[2],Computer_Data[3]); //测试数据
					Computer_Data_Handle();
					Computer_Rxstate = 0;			//帧结束		
					Computer_Rxcount = 0;					
					Computer_Rxbuffer = 0;				  
					memset(Computer_Rxbuff, 0, sizeof(200));  
				}
				else
				{
					//非正确协议
				}
		}
		else if(Computer_Rxstate == 1 && Computer_Rxbuffer == ',')		//‘&’是协议的连接符，无意义，算法处理时跳过
		{
				if(Computer_Split_count != COMPUTER_MAX_DATA_BYTE)   //每个数据都要是MAX_DATA_BYTE位才正确
				{
					//非正确协议
					Computer_Rxstate = 0;					
					Computer_Rxcount = 0;					
					Computer_Rxbuffer = 0;				  
					memset(Computer_Rxbuff, 0, sizeof(200)); 
				}
				Computer_Split_count = 0;	//重置计数
				
		}
		else if(Computer_Rxstate == 1)				//Ble_Rxstate == 1表示正在接收数据
		{
				Computer_Rxbuff[Computer_Rxcount++] = Computer_Rxbuffer; 
				Computer_Split_count++;
		}
				
		HAL_UART_Receive_IT(&ComputerInterrupt,(uint8_t *)&Computer_Rxbuffer,1);	//开中断
}




/*  改变电机控制变量  */
void Computer_Data_Handle()
{
	/* 上位机测试电机 */
//	Now_Left_Dir = Computer_Data[0];
//	Now_Left_Pwm = Computer_Data[1];
//	Now_Right_Dir = Computer_Data[2];
//	Now_Right_Pwm = Computer_Data[3];
//	printf("%d %d %d %d\r\n",Now_Left_Dir,Now_Left_Pwm,Now_Right_Dir,Now_Right_Pwm);
//	Motors_Control(Now_Left_Dir, Now_Left_Pwm, Now_Right_Dir, Now_Right_Pwm);
	
	/* 上位机测试舵机 */
	int pwm = Computer_Data[0];
	__HAL_TIM_SetCompare(&Up_Servo_Interrrupt, Up_Servo_Channel, pwm);

//	pid_left_speed.Kp =	(float)Computer_Data[0] / 100.0;
//	pid_left_speed.Ki = (float)Computer_Data[1] / 100.0;
//	pid_right_speed.Kp = (float)Computer_Data[2] / 100.0;
//  pid_right_speed.Ki =(float)Computer_Data[3] / 100.0;
//	
//	printf("%f %f %f %f\r\n",pid_left_speed.Kp,pid_left_speed.Ki,pid_right_speed.Kp,pid_right_speed.Ki);
	//PID_param_init();
}




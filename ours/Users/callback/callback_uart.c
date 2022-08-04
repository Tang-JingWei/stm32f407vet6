#include "callback_uart.h"

/**
 * @description: 串口接收中断函数
	协议说明：
	<1>
		高位-----------------低位
			#xxxx,xxxx,xxxx,xxxx,$
		帧首-----------------帧尾	
	<2>
		xxxx:  x表示一个字节长度的数据，xxxx表示接收四个字节
	 ‘,’:  表示分隔符(可自定义)，Ble_Split_count进行计数，判断每个数据是否正确，
					 否则可认为 到‘,’为止的前一个接收数据为错误，该帧丢弃，重置变量，接收下个帧
	<3>
		算法原理：1.单个字符拼接 --> 字符转数字（ASCII == 1）
						  2.直接传输数据，当然也要规定传输的数据长度和种类多少还有分隔符（ASCII == 0）
		算法参考：http://www.51hei.com/bbs/dpj-207742-1.html
 * @param {UART_HandleTypeDef} *huart
 * @author: 唐京伟
 * 
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//printf("hello\r\n");
	if(huart->Instance == BleUsart)  //蓝牙中断
	{
		/* Receive_Data() 前面不要加printf输出，会影响接收 */
		Ble_Receive_Data();
	}
	
	if(huart->Instance == ComputerUsart)  //上位机中断
	{
		/* Receive_Data() 前面不要加printf输出，会影响接收 */
		Computer_Receive_Data();
	}
	
	if(huart->Instance == OpenmvUsart)	//Openmv中断
	{
		/* Receive_Data() 前面不要加printf输出，会影响接收 */
		Openmv_Recive_Data();
	}

}






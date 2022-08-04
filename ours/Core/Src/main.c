/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char str_oled[50] = {0};

short gx, gy, gz;
short ax, ay, az;

/*  小车执行任务代码  0-无任务default 1-近端任务 2-中端任务 3-远端任务 */
uint8_t Car_Task = 0, task_dir = 0;
uint8_t LoadOrNot = 0;
uint8_t Do_count = 0;	//任务执行步骤

/* 任务一 近端病房 */
uint8_t task1_dir = 2;
uint8_t finish_11 = 0, start_11 = 0;
uint8_t finish_12 = 0, start_12 = 0;

/* 任务二 中端病房 */
uint8_t task2_dir = 1;
uint8_t finish_21 = 0, start_21 = 0;
uint8_t finish_22 = 0, start_22 = 0;

/* 任务三 远端病房 */
uint8_t task3_dir = 0;
uint8_t finish_31 = 0, start_31 = 0;
uint8_t finish_32 = 0, start_32 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	delay_init(72);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_I2C2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();	//oled初始化 ！！！一定要放在GOIO_Init()之后
	
//	MPU6050_Init();	//mpu6050初始化
//	while(MPU6050ReadID() != 0x68)
//	{
//		OLED_Show_Position(1,6,"MPU6050 error!");
//		printf("MPU ID错误\r\n");
//	}
//	OLED_Show_Position(1,6,"MPU6050 ready!");
	
	__HAL_TIM_SET_COUNTER(&htim6,400-1); //40ms
	HAL_TIM_Base_Start_IT(&htim6); //电机任务
	
	Left_Enable();
	Right_Enable();
	 	 
	HAL_UART_Receive_IT(&ComputerInterrupt,(uint8_t *)&Computer_Rxbuffer,1);	//开上位机接收中断
	HAL_UART_Receive_IT(&BleInterrupt,(uint8_t *)&Ble_Rxbuffer,1);						//开蓝牙接收中断
	HAL_UART_Receive_IT(&OpenmvInterrupt,(uint8_t *)&Openmv_Rxbuffer,1);			//开openmv接收中断
	
  Encoder_Configuration();//编码器启动
	
	PID_param_init();/* 左右轮pid控制器参数初始化 */

	/* 舵机使能 */
	//Servos_Enable();

	/* 小车直行、拐弯测试 */
	//Spin_Turn(right_90);
	//Car_Go(300);
	YunSu_GO(200);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {		
//		char str[50];
//		sprintf(str,"Angle.yaw: %.1f",now_car_yaw);
//		OLED_Show_Position(1,3,str);
		
		//OLED_Show_Position(1,6,"%d %d %d %d",err_dir,err_data_angel,err_dir2,err_data_dis);
//		OLED_Show_Position(1,6,"%d %d %d %d %d",Line_flag, Turn_flag, Stop_flag, Car_Task, task_dir);
		
//		sprintf(str_oled,"Task_Num: %d",Car_Task);
//		OLED_Show_Position(1,1,str_oled);
		
		/* 近端病房任务 */
//		if(Car_Task == 1)
//		{
//			//task1_dir = Openmv_Data[1];	//获得方向
//			/* 1 号 */
//			if(task_dir == 1)	//左 任务11
//			{
//				if(finish_11 == 0)	//任务11开始
//				{
//					switch(Do_count)
//					{
//						case 0:
//							if(LoadOrNot == 1)
//							{
//								RedLed_off();
//								GreenLed_on();
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 1:
//							if(Turn_flag == 1)
//							{
//								Spin_Turn(left_90);
//								Do_count++;
//							}
//						break;
//						case 2:
//							if(Stop_flag == 1)
//							{
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 3:
//							if(Stop_flag == 1 && LoadOrNot == 0)
//							{
//								Spin_Turn(back_180);
//								Do_count++;
//							}
//						break;
//						case 4:
//							if(Stop_flag == 1)
//							{
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 5:
//							if(Turn_flag == 1)
//							{
//								Spin_Turn(right_90);
//								Do_count++;
//							}
//						break;
//						case 6:
//							if(Stop_flag == 1)
//							{
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 7:
//							if(Stop_flag == 1)
//							{
//								Spin_Turn(back_180);
//								Do_count = 0;
//								finish_11 = 1;	//任务11结束
//								GreenLed_on();//绿灯
//							}
//						break;
//					}
//				}
//			}
//			/* 2 号 */
//			else if(task_dir == 2)	//右边 任务12
//			{
//				if(finish_12 == 0)	//任务11开始
//				{
//					switch(Do_count)
//					{
//						case 0:
//							if(LoadOrNot == 1)
//							{
//								RedLed_off();
//								GreenLed_on();
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 1:
//							if(Turn_flag == 1)
//							{
//								Spin_Turn(left_90);
//								Do_count++;
//							}
//						break;
//						case 2:
//							if(Stop_flag == 1)
//							{
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 3:
//							if(Stop_flag == 1 && LoadOrNot == 0)
//							{
//								Spin_Turn(back_180);
//								Do_count++;
//							}
//						break;
//						case 4:
//							if(Stop_flag == 1)
//							{
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 5:
//							if(Turn_flag == 1)
//							{
//								Spin_Turn(right_90);
//								Do_count++;
//							}
//						break;
//						case 6:
//							if(Stop_flag == 1)
//							{
//								YunSu_GO(120);
//								Do_count++;
//							}
//						break;
//						case 7:
//							if(Stop_flag == 1)
//							{
//								Spin_Turn(back_180);
//								Do_count = 0;
//								finish_12 = 1;	//任务12结束
//								GreenLed_on();//绿灯
//							}
//						break;
//					}
//				}
//			}
//		}

		if(Car_Task == 1)
		{
			//task1_dir = Openmv_Data[1];	//获得方向
			/* 1 号 */
				if(finish_11 == 0)	//任务11开始
				{
					switch(Do_count)
					{
						case 0:
							if(LoadOrNot == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 1:
							if(Turn_flag == 1)
							{
								if(task_dir == 1)
								{
									Spin_Turn(left_90);
									Do_count++;
								}
								else if(task_dir == 2)
								{
									Spin_Turn(right_90);
									Do_count++;
								}
							}
						break;
						case 2:
							if(spin_succeed_flag == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 3:
							if(Stop_flag == 1 && LoadOrNot == 0)
							{
								Spin_Turn(back_180);
								Do_count++;
							}
						break;
						case 4:
							if(spin_succeed_flag == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 5:
							if(Stop_flag == 1)
							{
								if(task_dir == 1)
								{
									Spin_Turn(right_90);
									Do_count++;
								}
								else if(task_dir == 2)
								{
									Spin_Turn(left_90);
									Do_count++;
								}
							}
						break;
						case 6:
							if(spin_succeed_flag == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 7:
							if(Stop_flag == 1)
							{
								Spin_Turn(back_180);
								Do_count = 0;
								finish_11 = 1;	//任务11结束
								GreenLed_on();//绿灯
							}
						break;
					}
				}
			
			/* 2 号 */
				else if(finish_12 == 0)	//任务12开始
				{
					switch(Do_count)
					{
						case 0:
							if(LoadOrNot == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 1:
//							if(task_dir == 1)
//							{
//								Spin_Turn(left_90);
//								Do_count++;
//							}
//							else if(task_dir == 2)
//							{
//								Spin_Turn(right_90);
//								Do_count++;
//							}
							if(Stop_flag == 1)
							{
								Spin_Turn(right_90);
								Do_count++;
							}
						break;
						case 2:
							if(spin_succeed_flag == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 3:
							if(Stop_flag == 1)
							{
								Motor_L_stop();
								Motor_R_stop();
								Do_count++;
							}
						break;
						case 4:
							if(LoadOrNot == 0)
							{
								Spin_Turn(back_180);
								Do_count++;
							}
						break;
 						case 5:
							if(spin_succeed_flag == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 6:
							if(Stop_flag == 1)
							{
								Spin_Turn(left_90);
//								if(task_dir == 1)
//								{
//									Spin_Turn(right_90);
//									Do_count++;
//								}
//								else if(task_dir == 2)
//								{
//									Spin_Turn(left_90);
//									Do_count++;
//								}
							}
						break;
						case 7:
							if(spin_succeed_flag == 1)
							{
								YunSu_GO(120);
								Do_count++;
							}
						break;
						case 8:
							if(Stop_flag == 1)
							{
								Spin_Turn(back_180);
								Do_count = 0;
								finish_12 = 1;	//任务12结束
								GreenLed_on();//绿灯
							}
						break;
					}
				}
			}
		
		/* 中端病房任务 */
		else if(Car_Task == 2)
		{
			if(LoadOrNot == 1)
			{
				Car_Go(135);
				while(Stop_flag != 1){delay_ms(1);}
				delay_ms(2000);
				//while(Openmv_Data[1] == 0){delay_us(1);}
				//task2_dir = Openmv_Data[1];
				if(task2_dir == 1)	//左边 任务21
				{
					if(start_21 == 0)
					{
						Car_Go(20);
						while(Stop_flag != 1){delay_ms(1);}
						Spin_Turn(left_90);
						while(Stop_flag != 1){delay_ms(1);}
						Car_Go(35);
						while(Stop_flag != 1 || LoadOrNot != 0){delay_us(1);}
						Spin_Turn(back_180);
						while(Stop_flag != 1){delay_ms(1);}
						Car_Go(35);
						while(Stop_flag != 1){delay_ms(1);}
						Spin_Turn(right_90);
						while(Stop_flag != 1){delay_ms(1);}
						Car_Go(155);
						while(Stop_flag != 1){delay_ms(1);}
						Spin_Turn(back_180);
						
						start_21 = 1;
						GreenLed_on();
					}
				}
			
			}
			else if(task2_dir == 2)	//右边 任务22
			{
				
			}
		}
		/* 远端病房任务 */
		else if(Car_Task == 3)
		{
		
		
		}
		else
		{
			//
		}
		
		
		
		
		
		
		
		
		
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


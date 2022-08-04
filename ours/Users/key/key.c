#include "key.h"

uint8_t key_count = 1;

void KeyScan()
{
	if(KEY1_SCAN() == 0)
	{
		key_count++;
		if(key_count == 2)
		{
			/* 用户代码开始 */
			
			RedLed_Tog();
			/* 用户代码结束 */
			
			key_count = 0;
		}while(KEY1_SCAN() == 0);
	}
	
	else if(KEY2_SCAN() == 0)
	{
		key_count++;
		if(key_count == 2)
		{
			/* 用户代码开始 */
			
			BlueLed_Tog();
			/* 用户代码开始 */
			
			key_count = 0;
		}while(KEY2_SCAN() == 0);
	}
}








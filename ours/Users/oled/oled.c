// OLED显示
//屏幕像素点为128*64，每8行为一页，共8页
//显示a*b:a为字体宽度，b为字体高度（因为一页的高度为8，当b>8时，需要b/8页）
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "oled.h"

unsigned char oled_picture[8][128] = {0};

volatile u8 Flag_clear = 0;

// OLED写数据
void OLED_WrDat(unsigned char dat)
{
	u8 i;
	OLED_RS_Set(); // DC 置1写数据
	for (i = 0; i < 8; i++)
	{
		OLED_SCLK_Clr();
		if (dat & 0x01)
		{
			OLED_SDIN_Set();
		}
		else
		{
			OLED_SDIN_Clr();
		}
		OLED_SCLK_Set();
		dat >>= 1;
	}
	OLED_RS_Set();
}

// OLED写命令
void OLED_WrCmd(unsigned char cmd)
{
	u8 i;
	OLED_RS_Clr(); // DC 置0写命令
	for (i = 0; i < 8; i++)
	{
		OLED_SCLK_Clr();
		if (cmd & 0x80)
		{
			OLED_SDIN_Set();
		}
		else
		{
			OLED_SDIN_Clr();
		}
		OLED_SCLK_Set();
		cmd <<= 1;
	}
	OLED_RS_Set();
}

//开启OLED显示
void OLED_Display_On(void)
{
	OLED_WrCmd(0X8D); // SET DCDC命令（开始写电荷泵）
	OLED_WrCmd(0X14); // DCDC ON（bit2置1开启电荷泵）
	OLED_WrCmd(0XAF); // DISPLAY ON（开启显示）
}

//关闭OLED显示
void OLED_Display_Off(void)
{
	OLED_WrCmd(0X8D); // SET DCDC命令（开始写电荷泵）
	OLED_WrCmd(0X10); // DCDC OFF（bit2置0关闭电荷泵）
	OLED_WrCmd(0XAE); // DISPLAY OFF（关闭显示）
}

// OLED 设置坐标
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WrCmd(0xb0 + (7 - y));			  //设置页地址
	OLED_WrCmd((x & 0x0f) | 0x00);		  //起始地址低位
	OLED_WrCmd(((x & 0xf0) >> 4) | 0x10); //起始地址高位
}

// OLED填充（每页，每竖行填满bmp_dat，低位在上，1为亮）
void OLED_Fill(unsigned char bmp_dat)
{
	unsigned char y, x;
	for (y = 0; y < 8; y++)
	{
		OLED_WrCmd(0xb0 + y); //页地址(y轴地址)
		OLED_WrCmd(0x00);	  //设定起始地址低位（x轴）
		OLED_WrCmd(0x10);	  //设定起始地址高位（x轴）
		for (x = 0; x < X_WIDTH; x++)
			OLED_WrDat(bmp_dat);
	}
}

// OLED复位（即OLED_Fill(0x00) （填满）0）
void OLED_CLS(void)
{
	unsigned char y, x;
	for (y = 0; y < 8; y++)
	{
		OLED_WrCmd(0xb0 + y); //页地址(y轴地址)
		OLED_WrCmd(0x00);	  //设定起始地址低位（x轴）
		OLED_WrCmd(0x10);	  //设定起始地址高位（x轴）
		for (x = 0; x < X_WIDTH; x++)
			OLED_WrDat(0);
	}
}

//显示6*8一个标准ASCII字符,显示的坐标（x,y），y为页范围0～7
void OLED_P6x8Char(unsigned char x, unsigned char y, unsigned char ch)
{
	unsigned char c = 0, i;
	c = ch - 32;
	OLED_Set_Pos(x, y);		//设置初始坐标
	for (i = 0; i < 6; i++) // 6为字体宽度
		OLED_WrDat(F6x8[c][i]);
}

//显示6*8一组标准ASCII字符串，显示的坐标（x,y），y为页范围0～7
void OLED_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[])
{
	unsigned char c = 0, i = 0, j = 0;
	while (ch[j] != '\0') //判断字符串是否截止
	{
		c = ch[j] - 32;
		if (x > 120) //因为一页最宽为128，所以最后一个字器起始在第128-int(128/6)*6=120列
		{
			x = 0;	   //回到第1列
			y = y + 1; //满后跳到下一页
			if (y > 7)
			{
				break; //超过一个屏幕的显示范围，直接跳出
			}
		}

		OLED_Set_Pos(x, y); //设置第一页初始坐标
		for (i = 0; i < 6; i++)
			OLED_WrDat(F6x8[c][i]);
		OLED_Set_Pos(x, y + 1);
		x += 6; //自动往后6列（字体宽度为6）
		j++;
	}
}

//显示8*16（16<8，所以需要2页）一个标准ASCII字符,显示的坐标（x,y），y为页范围0～7
void OLED_P8x16Char(unsigned char x, unsigned char y, unsigned char ch)
{
	unsigned char c = 0, i;
	c = ch - 32;
	OLED_Set_Pos(x, y);		//设置第一页初始坐标
	for (i = 0; i < 8; i++) // 8为字体宽度
		OLED_WrDat(F8X16[c][i]);
	OLED_Set_Pos(x, y + 1); //设置第二页初始坐标
	for (i = 0; i < 8; i++) // 8为字体宽度
		OLED_WrDat(F8X16[c][i + 8]);
}

//显示8*16一组标准ASCII字符串（16<8，所以需要2页），显示的坐标（x,y），y为页范围0～7
void OLED_P8x16Str(unsigned char x, unsigned char y, unsigned char ch[])
{
	unsigned char c = 0, i = 0, j = 0;
	while (ch[j] != '\0') //判断字符串是否截止
	{
		c = ch[j] - 32;
		if (x > 120) //因为一页最宽为128，所以最后一个字器起始在第120列
		{
			x = 0;	   //回到第1列
			y = y + 2; //满后跳到下两页（因为高度为2，所以要跳两页，最多显示四行）
			if (y > 6)
			{
				break; //超过一个屏幕的显示范围，直接跳出
			}
		}

		OLED_Set_Pos(x, y); //设置第一页初始坐标
		for (i = 0; i < 8; i++)
			OLED_WrDat(F8X16[c][i]);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WrDat(F8X16[c][i + 8]);
		x += 8; //自动往后8列
		j++;
	}
}

//初始化OLED
void OLED_Init(void)
{
	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Set();
	OLED_RST_Set();

	OLED_RST_Clr();			 //硬件复位
	HAL_Delay(100); //等待复位完成
	OLED_RST_Set();
	OLED_WrCmd(0xAE); //关闭显示
	OLED_WrCmd(0xD5); //设置时钟分频因子,震荡频率
	OLED_WrCmd(80);	  //[3:0],分频因子;[7:4],震荡频率
	OLED_WrCmd(0xA8); //设置驱动路数
	OLED_WrCmd(0X3F); //默认0X3F(1/64)
	OLED_WrCmd(0xD3); //设置显示偏移
	OLED_WrCmd(0X00); //默认为0
	OLED_WrCmd(0x40); //设置显示开始行 [5:0],行数.

	OLED_WrCmd(0x8D); //电荷泵设置
	OLED_WrCmd(0x14); // bit2，开启/关闭
	OLED_WrCmd(0x20); //设置内存地址模式
	OLED_WrCmd(0x02); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_WrCmd(0xA1); //段重定义设置,bit0:0,0->0;1,0->127;
	OLED_WrCmd(0xC0); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	OLED_WrCmd(0xDA); //设置COM硬件引脚配置
	OLED_WrCmd(0x12); //[5:4]配置

	OLED_WrCmd(0x81); //对比度设置
	OLED_WrCmd(0x5f); // 1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WrCmd(0xD9); //设置预充电周期
	OLED_WrCmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WrCmd(0xDB); //设置VCOMH 电压倍率
	OLED_WrCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WrCmd(0xA4); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WrCmd(0xA6); //设置显示方式;bit0:1,反相显示;0,正常显示
	OLED_WrCmd(0xAF); //开启显示
	OLED_Fill(0x00);
	OLED_Set_Pos(0, 0);
}

unsigned char oled_overflowstop_flag = 0; //溢出停止标志位（一个屏幕显示不下）
// OLEDPritnf(...)服务子函数，显示6*8一组标准ASCII字符串,显示的坐标（x,y）
void OLED_P6x8CharPutc(unsigned char *x, unsigned char *y, unsigned char ch)
{
	unsigned char c = 0, i = 0;
	if (*x > 120) //判断横轴是否超出界限(120)，如果超出则纵轴换行
	{
		*x = 0;
		(*y) += 1;
	}
	if (*y > 7) //判断纵轴是否超出界限(6)
	{
		*y = 0;
		oled_overflowstop_flag = 1; //超出掷出停止标志位
	}
	if (oled_overflowstop_flag == 0)
	{
		switch (ch)
		{
		case '\r': //回车
		{
			*x = 0;
			return;
		}
		case '\n': //换行
		{
			(*y) += 1;
			return;
		}
		case '\t': // TAB
		{
			(*x) += 24;
			return;
		}
		default: //通用字符显示
		{
			c = ch - 32;
			OLED_Set_Pos(*x, *y);
			for (i = 0; i < 6; i++)
				OLED_WrDat(F6x8[c][i]);

			(*x) += 6;
			break;
		}
		}
	}
}

// OLEDPritnf(...)服务子函数，显示8*16一组标准ASCII字符串，显示的坐标（x,y）
void OLED_P8x16CharPutc(unsigned char *x, unsigned char *y, unsigned char ch)
{
	unsigned char c = 0, i = 0;
	if (*x > 120) //判断横轴是否超出界限(120)，如果超出则纵轴换行
	{
		*x = 0;
		(*y) += 2;
	}
	if (*y > 6) //判断纵轴是否超出界限(6)，如果超出则清屏
	{
		*y = 0;
		oled_overflowstop_flag = 1; //超出掷出停止标志位
	}
	if (oled_overflowstop_flag == 0)
	{
		switch (ch)
		{
		case '\r': //回车
		{
			*x = 0;
			return;
		}
		case '\n': //换行
		{
			(*y) += 2;
			return;
		}
		case '\t': // TAB
		{
			(*x) += 32;
			return;
		}
		default: //通用字符显示
		{
			c = ch - 32;
			OLED_Set_Pos(*x, *y);
			for (i = 0; i < 8; i++)
				OLED_WrDat(F8X16[c][i]);
			OLED_Set_Pos(*x, (*y) + 1);
			for (i = 0; i < 8; i++)
				OLED_WrDat(F8X16[c][i + 8]);
			(*x) += 8;
			break;
		}
		}
	}
}

// OLED格式输出显示函数
uint8_t OLED_buf[PRI_BUF];
void OLEDPritnf(const char *format, ...)
{
	uint16_t i, j;
	va_list ap;
	static unsigned char x = 0, y = 0;
	if (Flag_clear == 1)
	{
		x = 0;
		y = 0;
		OLED_Fill(0x00); //清屏
		Flag_clear = 0;
	}

	va_start(ap, format);
	vsprintf((char *)OLED_buf, format, ap);
	va_end(ap);

	i = strlen((const char *)OLED_buf); //此次发送数据的长度
	for (j = 0; j < i; j++)				//循环发送数据
	{
		OLED_P6x8CharPutc(&x, &y, OLED_buf[j]);
	}
}

//固定位置显示数字或字符
void OLED_Show_Position(u8 x, u8 y, const char *format, ...)
{
	uint16_t i, j;
	va_list ap;
	va_start(ap, format);
	vsprintf((char *)OLED_buf, format, ap);
	va_end(ap);

	i = strlen((const char *)OLED_buf); //此次发送数据的长度
	for (j = 0; j < i; j++)				//循环发送数据
	{
		if (oled_overflowstop_flag == 1)
		{
			oled_overflowstop_flag = 0; //清除停止标志位
			break;
		}
	  //OLED_P6x8CharPutc(&x, &y, OLED_buf[j]);
		OLED_P8x16CharPutc(&x, &y, OLED_buf[j]);
	}
}

//显示显示BMP图片128×64起始点坐标(0,0),x的范围0～127，y为页的范围0～7（图形显示已经是全屏扫，所以不用每一次都进行复位，不然会闪）
void OLED_Draw_BMP(unsigned char BMP[][128])
{
	unsigned char x, y;

	for (y = 0; y < 64; y++)
	{
		for (x = 0; x < 128; x++)
		{
			OLED_Set_Pos(x, y);	   //设置每8竖排点的初始坐标
			OLED_WrDat(BMP[y][x]); //显示每一排
		}
	}
}

// void mode_oled_show()
//{
//	Uc_Array2_All_Num((unsigned char *)oled_picture, 8, 128, 0); //清屏

//	OLED_Show_Printf(0, 0, 1, "motor direction:");
//	OLED_Show_Printf(2, 0, 1, "%s", forward_word);
//	OLED_Show_Printf(4, 0, 1, "right value: %d", 100);
//	OLED_Show_Printf(6, 0, 1, "left  value: %d", 100);

//	OLED_Draw_BMP(oled_picture); //刷屏
//}

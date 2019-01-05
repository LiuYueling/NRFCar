/**********************************************************************
-  File name : delay.c
-  Author : yueling_liu	Version: 0.1	Date: 2018年10月01日星期一
-  Description :	延时函数定义
-  Function List :	
   1. void delay_us(const uint16_t xus);//us delay
   2. void delay_ms(const uint16_t xms);//ms delay
-  History :
   NO.<author>		<time>		<version>	<desc>
   1.yueling_liu	18/10/01	0.1			project initial
**********************************************************************/

//--Header File--//
#include "delay.h"

#ifdef STC_Y5
#if (FOSC == 11059200L)
/**********************************************************************
-  Function :		void SoftDelay500ms(void)
-  Description :	500毫秒延时函数
-  Input :			void
-  Return :			void
-  Others :			@11.0592MHz
**********************************************************************/

//void Delay10us(void)		//@11.0592MHz
//{
//	unsigned char i;

//	_nop_();
//	i = 25;
//	while (--i);
//}

//void Delay100us(void)		//@11.0592MHz
//{
//	unsigned char i, j;

//	_nop_();
//	_nop_();
//	i = 2;
//	j = 15;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

//void Delay5ms(void)		//@11.0592MHz
//{
//	unsigned char i, j;

//	i = 54;
//	j = 199;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

//void Delay10ms(void)		//@11.0592MHz
//{
//	unsigned char i, j;

//	i = 108;
//	j = 145;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

void Delay200ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//void SoftDelay500ms(void)		
//{
//	unsigned char i, j, k;

//	_nop_();
//	_nop_();
//	i = 22;
//	j = 3;
//	k = 227;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}

#endif
#endif

//void Delay(uint16_t n)
//{
//    uint16_t x;

//    while (n--)
//    {
//        x = 5000;
//        while (x--);
//    }
//}

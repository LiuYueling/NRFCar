/**********************************************************************
-  File name : delay.h
-  Author : yueling_liu	Version: 0.1	Date: 2018��10��01������һ
-  Description :System��ʱ����
-  Others :		�����ʱ��POSC�йأ����ȡ��ȷ��ʱʹ�ö�ʱ����ʱ
-  Function List : 
   1. void delay_us(const uint16_t xus);//us delay
   2. void delay_ms(const uint16_t xms);//ms delay
-  History :
   1.Date: ...
     Author: ...
	 Modification: ...
**********************************************************************/
#ifndef __DELAY_H
#define __DELAY_H

//--File Include--//
#include "SYS.H"

//--Type Definition--//
//--Extern Variable--//
//--Interface--//

//--Function Prototype--//
void Delay10us(void);
void Delay100us(void);
void Delay5ms(void);		//@11.0592MHz
void Delay10ms(void);
void Delay200ms(void);
void SoftDelay500ms(void);
void Delay(uint16_t n);
#endif


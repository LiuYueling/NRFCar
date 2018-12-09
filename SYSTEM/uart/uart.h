/**********************************************************************
-  File name : uart.h
-  Author : yueling_liu	Version: 0.1	Date: 2018年10月01日星期一
-  Description ://用于详细说明此程序文件完成的主要功能，与其他模块
				//或函数的接口，输出值，取值范围，含义及参数间的控
				//制、顺序、独立或依赖关系
-  Others :		//其他内容说明
-  Function List : //主要函数列表，每条记录应包括函数名及功能的简要说明
   1. ...
   2. ...
-  History :	//修改历史记录列表，每条修改记录修改日期、修改者
				//以及修改内容
   1.Date: ...
     Author: ...
	 Modification: ...
   2. ...
**********************************************************************/
#ifndef __UART_H
#define __UART_H

//--File Include--//
#include "SYS.H"

//--Type Definition--//
//typedef TypSendString{
//	uint8_t *StrAddr;
//	uint8_t StrCount;
//};

//--Definition--//
//#define BAUD 115200
//#define BAUD (256 - FOSC/32/UART_BAUD)

//--Extern Variable--//


//--Interface--//

//--Function Prototype--//
void UART_Init(void);
//void UART_Init(const uint16_t Baud);
void UART_SendData(const uint8_t Data);
void UART_SendString(uint8_t *Str);
#endif

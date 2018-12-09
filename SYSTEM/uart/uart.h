/**********************************************************************
-  File name : uart.h
-  Author : yueling_liu	Version: 0.1	Date: 2018��10��01������һ
-  Description ://������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
				//�����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
				//�ơ�˳�򡢶�����������ϵ
-  Others :		//��������˵��
-  Function List : //��Ҫ�����б�ÿ����¼Ӧ���������������ܵļ�Ҫ˵��
   1. ...
   2. ...
-  History :	//�޸���ʷ��¼�б�ÿ���޸ļ�¼�޸����ڡ��޸���
				//�Լ��޸�����
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

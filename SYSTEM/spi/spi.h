/**********************************************************************
-  File name : spi.h
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
#ifndef __SPI_H
#define __SPI_H

//--Header File--//
#include "SYS.H"

//--Type Definition--//
#define SPI_S0          0x04
#define SPI_S1          0x08

#define SPIF            0x80                    //SPSTAT.7
#define WCOL            0x40                    //SPSTAT.6

#define SSIG            0x80                    //SPCTL.7
#define SPEN            0x40                    //SPCTL.6
#define DORD            0x20                    //SPCTL.5
#define MSTR            0x10                    //SPCTL.4
#define CPOL            0x08                    //SPCTL.3
#define CPHA            0x04                    //SPCTL.2
#define SPDHH           0x00                    //CPU_CLK/4
#define SPDH            0x01                    //CPU_CLK/16
#define SPDL            0x02                    //CPU_CLK/64
#define SPDLL           0x03                    //CPU_CLK/128

//--Function Prototype--//
void SPI_Init(void);
uint8_t SPI_ReadWriteByte(uint8_t TxData);

#endif


#ifndef _NRF_DT_H
#define _NRF_DT_H

#include "SYS.H"

/**********************************************************************
			NRF_Car ֡���������Զ���Э��

-	Head:֡ͷ				: 16
-	Addr:�ӻ�ʶ����			: 8
-	Cmd:������				: 8
-	Len:Data����Ч���ݸ���	: 8
-	Data:���ݰ�				: 8 
-	SUM Check:����У���	: 8
**********************************************************************/
typedef struct{
	uint8_t Head_H;			//֡ͷH
	uint8_t Head_L;			//֡ͷL
	uint8_t SLAVE_Addr;		//�ӻ���ַ
	uint8_t Command;		//������
	uint8_t Data_Len;		//���ݳ���
	uint8_t *Data_Buff;		//���ݰ�
	uint8_t Sum_Check;		//��У��
}DT_TypeDef;

//typedef struct{
//	uint8_t CH;
//	DT_TypeDef DT_Struct;
//}NRF_DT_TypeDef;

//---HEAD---//
#define HEAD_H 					0xAA	//֡ͷH
#define HEAD_L 					0xAA	//֡ͷL
//---COMMAND---//
#define CMD_OK 					0x00
//---SLAVE CONTROL---//
#define CMD_GET_SLAVE_ADDR		0x00
#define CMD_CHANGE_SLAVE_ADDR	0x00
//---REMOTE CONTROL---//
#define CMD_GET_CONTROL			0x00
#define CMD_ROCKER_BUFF			0x00
//---PID---//
#define CMD_GET_PID				0x00
#define CMD_CHANGE_PID			0x00
#define CMD_INIT_PID			0x00

#define CMD_ERR 				0xFF 
#endif


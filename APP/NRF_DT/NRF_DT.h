#ifndef _NRF_DT_H
#define _NRF_DT_H

#include "SYS.H"

/**********************************************************************
			NRF_Car 帧传输数据自定义协议

-	Head:帧头				: 16
-	Addr:从机识别码			: 8
-	Cmd:功能字				: 8
-	Len:Data区有效数据个数	: 8
-	Data:数据包				: 8 
-	SUM Check:数据校验和	: 8
**********************************************************************/
typedef struct{
	uint8_t Head_H;			//帧头H
	uint8_t Head_L;			//帧头L
	uint8_t SLAVE_Addr;		//从机地址
	uint8_t Command;		//命令字
	uint8_t Data_Len;		//数据长度
	uint8_t *Data_Buff;		//数据包
	uint8_t Sum_Check;		//和校验
}DT_TypeDef;

//typedef struct{
//	uint8_t CH;
//	DT_TypeDef DT_Struct;
//}NRF_DT_TypeDef;

//---HEAD---//
#define HEAD_H 					0xAA	//帧头H
#define HEAD_L 					0xAA	//帧头L
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


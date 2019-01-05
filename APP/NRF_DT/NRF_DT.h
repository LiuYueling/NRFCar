#ifndef _NRF_DT_H
#define _NRF_DT_H

//--Header File--//
#include "MAIN.h"

//--Type Definition--//
#if (ROCKER_SUM == 1)
typedef struct{//摇杆数据结构体
	uint16_t X;				//水平方向
	uint16_t Y;				//垂直方向
	uint8_t  Rocker_Key;	//Rocker key
}RockerTypeDef;
#endif

//--Function Prototype--//
void DT_DATA_INIT(void);//DT数据结构初始化
void NRF_DT(void);

//--Extern Variable--//

//--Definition--//
//#define FOSC	11059200L



#endif






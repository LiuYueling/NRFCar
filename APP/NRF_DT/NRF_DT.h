#ifndef _NRF_DT_H
#define _NRF_DT_H

//--Header File--//
#include "MAIN.h"

//--Type Definition--//
#if (ROCKER_SUM == 1)
typedef struct{//ҡ�����ݽṹ��
	uint16_t X;				//ˮƽ����
	uint16_t Y;				//��ֱ����
	uint8_t  Rocker_Key;	//Rocker key
}RockerTypeDef;
#endif

//--Function Prototype--//
void DT_DATA_INIT(void);//DT���ݽṹ��ʼ��
void NRF_DT(void);

//--Extern Variable--//

//--Definition--//
//#define FOSC	11059200L



#endif






#incldue "NEF_DT.h"
#include "stdint.h"
typedef struct{
	uint8_t Head_H;			//帧头H
	uint8_t Head_L;			//帧头L
	uint8_t SLAVE_Addr;		//从机地址
	uint8_t Command;		//命令字
	uint8_t Data_Len;		//数据长度
	uint8_t *Data_Buff;		//数据包
	uint8_t Sum_Check;		//和校验
}DT_TypeDef;

void NRFSend_Data(DT_TypeDef* _Data_Pack)
{
	uint8_t sat;

	


}


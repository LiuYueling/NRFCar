#incldue "NEF_DT.h"
#include "stdint.h"
typedef struct{
	uint8_t Head_H;			//֡ͷH
	uint8_t Head_L;			//֡ͷL
	uint8_t SLAVE_Addr;		//�ӻ���ַ
	uint8_t Command;		//������
	uint8_t Data_Len;		//���ݳ���
	uint8_t *Data_Buff;		//���ݰ�
	uint8_t Sum_Check;		//��У��
}DT_TypeDef;

void NRFSend_Data(DT_TypeDef* _Data_Pack)
{
	uint8_t sat;

	


}


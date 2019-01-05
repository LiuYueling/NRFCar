#include "NRF_DT.h"

extern volatile bit Time0_Delay_OK_Flag;	//Time0��ʱ�곡��־
extern volatile uint8_t TX_PLOAD_WIDTH;		//RF�����ֽ��������32�ֽ�
extern volatile uint8_t RX_PLOAD_WIDTH;		//RF�����ֽ��������32�ֽ�

#if (ROCKER_SUM == 1)
RockerTypeDef ONE;
RockerTypeDef *RackerStruct_P;
#endif

//#ifdef NRF_CAR_SLAVE 
//uint8_t str[20];
//#endif



void DT_DATA_INIT(void)
{
#if (ROCKER_SUM == 1)
	ONE.X = 0;
	ONE.Y = 0;
	ONE.Rocker_Key = 0;
	RackerStruct_P = &ONE;
#endif
}



void NRF_DT(void)
{	
#ifdef NRF_CAR_MASTER 
	if(Time0_Delay_OK_Flag == 1)
	{/*RF��ʱ��������*/
		Get_Rocker();//���ҡ������
		
		{/*����ҡ������*/	
#if (ROCKER_SUM == 1)	
//			if(NRF24L01_TxPacket(RackerStruct_P) == TX_OK)//�������ݰ�
//			{
//				/*���ͳɹ���LED RUN*/
//				LED_RUN = !LED_RUN;
//				UART_SendString("NRF24L01 TxPacket Send OK\r\n");
//			}
//			else
//			{
//				UART_SendString("NRF24L01 TxPacket Send ERR\r\n");
//			}
#endif	
//#if (ROCKER_SUM == 2)
//			
//#endif	
		}
		Time0_Delay_OK_Flag = 0;
	}
#endif
	
#ifdef NRF_CAR_SLAVE
	
	if(NRF24L01_RxPacket(RackerStruct_P) == 0)//���ܵ����ݰ�
	{
		LED_RUN = !LED_RUN;
		UART_SendString("Get NRF24L01 Rx Packet:\r\n");
#if (ROCKER_SUM == 1)
		sprintf(str, "Rocker_X = %u\t", RackerStruct_P->X);
		UART_SendString(str);
		sprintf(str, "Rocker_Y = %u\r\n", RackerStruct_P->Y);
		UART_SendString(str);
//			sprintf(str, "%u,%u,%u,\r\n", sizeof(unsigned char), sizeof(unsigned int), sizeof(unsigned long));
//			UART_SendString(str);
#endif
//#if (ROCKER_SUM == 2)
//			sprintf(str, "Rocker_L_X = %u\t", Rocker.L.X);
//			UART_SendString(str);
//			sprintf(str, "Rocker_L_Y = %u\r\n", Rocker.L.Y);
//			UART_SendString(str);
//			sprintf(str, "Rocker_R_X = %u\t", Rocker.R.X);
//			UART_SendString(str);
//			sprintf(str, "Rocker_R_Y = %u\r\n", Rocker.R.Y);
//			UART_SendString(str);
//#endif
//			tmp_buf[5] = '\r';
//			tmp_buf[6] = '\n';
//			tmp_buf[7] = '\0';//�����ַ���������
//			UART_SendString(Rocker);    
	}
#endif	//NRF_CAR_SLAVE End
}





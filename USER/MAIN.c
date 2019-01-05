/**********************************************************************
-  File name : MAIN.c
-  Author : yueling_liu	Version: 0.1	Date: 2018��10��01������һ
-  Description :	main
-  History :
   NO.<author>		<time>		<version>	<desc>
   1.yueling_liu	18/10/01	0.1			project initial
**********************************************************************/

//--Header File--//
#include "MAIN.h"

/**********************************************************************
-  Function :		void System_Init(void)
-  Description :	System_Init
**********************************************************************/
void System_Init(void)
{
	/*MCLK Init*/
	CLK_DIV = 0x00;	
	
	{/*IO_Init; P0-P7 IO_MODE:׼˫��IO*/
		P0M0 = 0x00;
		P0M1 = 0x00;
		P1M0 = 0x00;
		P1M1 = 0x00;
		P2M0 = 0x00;
		P2M1 = 0x00;
		P3M0 = 0x00;
		P3M1 = 0x00;
		P4M0 = 0x00;
		P4M1 = 0x00;
		P5M0 = 0x00;
		P5M1 = 0x00;
		P6M0 = 0x00;
		P6M1 = 0x00;
		P7M0 = 0x00;
		P7M1 = 0x00;
	}
	
	{/*LED_RUN OFF*/
		LED_RUN = 1;			//LED OFF
	}

	{/*IO Init*/

#ifdef NRF_CAR_MASTER
{
	
}
#endif

/*Output IO Init*/
#ifdef NRF_CAR_SLAVE
{
		
}
#endif
	}
	
	EA = 1;				//�������ж�
	
#if (TEST_MODE == 1)	//UART Lock
{
	UART_Init();		//���ڳ�ʼ��
}
#endif
	
#ifdef NRF_CAR_MASTER
{
	UART_SendString("NRF CAR MASTER DEMO\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
}
#endif

#ifdef NRF_CAR_SLAVE
{
	UART_SendString("NRF CAR SLAVE DEMO\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
}
#endif

	NRF24L01_Init();	//NRF24L01��ʼ��
	UART_SendString("NRF24L01 Init\r\n");
	UART_SendString("NRF24L01 Check...\r\n");
	while(NRF24L01_Check())//���NRF�Ƿ����
	{
		Delay200ms();
		UART_SendString("NRF24L01 Check Error\r\n");
	}
	UART_SendString("NRF24L01 Check OK\r\n");
	
#ifdef NRF_CAR_MASTER 
{
	/*�������س�ʼ��*/
	NRF24L01_TX_Mode();//����NRF24L01ΪTxģʽ
	UART_SendString("NRF24L01 TX Mode\r\n");
	Rocker_init();//ҡ�������ʼ��
	Timer0_1MS_Init(200);	//Timer0��ʼ����200ms��ʱ
	UART_SendString("Timer0 Init\r\n");
}
#endif

#ifdef NRF_CAR_SLAVE
{
	/*���ջ���س�ʼ��*/
	NRF24L01_RX_Mode();//����NRF24L01��RXģʽ
	UART_SendString("NRF24L01 RX Mode\r\n");
	
		//����˶���س�ʼ��
}
#endif
	DT_DATA_INIT();//����Э�����ݽṹ��ʼ��
	UART_SendString("System Init OK\r\n");
}


/**********************************************************************
-  Function :		int main(void)
-  Description :	main
**********************************************************************/
int main(void)
{
	System_Init();//ϵͳ��ʼ��
	
	while(1)
	{
		NRF_DT();
	}
	
}







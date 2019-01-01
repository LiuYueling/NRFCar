/**********************************************************************
-  File name : MAIN.c
-  Author : yueling_liu	Version: 0.1	Date: 2018��10��01������һ
-  Description :	main
-  History :
   NO.<author>		<time>		<version>	<desc>
   1.yueling_liu	18/10/01	0.1			project initial
**********************************************************************/

//--Header File--//
#include "SYS.H"
#include "delay.h"
#include "uart.h"
#include "timer.h"
#include "NRF24L01.h"
#include "spi.h"
#include "adc.h"
#include "Rocker.h"
#include "NRF_DT.h"

sbit LED_RUN = P5^4;
sbit Rocker1_Key = P2^2;
//sbit Rocker2_Key = P2^3;
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
/*Rocker1_Key IO Init*/
#ifdef NRF_CAR_MASTER
{
	#if (ROCKER_SUM == 1)
	{
		Rocker1_Key = 1;
	}
	#endif
	#if (ROCKER_SUM == 2)
	{
		Rocker1_Key = 1;
		Rocker2_Key = 1;
	}
	#endif
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
	Timer0_1MS_Init();	//Timer0��ʼ��
	UART_SendString("Timer0 Init\r\n");
}
#endif

#if NRF_CAR_SLAVE
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
	Delay200ms();
	
#ifdef NRF_CAR_MASTER 
{
	/*�������س�ʼ��*/
	NRF24L01_TX_Mode();//����NRF24L01ΪTxģʽ
	UART_SendString("NRF24L01 TX Mode\r\n");
	Adc_Init();//ADC��ʼ��
}
#endif

#if NRF_CAR_SLAVE
{
	/*���ջ���س�ʼ��*/
	NRF24L01_RX_Mode();//����NRF24L01��RXģʽ
	UART_SendString("NRF24L01 RX Mode\r\n");
	
		//����˶���س�ʼ��
}
#endif
	
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







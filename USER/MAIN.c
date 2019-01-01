/**********************************************************************
-  File name : MAIN.c
-  Author : yueling_liu	Version: 0.1	Date: 2018年10月01日星期一
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
	
	{/*IO_Init; P0-P7 IO_MODE:准双向IO*/
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
	
	EA = 1;				//开启总中断
	
#if (TEST_MODE == 1)	//UART Lock
{
	UART_Init();		//串口初始化
}
#endif
	
#ifdef NRF_CAR_MASTER
{
	UART_SendString("NRF CAR MASTER DEMO\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
	Timer0_1MS_Init();	//Timer0初始化
	UART_SendString("Timer0 Init\r\n");
}
#endif

#if NRF_CAR_SLAVE
{
	UART_SendString("NRF CAR SLAVE DEMO\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
}
#endif
	
	NRF24L01_Init();	//NRF24L01初始化
	UART_SendString("NRF24L01 Init\r\n");
	UART_SendString("NRF24L01 Check...\r\n");
	while(NRF24L01_Check())//检查NRF是否存在
	{
		Delay200ms();
		UART_SendString("NRF24L01 Check Error\r\n");
	}
	UART_SendString("NRF24L01 Check OK\r\n");
	Delay200ms();
	
#ifdef NRF_CAR_MASTER 
{
	/*发射机相关初始化*/
	NRF24L01_TX_Mode();//配置NRF24L01为Tx模式
	UART_SendString("NRF24L01 TX Mode\r\n");
	Adc_Init();//ADC初始化
}
#endif

#if NRF_CAR_SLAVE
{
	/*接收机相关初始化*/
	NRF24L01_RX_Mode();//配置NRF24L01到RX模式
	UART_SendString("NRF24L01 RX Mode\r\n");
	
		//电机运动相关初始化
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
	System_Init();//系统初始化
	
	while(1)
	{
		NRF_DT();
	}
	
}







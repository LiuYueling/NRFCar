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
#include "stdio.h"
#include "intrins.h"
#include "NRF24L01.h"
#include "spi.h"
#include "adc.h"
#include "Rocker.h"

extern volatile bit UART_Txd_Pre_OK_Flag;
//extern volatile uint16_t ADC_BUFF_CH_0_1_6_7[4];
extern volatile uint16_t ADC_BUFF[2];



volatile bit Delay_Time0_500ms_Flag = 0;
xdata uint8_t tmp_buf[16];
xdata uint8_t Tx_tmp_buff[32] = "abcdefghijklmnopqrstyuwxyz12345";

sbit LED_RUN = P5^4;
sbit Rocker1_Key = P2^2;
//sbit Rocker2_Key = P2^3;

void System_Init(void)
{
	/*MCLK Init*/
	CLK_DIV = 0x00;	
	
	/*IO_Init; P0-P7 IO_MODE:准双向IO*/
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
	
	LED_RUN = 1;			//LED OFF
#ifdef NRF_CAR_MASTER
	Rocker1_Key = 1;
//	Rocker2_Key = 1;
#elif defined NRF_CAR_SLAVE
	
#endif
	
	EA = 1;				//开启总中断
	
#if (TEST_MODE == 1)	//TEST
	UART_Init();		//串口初始化
#endif
	
#ifdef NRF_CAR_MASTER
	UART_SendString("NRF CAR MASTER DEMO\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
#elif defined NRF_CAR_SLAVE
	UART_SendString("NRF CAR SLAVE\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
#endif
	
	Timer0_1MS_Init();	//Timer0初始化
	NRF24L01_Init();	//NRF24L01初始化
	
#ifdef NRF_CAR_MASTER
//	Adc_Init();			//ADC初始化
#elif defined NRF_CAR_SLAVE
	
#endif
	
}


/**********************************************************************
-  Function :		int main(void)
-  Description :	main
**********************************************************************/
int main(void)
{
	System_Init();//系统初始化
	UART_SendString("System Init OK\r\n");
	UART_SendString("NRF24L01 Check...\r\n");
	
	while(NRF24L01_Check())//检查NRF是否存在
	{
		Delay200ms();
		UART_SendString("NRF24L01 Check Error\r\n");
	}
	UART_SendString("NRF24L01 Check OK\r\n");
	
#ifdef NRF_CAR_MASTER
	NRF24L01_TX_Mode();//配置NRF24L01为Tx模式
	UART_SendString("NRF24L01 TX Mode\r\n");
#elif defined NRF_CAR_SLAVE
	NRF24L01_RX_Mode();//配置NRF24L01到RX模式
	UART_SendString("NRF24L01 RX Mode\r\n");
#endif
	
	while(1)
	{
		if(Delay_Time0_500ms_Flag == 1)
		{
#ifdef NRF_CAR_MASTER
//			Get_Rocker();//获得摇杆数据
//			UART_SendString("Get Rocker...\r\n");
//		sprintf(tmp_buf, "Hello World \r\n");
		
			//
			if(NRF24L01_TxPacket(Tx_tmp_buff) == TX_OK)
			{
				UART_SendString("NRF24L01 TxPacket Send OK");
			}
			else
			{
				UART_SendString("NRF24L01 TxPacket Send ERR");
			}
#elif defined NRF_CAR_SLAVE
		
#endif
//			LED_RUN = !LED_RUN;
			Delay_Time0_500ms_Flag = 0;
		}
		
#ifdef NRF_CAR_MASTER
//		if(NRF24L01_TxPacket("Hello World\r\n") == TX_OK)
//		{
//			Delay200ms();
//		}
#elif defined NRF_CAR_SLAVE
		if(NRF24L01_RxPacket(tmp_buf) == 0)//一旦接收到信息,则显示出来.
		{
			UART_SendString("Get NRF24L01 Rx Packet:\r\n");
			tmp_buf[29] = '\r';
			tmp_buf[30] = '\n';
			tmp_buf[31] = '\0';//加入字符串结束符
			UART_SendString(tmp_buf);    
		}
#endif
	}
	
}







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
xdata uint8_t tmp_buf[32];

sbit LED = P5^4;
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
	
	LED = 1;			//LED OFF
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
	UART_SendString("NRF_CAR_MASTER DEMO\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
#elif defined NRF_CAR_SLAVE
	UART_SendString("NRF_CAR_SLAVE\r\n");
	UART_SendString("DEMO Version: 0.1\r\n");
#endif
	
	Timer0_1MS_Init();	//Timer0初始化
	NRF24L01_Init();	//NRF24L01初始化
	
#ifdef NRF_CAR_MASTER
	Adc_Init();			//ADC初始化
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
	UART_SendString("NRF24L01 Check\r\n");
	
	while(NRF24L01_Check())
	{
		Delay200ms();
		UART_SendString("NRF24L01 Error\r\n");
	}
	UART_SendString("NRF24L01 OK\r\n");
	
#ifdef NRF_CAR_MASTER
	NRF24L01_TX_Mode();//配置NRF24L01为Tx模式
#elif defined NRF_CAR_SLAVE
	NRF24L01_RX_Mode();//配置NRF24L01到RX模式
#endif
	
	while(1)
	{
		
//		if(Delay_Time0_500ms_Flag == 1)
		{
			Delay_Time0_500ms_Flag = 0;
			
#ifdef NRF_CAR_MASTER
			Get_Rocker();//获得摇杆数据
#elif defined NRF_CAR_SLAVE
			
#endif
			LED = !LED;
		}
		
#ifdef NRF_CAR_MASTER
		
#elif defined NRF_CAR_SLAVE
		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
		{
			tmp_buf[29] = '\r';
			tmp_buf[30] = '\n';
			tmp_buf[31] = '\0';//加入字符串结束符
			UART_SendString(tmp_buf);    
		}
#endif
	}
	
}







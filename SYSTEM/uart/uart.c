/**********************************************************************
-  File name : uart.c
-  Author : yueling_liu	Version: 0.1	Date: 2018.10.01 MO
-  Description :	串口函数定义
-  Function List :	
   1. void delay_us(const uint16_t xus);//us delay
   2. void delay_ms(const uint16_t xms);//ms delay
-  History :
   NO.<author>		<time>		<version>	<desc>
   1.yueling_liu	18/10/01	0.1			project initial
**********************************************************************/

//--Header File--//
#include "uart.h"
#include "delay.h"

#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

//#define UART_PARITYBIT  NONE_PARITY   //定义校验位

volatile bit UART_Txd_Pre_OK_Flag = 1;	//上一次发送完成标志

/**********************************************************************
-  Function :		void UART_Init(void)
-  Description :	UART
-  Input :			void
-  Return :			void
-  Others :			Timer 2; UART 中断优先;
**********************************************************************/
void UART_Init(void)
{
	uint8_t Buff;
	
	Buff = P_SW1;
    Buff &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = Buff;                //(P3.0/RxD, P3.1/TxD)
    
//  Buff = P_SW1;
//  Buff &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
//  Buff |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
//  P_SW1 = Buff;  
//  
//  Buff = P_SW1;
//  Buff &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
//  Buff |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
//  P_SW1 = Buff; 
	
#if (UART_PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8位可变波特率
#elif (UART_PARITYBIT == ODD_PARITY) || (UART_PARITYBIT == EVEN_PARITY)	\
	|| (UART_PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9位可变波特率,校验位初始为1
#elif (UART_PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9位可变波特率,校验位初始为0
#endif
	
    T2L = (65536 - (FOSC/4/UART_BAUD));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/UART_BAUD))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器
    PS = 1;			//串口中断优先
		ES = 1;			//使能串口1中断
}

/**********************************************************************
-  Function :		void UART_SendData(const uint8_t Data)
-  Description :	UART发送8bit数据
-  Input :			const uint8_t Data;
-  Return :			void
-  Others :			校验全局定义在
**********************************************************************/
void UART_SendData(const uint8_t Data)
{	
	uint8_t buff;
	
	while(1)
	{
		if(UART_Txd_Pre_OK_Flag == 1)//上一次数据发送完成
		{
			UART_Txd_Pre_OK_Flag = 0;
			EA = 0;
			buff = Data;
			if (buff&0x01 == 0x01)                     //根据P来设置校验位
			{
#if (UART_PARITYBIT == ODD_PARITY)
				TB8 = 0;                //设置校验位为0
#elif (UART_PARITYBIT == EVEN_PARITY)
				TB8 = 1;                //设置校验位为1
#endif
			}
			else
			{
#if (UART_PARITYBIT == ODD_PARITY)
				TB8 = 1;                //设置校验位为1
#elif (UART_PARITYBIT == EVEN_PARITY)
				TB8 = 0;                //设置校验位为0
#endif
			}
			EA = 1;
			
			SBUF = Data;
			return ;
		}
	}
}


/**********************************************************************
-  Function :		void UART_SendString(uint8_t *Str)
-  Description :	UART发送字符串函数
-  Input :			uint8_t *Str
-  Return :			void	
-  Others :			
**********************************************************************/
void UART_SendString(uint8_t *Str)
{
#if (TEST_MODE == 1)	//TEST
	while(*Str != '\0')
	{
		UART_SendData(*Str++);
	}
#endif
}



/**********************************************************************
-  Function :		void InterruptUART() interrupt 4 using 1
-  Description :	UART中断服务函数
-  Input :			void
-  Return :			void	
-  Others :			占用T2定时器; UART中断优先级最高; 中断4;
**********************************************************************/
void UART_Time1_Interruption(void) interrupt 4
{
    if (RI)
    {
        RI = 0;                 //清除RI位
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        UART_Txd_Pre_OK_Flag = 1;//发送完成置发送完成标志
    }
}



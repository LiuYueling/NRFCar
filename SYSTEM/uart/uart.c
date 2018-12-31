/**********************************************************************
-  File name : uart.c
-  Author : yueling_liu	Version: 0.1	Date: 2018.10.01 MO
-  Description :	���ں�������
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

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��

//#define UART_PARITYBIT  NONE_PARITY   //����У��λ

volatile bit UART_Txd_Pre_OK_Flag = 1;	//��һ�η�����ɱ�־

/**********************************************************************
-  Function :		void UART_Init(void)
-  Description :	UART
-  Input :			void
-  Return :			void
-  Others :			Timer 2; UART �ж�����;
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
    SCON = 0x50;                //8λ�ɱ䲨����
#elif (UART_PARITYBIT == ODD_PARITY) || (UART_PARITYBIT == EVEN_PARITY)	\
	|| (UART_PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (UART_PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif
	
    T2L = (65536 - (FOSC/4/UART_BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/UART_BAUD))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
    PS = 1;			//�����ж�����
		ES = 1;			//ʹ�ܴ���1�ж�
}

/**********************************************************************
-  Function :		void UART_SendData(const uint8_t Data)
-  Description :	UART����8bit����
-  Input :			const uint8_t Data;
-  Return :			void
-  Others :			У��ȫ�ֶ�����
**********************************************************************/
void UART_SendData(const uint8_t Data)
{	
	uint8_t buff;
	
	while(1)
	{
		if(UART_Txd_Pre_OK_Flag == 1)//��һ�����ݷ������
		{
			UART_Txd_Pre_OK_Flag = 0;
			EA = 0;
			buff = Data;
			if (buff&0x01 == 0x01)                     //����P������У��λ
			{
#if (UART_PARITYBIT == ODD_PARITY)
				TB8 = 0;                //����У��λΪ0
#elif (UART_PARITYBIT == EVEN_PARITY)
				TB8 = 1;                //����У��λΪ1
#endif
			}
			else
			{
#if (UART_PARITYBIT == ODD_PARITY)
				TB8 = 1;                //����У��λΪ1
#elif (UART_PARITYBIT == EVEN_PARITY)
				TB8 = 0;                //����У��λΪ0
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
-  Description :	UART�����ַ�������
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
-  Description :	UART�жϷ�����
-  Input :			void
-  Return :			void	
-  Others :			ռ��T2��ʱ��; UART�ж����ȼ����; �ж�4;
**********************************************************************/
void UART_Time1_Interruption(void) interrupt 4
{
    if (RI)
    {
        RI = 0;                 //���RIλ
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
        UART_Txd_Pre_OK_Flag = 1;//��������÷�����ɱ�־
    }
}



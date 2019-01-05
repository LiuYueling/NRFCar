#include "timer.h"


#define T0H_Buff 0xD4	//500us
#define T0L_Buff 0xCD


volatile bit Time0_Delay_OK_Flag = 0;	//��ʱ��ɱ�־
volatile uint16_t Time0_Delay_Time_500uS = 0;	//��ʱx*500uSʱ��

/**********************************************************************
-  Function :		void Timer0_1MS_Init(uint16_t xms)
-  Description :	��ʱ��0��500us��ʱ�жϳ�ʼ��
-  Input :			void
-  Return :			void	
-  Others :			T0��ʱ;���ʱʱ��Ϊ3S����СΪ1Ms
**********************************************************************/
void Timer0_1MS_Init(uint16_t xms)
{
	if(xms > 3000) 
		xms = 3000;//��ֹ������־���
	Time0_Delay_Time_500uS = xms*2;	//װ�ض�ʱʱ��
	
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = T0L_Buff;		//���ö�ʱ��ֵ
	TH0 = T0H_Buff;		//���ö�ʱ��ֵ
	TF0 = 0;			//���TF0��־
	ET0 = 1;    		//ʹ��T0�ж�
	TR0 = 1;			//����T0

}

/**********************************************************************
-  Function :		void Time0_interruption() interrupt 1
-  Description :	��ʱ��0��ʱ�жϺ���
-  Input :			void
-  Return :			void	
-  Others :			T0��ʱ; �ж�1;
**********************************************************************/
void Time0_Interruption(void) interrupt 1
{
	static volatile uint16_t Time0_Delay_Count_Buff = 0;
	
	if(++Time0_Delay_Count_Buff >= Time0_Delay_Time_500uS)	
	{
		Time0_Delay_Count_Buff = 0;
		
		Time0_Delay_OK_Flag = 1;
	}
}


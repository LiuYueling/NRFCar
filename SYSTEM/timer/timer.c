#include "timer.h"


#define T0H_Buff 0xD4	//500us
#define T0L_Buff 0xCD

extern volatile bit Delay_Time0_500ms_Flag;

void Timer0_1MS_Init(void)
{
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
	static volatile uint16_t Delay_Count_Buff = 0;
	
	Delay_Count_Buff++;
	
	if(Delay_Count_Buff >= 1000)	
	{
		Delay_Count_Buff = 0;
		
		Delay_Time0_500ms_Flag = 1;
	}
}


#include "timer.h"


#define T0H_Buff 0xD4	//500us
#define T0L_Buff 0xCD


volatile bit Delay_Time0_500ms_Flag = 0;
void Timer0_1MS_Init(void)
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = T0L_Buff;		//设置定时初值
	TH0 = T0H_Buff;		//设置定时初值
	TF0 = 0;			//清除TF0标志
	ET0 = 1;    		//使能T0中断
	TR0 = 1;			//启动T0

}

/**********************************************************************
-  Function :		void Time0_interruption() interrupt 1
-  Description :	定时器0定时中断函数
-  Input :			void
-  Return :			void	
-  Others :			T0计时; 中断1;
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


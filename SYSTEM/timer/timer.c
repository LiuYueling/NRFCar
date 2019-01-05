#include "timer.h"


#define T0H_Buff 0xD4	//500us
#define T0L_Buff 0xCD


volatile bit Time0_Delay_OK_Flag = 0;	//定时完成标志
volatile uint16_t Time0_Delay_Time_500uS = 0;	//定时x*500uS时间

/**********************************************************************
-  Function :		void Timer0_1MS_Init(uint16_t xms)
-  Description :	定时器0，500us定时中断初始化
-  Input :			void
-  Return :			void	
-  Others :			T0计时;最大定时时间为3S，最小为1Ms
**********************************************************************/
void Timer0_1MS_Init(uint16_t xms)
{
	if(xms > 3000) 
		xms = 3000;//防止计数标志溢出
	Time0_Delay_Time_500uS = xms*2;	//装载定时时间
	
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
	static volatile uint16_t Time0_Delay_Count_Buff = 0;
	
	if(++Time0_Delay_Count_Buff >= Time0_Delay_Time_500uS)	
	{
		Time0_Delay_Count_Buff = 0;
		
		Time0_Delay_OK_Flag = 1;
	}
}


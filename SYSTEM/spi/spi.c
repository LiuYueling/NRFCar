/**********************************************************************
-  File name : spi.c
-  Author : yueling_liu	Version: 0.1	Date: 2018年10月01日星期一
-  Description :	硬件SPI
-  History :
   NO.<author>		<time>		<version>	<desc>
   1.yueling_liu	18/10/01	0.1			project initial
**********************************************************************/

#include "spi.h"

volatile bit SPI_Busy_Flag = 1;

/**********************************************************************
-  Function :		void SPI_Init(void)
-  Description :	SPI Init
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void SPI_Init(void)
{
	SPDAT = 0x00;//初始化SPI数据

//	#define SFR_SPSTAT_PSIF_INIT	1	//传输完成标志
//	#define SFR_SPSTAT_WCOL_INIT	1	//SPI写冲突
//	SPSTAT = (SFR_SPSTAT_PSIF_INIT<<7)|(SFR_SPSTAT_WCOL_INIT<<6);
	
//	SPSTAT = 0xC0;
	
	SPSTAT = SPIF | WCOL;				//清除SPI状态
	
//	#define SFR_SPCTL_SSIG_INIT		1	//SFR_SPCTL_MSRT 确定器件为主机还是从机:由MSTR决定主从机
//	#define SFR_SPCTL_SPEN_INIT		1	//SPI使能
//	#define SFR_SPCTL_DORD_INIT		1	//数据顺序:MSB
//	#define SFR_SPCTL_MSTR_INIT		1	//SPI Mode:Master
//	#define SFR_SPCTL_CPOL_INIT		0	//SPI CPOL:串行同步时钟的空闲状态为低电平
//	#define SFR_SPCTL_CPHA_INIT		0	//SPI CPHA:串行同步时钟的第1个跳变沿（上升或下降）数据被采样
//	#define SFR_SPCTL_SPRx_INIT		0	//SPI SCLK: 0:CPU_CLK/4 = 11.0592MHz/4 = 2.7648MHz
//	SPCTL =  (SFR_SPCTL_SSIG_INIT<<7)|(SFR_SPCTL_SPEN_INIT<<6)|(SFR_SPCTL_DORD_INIT<<5)
//			|(SFR_SPCTL_MSTR_INIT<<4)|(SFR_SPCTL_CPOL_INIT<<3)|(SFR_SPCTL_CPHA_INIT<<2)
//			| SFR_SPCTL_SPRx_INIT;
//	SPCTL = 0xF0;
	
	SPCTL = SSIG | SPEN | MSTR;			//设置SPI为主模式
	
	IE2 |= 0x02; //允许SPI中断
}

/**********************************************************************
-  Function :		uint8_t SPI_ReadWriteByte(uint8_t TxData)
-  Description :	SPI读写一个字节
-  Input :			uint8_t TxData;发送字节
-  Return :			uint8_t RxData:接收字节
-  Others :			使用此函数前判断总线是否空闲;
					SPI CS = 0;
**********************************************************************/
uint8_t SPI_ReadWriteByte(uint8_t TxData)
{
	while(SPI_Busy_Flag);
	SPI_Busy_Flag = 1;		//SPI BUS Busy
	SPDAT = TxData;			//触发SPI发送
	while(SPI_Busy_Flag);	//等待SPI数据传输完成
	
	return SPDAT;
}

/**********************************************************************
-  Function :		void SPI_Interruption(void) interrupt 9
-  Description :	SPI中断服务函数
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void SPI_Interruption(void) interrupt 9
{
	SPSTAT = 0x80|0x40;//清除SPI状态位
	
	SPI_Busy_Flag = 0;
}



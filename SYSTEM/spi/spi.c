/**********************************************************************
-  File name : spi.c
-  Author : yueling_liu	Version: 0.1	Date: 2018��10��01������һ
-  Description :	Ӳ��SPI
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
	SPDAT = 0x00;//��ʼ��SPI����

//	#define SFR_SPSTAT_PSIF_INIT	1	//������ɱ�־
//	#define SFR_SPSTAT_WCOL_INIT	1	//SPIд��ͻ
//	SPSTAT = (SFR_SPSTAT_PSIF_INIT<<7)|(SFR_SPSTAT_WCOL_INIT<<6);
	
//	SPSTAT = 0xC0;
	
	SPSTAT = SPIF | WCOL;				//���SPI״̬
	
//	#define SFR_SPCTL_SSIG_INIT		1	//SFR_SPCTL_MSRT ȷ������Ϊ�������Ǵӻ�:��MSTR�������ӻ�
//	#define SFR_SPCTL_SPEN_INIT		1	//SPIʹ��
//	#define SFR_SPCTL_DORD_INIT		1	//����˳��:MSB
//	#define SFR_SPCTL_MSTR_INIT		1	//SPI Mode:Master
//	#define SFR_SPCTL_CPOL_INIT		0	//SPI CPOL:����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
//	#define SFR_SPCTL_CPHA_INIT		0	//SPI CPHA:����ͬ��ʱ�ӵĵ�1�������أ��������½������ݱ�����
//	#define SFR_SPCTL_SPRx_INIT		0	//SPI SCLK: 0:CPU_CLK/4 = 11.0592MHz/4 = 2.7648MHz
//	SPCTL =  (SFR_SPCTL_SSIG_INIT<<7)|(SFR_SPCTL_SPEN_INIT<<6)|(SFR_SPCTL_DORD_INIT<<5)
//			|(SFR_SPCTL_MSTR_INIT<<4)|(SFR_SPCTL_CPOL_INIT<<3)|(SFR_SPCTL_CPHA_INIT<<2)
//			| SFR_SPCTL_SPRx_INIT;
//	SPCTL = 0xF0;
	
	SPCTL = SSIG | SPEN | MSTR;			//����SPIΪ��ģʽ
	
	IE2 |= 0x02; //����SPI�ж�
}

/**********************************************************************
-  Function :		uint8_t SPI_ReadWriteByte(uint8_t TxData)
-  Description :	SPI��дһ���ֽ�
-  Input :			uint8_t TxData;�����ֽ�
-  Return :			uint8_t RxData:�����ֽ�
-  Others :			ʹ�ô˺���ǰ�ж������Ƿ����;
					SPI CS = 0;
**********************************************************************/
uint8_t SPI_ReadWriteByte(uint8_t TxData)
{
	while(SPI_Busy_Flag);
	SPI_Busy_Flag = 1;		//SPI BUS Busy
	SPDAT = TxData;			//����SPI����
	while(SPI_Busy_Flag);	//�ȴ�SPI���ݴ������
	
	return SPDAT;
}

/**********************************************************************
-  Function :		void SPI_Interruption(void) interrupt 9
-  Description :	SPI�жϷ�����
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void SPI_Interruption(void) interrupt 9
{
	SPSTAT = 0x80|0x40;//���SPI״̬λ
	
	SPI_Busy_Flag = 0;
}



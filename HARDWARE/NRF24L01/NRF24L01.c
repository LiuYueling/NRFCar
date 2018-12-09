
#include "NRF24L01.h"
#include "spi.h"
extern volatile bit SPI_Busy_Flag;
const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ

/**********************************************************************
-  Function :		void NRF24L01_Init(void)
-  Description :	NRF24L01��ʼ��
-  Input :			void
-  Return :			void
-  Others :			NRF24L01_CE			-> P5^4	
					NRF24L01_SPI_CSN	-> P1^2
					NRF24L01_SPI_MOSI	-> P1^3
					NRF24L01_SPI_MISO	-> P1^4
					NRF24L01_SPI_SCLK	-> P1^5
					NRF24L01_IRQ		-> P3^2
**********************************************************************/
void NRF24L01_Init(void)
{
	//IO Mode:
	//NRF24L01_CE		PP			O
	//NRF24L01_SPI_CSN	PP			O
	//NRF24L01_SPI_MOSI	PP			O
	//NRF24L01_SPI_MISO	׼˫��IO	I
	//NRF24L01_SPI_SCLK	PP			O
	P2M0 &= 0xEF;
	P2M0 |= 0x2C;
	P2M1 &= 0xC3;
	P2M1 |= 0x00;
	NRF24L01_SPI_CSN  = 1; //SPIƬѡȡ��
	NRF24L01_SPI_MOSI = 1; //ǿ����
	NRF24L01_SPI_MISO = 1; //������
	NRF24L01_SPI_SCLK = 0; //����ͬ��ʱ�ӵĿ���״̬Ϊ��
	
	//NRF24L01_CE 		PP			O
	P5M0 &= 0xFF;
	P5M0 |= 0x20;
	P5M1 &= 0xDF;
	P5M1 |= 0x00;
	NRF24L01_CE = 1; //ȥ��NRF24L01
	
	//NRF24L01_IRQ		׼˫��IO	I
	P3M0 &= 0xF7;
	P3M0 |= 0x00;
	P3M1 &= 0xF7;
	P3M1 |= 0x00;
	NRF24L01_IRQ = 1; //����NRF24L01_IRQ,׼����ȡNRF24L01_IRQ
	
	
	SPI_Init();//��ʼ��NRF24L01_SPI
	
	SPI_Busy_Flag = 0;
	NRF24L01_CE = 0; //Enable NRF24L01
	NRF24L01_SPI_CSN  = 1; //SPIƬѡȡ��
}

/**********************************************************************
-  Function :		void NRF24L01_Init(void)
-  Description :	���NRF24L01�Ƿ����
-  Input :			void
-  Return :			uint8_t 0:�ɹ�;1:ʧ��
-  Others :			ͨ��д���͵�ַ�б�SPI�Ƿ���ͨ
**********************************************************************/
uint8_t NRF24L01_Check(void)
{
	volatile uint8_t buf[5]={0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
	uint8_t i;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR, buf, 5);//д��5���ֽڵĵ�ַ.		
	NRF24L01_Read_Buf(TX_ADDR, buf, 5); //����д��ĵ�ַ
	for(i=0;i<5;i++)
		if(buf[i]!=0xA5) break; 							   
	
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Write_Reg(uint8_t reg, uint8_t Data)
-  Description :	д�Ĵ���
-  Input :			uint8_t reg: �Ĵ�����ַ
					uint8_t Data: д�������
-  Return :			uint8_t status:	״ֵ̬
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Write_Reg(uint8_t Reg, uint8_t Data)
{
	uint8_t status;
	
	NRF24L01_SPI_CSN = 0;				//ʹ��SPI����
	status = SPI_ReadWriteByte(Reg);	//���ͼĴ�����
	SPI_ReadWriteByte(Data);			//д��Ĵ�����ֵ
	NRF24L01_SPI_CSN = 1;				//ȥ��SPI����
	
	return (status);					//����״ֵ̬
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Read_Reg(uint8_t reg)
-  Description :	��ȡ�Ĵ���
-  Input :			uint8_t reg: �Ĵ�����ַ
-  Return :			uint8_t Reg_Data: �Ĵ�����ֵ
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Read_Reg(uint8_t Reg)
{
	uint8_t Reg_Data;
	
	NRF24L01_SPI_CSN = 0;				//ʹ��SPI����
	SPI_ReadWriteByte(Reg);				//���ͼĴ�����
	Reg_Data = SPI_ReadWriteByte(0xFF);	//��ȡ�Ĵ�����ֵ
	NRF24L01_SPI_CSN = 1;				//ȥ��SPI����
	
	return (Reg_Data);					//����״ֵ̬
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Read_Buf(uint8_t, uint8_t*, uint8_t)
-  Description :	��ָ��λ�ö���ָ�����ȵ�����
-  Input :			uint8_t reg: �Ĵ�����ַ
					uint8_t *pBuf: ����ָ��
					uint8_t len: ���ݳ���
-  Return :			uint8_t Reg_Data: �Ĵ�����ֵ
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Read_Buf(uint8_t Reg, uint8_t *p_Buf, uint8_t Len)
{
	uint8_t status, u8_ctr;
	
	NRF24L01_SPI_CSN = 0;				//ʹ��SPI����
	status = SPI_ReadWriteByte(Reg);	//���ͼĴ�����
	for(u8_ctr=0; u8_ctr<Len; u8_ctr++) //��������
		p_Buf[u8_ctr] = SPI_ReadWriteByte(0xFF);
	NRF24L01_SPI_CSN = 1;				//ȥ��SPI����
	
	return (status);					//����״ֵ̬
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Write_Buf(uint8_t, uint8_t*, uint8_t)
-  Description :	��ָ��λ��д��ָ�����ȵ�����
-  Input :			uint8_t reg: �Ĵ�����ַ
					uint8_t *pBuf: ����ָ��
					uint8_t len: ���ݳ���
-  Return :			uint8_t status:	״ֵ̬
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Write_Buf(uint8_t Reg, uint8_t *p_Buf, uint8_t Len)
{
	uint8_t status,u8_ctr;
	
	NRF24L01_SPI_CSN = 0;				//ʹ��SPI����
	status = SPI_ReadWriteByte(Reg);	//���ͼĴ�����
	for(u8_ctr=0; u8_ctr<Len; u8_ctr++)	//д������
		SPI_ReadWriteByte(*p_Buf++);
	NRF24L01_SPI_CSN = 1;				//ȥ��SPI����
	
	return (status);					//����״ֵ̬
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_TxPacket(uint8_t *TxBuf)
-  Description :	����NRF24L01����һ������
-  Input :			uint8_t *TxBuf: �����������׵�ַ
-  Return :			uint8_t status:	״ֵ̬
-  Others :			
**********************************************************************/
uint8_t NRF24L01_TxPacket(uint8_t *TxBuf)
{
	uint8_t sta;
	
	NRF24L01_CE = 0;
	NRF24L01_Write_Buf(WR_TX_PLOAD, TxBuf, TX_PLOAD_WIDTH);//д���ݵ�TX BUF 32���ֽ�
	NRF24L01_CE = 1;				//��������
	while(NRF24L01_IRQ != 0);		//�ȴ��������
	sta = NRF24L01_Read_Reg(STATUS);//��ȡ״̬�Ĵ�����ֵ
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS, sta);//���TX_DS��MAX_RT�жϱ�־
	
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);//���TX FIFO�Ĵ���
		return MAX_TX;
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xFF;//����ԭ����ʧ��
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_RxPacket(uint8_t *RxBuf)
-  Description :	����NRF24L01����һ����������
-  Input :			uint8_t *RxBuf: ���������׵�ַ
-  Return :			uint8_t status:	״ֵ̬
-  Others :			
**********************************************************************/
uint8_t NRF24L01_RxPacket(uint8_t *RxBuf)
{
	uint8_t sta;
	
	sta = NRF24L01_Read_Reg(STATUS);//��ȡ״̬�Ĵ�����ֵ
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS, sta);//���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD, RxBuf, RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);//���TX FIFO�Ĵ���
		return 0;
	}
	return 1;//û���յ��κ�����
}


/**********************************************************************
-  Function :		void NRF24L01_RX_Mode(void)
-  Description :	��ʼ��NRF24L01��RXģʽ
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0, 
		(uint8_t*)RX_ADDRESS, RX_ADR_WIDTH);//дRX�ڵ��ַ
	  
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA, 0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR, 0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH, 40);	     //����RFͨ��Ƶ��		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP, 0x0f);//����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	
	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
}

/**********************************************************************
-  Function :		void NRF24L01_TX_Mode(void)
-  Description :	��ʼ��NRF24L01��RXģʽ
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;//ʹ��NRF24L01	
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR, 
		(uint8_t*)TX_ADDRESS, TX_ADR_WIDTH);//д��TX�ڵ��ַ 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0, 
		(uint8_t*)RX_ADDRESS, RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA, 0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR, 0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH, 40);       //����RFͨ��Ϊ40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP, 0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
}


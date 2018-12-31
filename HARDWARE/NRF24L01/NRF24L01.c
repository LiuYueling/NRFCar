#include "NRF24L01.h"
#include "spi.h"

extern volatile bit SPI_Busy_Flag;
const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址

/**********************************************************************
-  Function :		void NRF24L01_Init(void)
-  Description :	NRF24L01初始化
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
	//NRF24L01_SPI_MISO	准双向IO	I
	//NRF24L01_SPI_SCLK	PP			O
	P2M0 &= 0xEF;
	P2M0 |= 0x2C;
	P2M1 &= 0xC3;
	P2M1 |= 0x00;
	NRF24L01_SPI_CSN  = 1; //SPI片选取消
	NRF24L01_SPI_MOSI = 1; //强上拉
	NRF24L01_SPI_MISO = 1; //弱上拉
	NRF24L01_SPI_SCLK = 0; //串行同步时钟的空闲状态为低
	
	//NRF24L01_CE 		PP			O
	P5M0 &= 0xFF;
	P5M0 |= 0x20;
	P5M1 &= 0xDF;
	P5M1 |= 0x00;
	NRF24L01_CE = 1; //去能NRF24L01
	
	//NRF24L01_IRQ		准双向IO	I
	P3M0 &= 0xF7;
	P3M0 |= 0x00;
	P3M1 &= 0xF7;
	P3M1 |= 0x00;
	NRF24L01_IRQ = 1; //拉高NRF24L01_IRQ,准备读取NRF24L01_IRQ
	
	
	SPI_Init();//初始化NRF24L01_SPI
	
	SPI_Busy_Flag = 0;
	NRF24L01_CE = 0; //Enable NRF24L01
	NRF24L01_SPI_CSN  = 1; //SPI片选取消
}

/**********************************************************************
-  Function :		void NRF24L01_Init(void)
-  Description :	检测NRF24L01是否存在
-  Input :			void
-  Return :			uint8_t 0:成功;1:失败
-  Others :			通过写发送地址判别SPI是否联通
**********************************************************************/
uint8_t NRF24L01_Check(void)
{
	volatile uint8_t buf[5]={0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
	uint8_t i;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR, buf, 5);//写入5个字节的地址.		
	NRF24L01_Read_Buf(TX_ADDR, buf, 5); //读出写入的地址
	for(i=0;i<5;i++)
		if(buf[i]!=0xA5) break; 							   
	
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Write_Reg(uint8_t reg, uint8_t Data)
-  Description :	写寄存器
-  Input :			uint8_t reg: 寄存器地址
					uint8_t Data: 写入的数据
-  Return :			uint8_t status:	状态值
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Write_Reg(uint8_t Reg, uint8_t Data)
{
	uint8_t status;
	
	NRF24L01_SPI_CSN = 0;				//使能SPI传输
	status = SPI_ReadWriteByte(Reg);	//发送寄存器号
	SPI_ReadWriteByte(Data);			//写入寄存器的值
	NRF24L01_SPI_CSN = 1;				//去能SPI传输
	
	return (status);					//返回状态值
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Read_Reg(uint8_t reg)
-  Description :	读取寄存器
-  Input :			uint8_t reg: 寄存器地址
-  Return :			uint8_t Reg_Data: 寄存器的值
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Read_Reg(uint8_t Reg)
{
	uint8_t Reg_Data;
	
	NRF24L01_SPI_CSN = 0;				//使能SPI传输
	SPI_ReadWriteByte(Reg);				//发送寄存器号
	Reg_Data = SPI_ReadWriteByte(0xFF);	//读取寄存器的值
	NRF24L01_SPI_CSN = 1;				//去能SPI传输
	
	return (Reg_Data);					//返回状态值
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Read_Buf(uint8_t, uint8_t*, uint8_t)
-  Description :	在指定位置读出指定长度的数据
-  Input :			uint8_t reg: 寄存器地址
					uint8_t *pBuf: 数据指针
					uint8_t len: 数据长度
-  Return :			uint8_t Reg_Data: 寄存器的值
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Read_Buf(uint8_t Reg, uint8_t *p_Buf, uint8_t Len)
{
	uint8_t status, u8_ctr;
	
	NRF24L01_SPI_CSN = 0;				//使能SPI传输
	status = SPI_ReadWriteByte(Reg);	//发送寄存器号
	for(u8_ctr=0; u8_ctr<Len; u8_ctr++) //读出数据
		p_Buf[u8_ctr] = SPI_ReadWriteByte(0xFF);
	NRF24L01_SPI_CSN = 1;				//去能SPI传输
	
	return (status);					//返回状态值
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_Write_Buf(uint8_t, uint8_t*, uint8_t)
-  Description :	在指定位置写入指定长度的数据
-  Input :			uint8_t reg: 寄存器地址
					uint8_t *pBuf: 数据指针
					uint8_t len: 数据长度
-  Return :			uint8_t status:	状态值
-  Others :			
**********************************************************************/
uint8_t NRF24L01_Write_Buf(uint8_t Reg, uint8_t *p_Buf, uint8_t Len)
{
	uint8_t status,u8_ctr;
	
//	EA = 0;
	NRF24L01_SPI_CSN = 0;				//使能SPI传输
	status = SPI_ReadWriteByte(Reg);	//发送寄存器号
	for(u8_ctr=0; u8_ctr<Len; u8_ctr++)	//写入数据
		SPI_ReadWriteByte(*p_Buf++);
	NRF24L01_SPI_CSN = 1;				//去能SPI传输
//	EA = 1;
	
	return (status);					//返回状态值
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_TxPacket(uint8_t *TxBuf)
-  Description :	启动NRF24L01发送一次数据
-  Input :			uint8_t *TxBuf: 待发送数据首地址
-  Return :			uint8_t status:	状态值
-  Others :			
**********************************************************************/
uint8_t NRF24L01_TxPacket(uint8_t *TxBuf)
{
	uint8_t sta;
	
	NRF24L01_CE = 0;
	NRF24L01_Write_Buf(WR_TX_PLOAD, TxBuf, TX_PLOAD_WIDTH);//写数据到TX BUF 32个字节
	NRF24L01_CE = 1;				//启动发送
	while(NRF24L01_IRQ == 0);		//等待发送完毕
	sta = NRF24L01_Read_Reg(STATUS);//读取状态寄存器的值
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS, sta);//清除TX_DS或MAX_RT中断标志
	
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);//清除TX FIFO寄存器
		return MAX_TX;
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xFF;//其他原因发送失败
}

/**********************************************************************
-  Function :		uint8_t NRF24L01_RxPacket(uint8_t *RxBuf)
-  Description :	启动NRF24L01接收一个包的数据
-  Input :			uint8_t *RxBuf: 接收数据首地址
-  Return :			uint8_t status:	状态值
-  Others :			
**********************************************************************/
uint8_t NRF24L01_RxPacket(uint8_t *RxBuf)
{
	uint8_t sta;
	
	sta = NRF24L01_Read_Reg(STATUS);//读取状态寄存器的值
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS, sta);//清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD, RxBuf, RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);//清除TX FIFO寄存器
		return 0;
	}
	return 1;//没有收到任何数据
}


/**********************************************************************
-  Function :		void NRF24L01_RX_Mode(void)
-  Description :	初始化NRF24L01到RX模式
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0, 
		(uint8_t*)RX_ADDRESS, RX_ADR_WIDTH);//写RX节点地址
	  
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA, 0x01);    //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR, 0x01);//使能通道0的接收地址  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH, 40);	     //设置RF通信频率		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP, 0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	
	NRF24L01_CE = 1; //CE为高,进入接收模式 
}

/**********************************************************************
-  Function :		void NRF24L01_TX_Mode(void)
-  Description :	初始化NRF24L01到RX模式
-  Input :			void
-  Return :			void
-  Others :			
**********************************************************************/
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;//使能NRF24L01	
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR, 
		(uint8_t*)TX_ADDRESS, TX_ADR_WIDTH);//写入TX节点地址 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0, 
		(uint8_t*)RX_ADDRESS, RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA, 0x01);     //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR, 0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR, 0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH, 40);       //设置RF通道为40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP, 0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE=1;//CE为高,10us后启动发送
}


/**********************************************************************
-  File name : adc.c
-  Author : yueling_liu	Version: 0.1	Date: 2018��10��01������һ
-  Description :	Ӳ��ADC
-  History :
   NO.<author>		<time>		<version>	<desc>
   1.yueling_liu	18/10/01	0.1			project initial
**********************************************************************/

#include "adc.h"

//--Type Definition--//
#define ADC_POWER_ON	0x80				//ADC��Դ����λ
#define ADC_FLAG		0x10            	//ADC��ɱ�־
#define ADC_START		0x08            	//ADC��ʼ����λ
#define ADC_SPEEDLL		0x00            	//540��ʱ��
#define ADC_SPEEDL		0x20            	//360��ʱ��
#define ADC_SPEEDH		0x40            	//180��ʱ��
#define ADC_SPEEDHH		0x60            	//90��ʱ��



volatile bit ADC_OK_Flag = 1;//ADת����ɱ�־
volatile uint8_t ADCXY_CH = 0;//ADת��ͨ��

#if (ROCKER_SUM == 1)
volatile uint16_t ADC_BUFF[2] = {0, 0};//ADC���ݻ�����
#elif (ROCKER_SUM == 2)
volatile uint16_t ADC_BUFF[4] = {0, 0, 0, 0};
#endif

/**********************************************************************
-  Function :		void Adc_Init(void)
-  Description :	SPI Init
-  Input :			void
-  Return :			void
-  Others :			IO����ADC:
					Rocker1_CHX	->	ADC0(P1^0)
					Rocker1_CHY	->	ADC1(P1^1)
					Rocker2_CHX	->	ADC6(P1^6)
					Rocker2_CHY	->	ADC7(P1^7)
**********************************************************************/
void Adc_Init(void)
{
	P0M0 = 0x00;
	P0M1 = 0xC3;
	
	/*IO����:����P1��ΪAD��*/                   
    P1ASF = 0xC3;
	
	/*�������Ĵ���*/
	ADC_RES  = 0x00;                 
    ADC_RESL = 0x00;
	
	/*����ADC��Դ; 540��ʱ��; CH = ADC_0;*/
	ADC_CONTR = ADC_POWER_ON | ADC_SPEEDLL | ADC_START | 0x00;
	
	EADC = 1;//����A/Dת���ж�
}

/**********************************************************************
-  Function :		void Adc_Interruption(void) interrupt 5
-  Description :	ADC�жϷ�����
-  Input :			void
-  Return :			void
-  Others :			���AD�жϱ�־
**********************************************************************/
void Adc_Interruption(void) interrupt 5
{	
	ADC_CONTR &= !ADC_FLAG;         //���ADC�жϱ�־
	
	switch(ADCXY_CH)
	{
#if (ROCKER_SUM == 1)
		case 0: ADC_BUFF[0] = ADC_RES*4 + ADC_RESL; ADCXY_CH = 1; break;
		case 1: ADC_BUFF[1] = ADC_RES*4 + ADC_RESL; ADCXY_CH = 0; break;
		default: ADC_OK_Flag = 0; ADCXY_CH = 0; break;
#elif (ROCKER_SUM == 2)
		case 0: ADC_BUFF[0] = ADC_RES*4 + ADC_RESL; ADCXY_CH = 1; break;
		case 1: ADC_BUFF[1] = ADC_RES*4 + ADC_RESL; ADCXY_CH = 6; break;
		case 6: ADC_BUFF[2] = ADC_RES*4 + ADC_RESL; ADCXY_CH = 7; break;
		case 7: ADC_BUFF[3] = ADC_RES*4 + ADC_RESL; ADCXY_CH = 8; break;//CH=8���
		default: ADC_OK_Flag = 0; ADCXY_CH = 0; break;
#endif
	}
	ADC_CONTR = ADC_POWER_ON | ADC_SPEEDLL | ADC_START | ADCXY_CH;//�л�ͨ��	
}


//uint16_t Get_CH_ADC(uint8_t ch)
//{
//	uint16_t ADC_Buff;
//	
//	ADC_CONTR = ADC_POWER_ON | ADC_SPEEDLL | ADC_START | ch;//�л�ͨ��
//	_nop_();                        //�ȴ�4��NOP
//	_nop_();
//	_nop_();
//	_nop_();
//	while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
//    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
//	
////	ADC_OK_Flag = 1;//���AD��ɱ�־
////	while(ADC_OK_Flag == 0);//�ȴ�ADת�����
////	ADC_Buff = ADC_RES*4 + ADC_RESL;
//	ADC_Buff = ADC_RES;
//	
//	return ADC_Buff;	
//}

//uint16_t Get_ADC_Average(uint8_t ch, uint8_t count)
//{
//	uint32_t sum = 0;
//	uint8_t i;
//	
//	for(i=0; i<count; count++)
//	{
//		sum += Get_CH_ADC(ch);
//		Delay5ms();
//	}
//	
//	return (uint16_t)(sum/count);	
//}



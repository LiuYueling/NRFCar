#ifndef __ADC_H
#define __ADC_H

//--File Include--//
#include "SYS.H"



//--Type Definition--//


//--Function Prototype--//
void Adc_Init(void);//ADת����ʼ��
uint16_t Get_CH_ADC(uint8_t ch);//��ȡCHͨ��ADCֵ
uint16_t Get_ADC_Average(uint8_t ch, uint8_t count);//��ȡCHͨ����ADCƽ��ֵ

#endif

#ifndef __ADC_H
#define __ADC_H

//--File Include--//
#include "SYS.H"



//--Type Definition--//


//--Function Prototype--//
void Adc_Init(void);//AD转换初始化
uint16_t Get_CH_ADC(uint8_t ch);//获取CH通道ADC值
uint16_t Get_ADC_Average(uint8_t ch, uint8_t count);//获取CH通道的ADC平均值

#endif

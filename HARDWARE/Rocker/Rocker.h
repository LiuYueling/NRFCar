#ifndef _ROCKER_H
#define _ROCKER_H

#include "SYS.H"

typedef struct{//ҡ��BUFF�ṹ��
	uint16_t X;				//ˮƽ����AD��
	uint16_t Y;				//��ֱ����AD��
	uint8_t  Rocker_Key;	//Rocker key
}RockerTypeDef;

void Get_Rocker(void);//�õ�ҡ������
void ADC_UART_TEST(void);//ADC UART TEST Send

#endif

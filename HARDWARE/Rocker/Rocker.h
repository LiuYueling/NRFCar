#ifndef _ROCKER_H
#define _ROCKER_H

#include "SYS.H"

typedef struct{//摇杆BUFF结构体
	uint16_t X;				//水平方向AD量
	uint16_t Y;				//垂直方向AD量
	uint8_t  Rocker_Key;	//Rocker key
}RockerTypeDef;

void Get_Rocker(void);//得到摇杆数据
void ADC_UART_TEST(void);//ADC UART TEST Send

#endif

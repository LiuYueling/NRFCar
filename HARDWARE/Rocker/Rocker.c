#include "Rocker.h"
#include "adc.h"
#include "uart.h"
#include "stdio.h"

#define Average_Cont 3
#define RockerL_X_CH 0
#define RockerL_Y_CH 1
#define RockerR_X_CH 6
#define RockerR_Y_CH 7

struct _Rocker
{
	uint16_t X;
 	uint16_t Y;
}Rocker_L,Rocker_R;

extern volatile uint16_t ADC_BUF[4];

sbit Rocker1_Key = P2^2;
//sbit Rocker2_Key = P2^3;

void ADC_UART_TEST(void)
{
#if (TEST_MODE == 1)
	xdata uint8_t str[21];
	
	sprintf(str, "Rocker_L_X = %u\t", Rocker_L.X);
	UART_SendString(str);
	sprintf(str, "Rocker_L_Y = %u\r\n", Rocker_L.Y);
	UART_SendString(str);
//	sprintf(str, "Rocker_R_X = %u\t", Rocker_R.X);
//	UART_SendString(str);
//	sprintf(str, "Rocker_R_Y = %u\r\n", Rocker_R.Y);
//	UART_SendString(str);
#endif
}


void Get_Rocker(void)
{	
	Rocker_L.X = ADC_BUF[0];
	Rocker_L.Y = ADC_BUF[1];
//	Rocker_R.X = ADC_BUF[2];
//	Rocker_R.Y = ADC_BUF[3];
#if (TEST_MODE == 1)	
	ADC_UART_TEST();
#endif
}



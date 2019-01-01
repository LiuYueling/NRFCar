#include "Rocker.h"
#include "adc.h"
#include "uart.h"

#define Average_Cont 3
#define RockerL_X_CH 0
#define RockerL_Y_CH 1
#define RockerR_X_CH 6
#define RockerR_Y_CH 7

extern volatile uint16_t *ADC_BUF;//AD Buff address

#if (ROCKER_SUM == 1)
RockerTypeDef ONE;
RockerTypeDef *RackerStruct_P = &ONE;
#endif

//#if (ROCKER_SUM == 2)
//RockerTypeDef R;
//RockerTypeDef L;
//#endif

//sbit Rocker1_Key = P2^2;
//sbit Rocker2_Key = P2^3;

void ADC_UART_TEST(void)
{
#if (TEST_MODE == 1)
#if (ROCKER_SUM == 1)
	xdata uint8_t str[17];
	
	sprintf(str, "Rocke_X = %u\t", ONE.X);
	UART_SendString(str);
	sprintf(str, "Rocker_Y = %u\r\n", ONE.Y);
	UART_SendString(str);
#endif
	
//#if (ROCKER_SUM == 2)
//	xdata uint8_t str[19];
//	
//	sprintf(str, "Rocker_L_X = %u\t", L.X);
//	UART_SendString(str);
//	sprintf(str, "Rocker_L_Y = %u\r\n", L.Y);
//	UART_SendString(str);
//	sprintf(str, "Rocker_R_X = %u\t", R.X);
//	UART_SendString(str);
//	sprintf(str, "Rocker_R_Y = %u\r\n", R.Y);
//	UART_SendString(str);
//#endif
	
#endif
}


void Get_Rocker(void)
{
#if (ROCKER_SUM == 1)//µ¥¸öÒ£¸Ð
	ONE.X = ADC_BUF[0];
	ONE.Y = ADC_BUF[1];
#endif
	
//#if (ROCKER_SUM == 2)
//	L.X = ADC_BUF[0];
//	L.Y = ADC_BUF[1];
//	R.X = ADC_BUF[2];
//	R.Y = ADC_BUF[3];
//#endif	
}





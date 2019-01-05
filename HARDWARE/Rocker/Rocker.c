#include "Rocker.h"

//extern RockerTypeDef *RackerStruct_P;

//#if (ROCKER_SUM == 1)
//extern volatile uint16_t ADC_BUFF[2];//ADC数据缓存区
//#elif (ROCKER_SUM == 2)
//extern volatile uint16_t ADC_BUFF[4];
//#endif

//void ADC_UART_TEST(void)
//{
//#if (TEST_MODE == 1)
//#if (ROCKER_SUM == 1)
////	xdata uint8_t str[17];
//	
////	sprintf(str, "Rocke_X = %x\t", ONE.X);
////	UART_SendString(str);
////	sprintf(str, "Rocker_Y = %x\r\n", ONE.Y);
////	UART_SendString(str);
//#endif
//	
////#if (ROCKER_SUM == 2)
////	xdata uint8_t str[19];
////	
////	sprintf(str, "Rocker_L_X = %u\t", L.X);
////	UART_SendString(str);
////	sprintf(str, "Rocker_L_Y = %u\r\n", L.Y);
////	UART_SendString(str);
////	sprintf(str, "Rocker_R_X = %u\t", R.X);
////	UART_SendString(str);
////	sprintf(str, "Rocker_R_Y = %u\r\n", R.Y);
////	UART_SendString(str);
////#endif
//	
//#endif
//}

void Rocker_init(void)
{
	/*Rocker1_Key IO Init*/
	#if (ROCKER_SUM == 1)
	{
		
		Rocker1_Key = 1;
	}
	#endif
//	#if (ROCKER_SUM == 2)
//	{
//		Rocker1_Key = 1;
//		Rocker2_Key = 1;
//	}
//	#endif
	
	/*Rocker ADC Init*/
	Adc_Init();
	UART_SendString("ADC Init\r\n");
	
}

void Get_Rocker(void)
{
#if (ROCKER_SUM == 1)//单个遥感
//	xdata uint8_t str[17];
	
//	RackerStruct_P->X = ADC_BUFF[0];
//	RackerStruct_P->Y = ADC_BUFF[1];
//	RackerStruct_P->Rocker_Key = Rocker1_Key;
	
//	sprintf(str, "Rocke_X = %x\t", ADC_BUFF[0]);
//	UART_SendString(str);
//	sprintf(str, "Rocker_Y = %x\r\n", ADC_BUFF[1]);
//	UART_SendString(str);
#endif
	
//#if (ROCKER_SUM == 2)
//	L.X = ADC_BUF[0];
//	L.Y = ADC_BUF[1];
//	R.X = ADC_BUF[2];
//	R.Y = ADC_BUF[3];
//#endif	
}





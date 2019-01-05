#ifndef _MAIN_H
#define _MAIN_H


//--Global Header File--//
#ifdef NRF_CAR_MASTER 
#include "SYS.H"
#include "delay.h"
#include "uart.h"
#include "timer.h"
#include "NRF24L01.h"
#include "spi.h"
#include "adc.h"
#include "Rocker.h"
#include "NRF_DT.h"
#endif

#ifdef NRF_CAR_SLAVE
#include "SYS.H"
#include "delay.h"
#include "uart.h"
#include "timer.h"
#include "NRF24L01.h"
#include "spi.h"
#include "NRF_DT.h"
#endif


//--Global Type Definition--//


//--Global Extern Variable--//

//--Global Definition--//

//--Global Interface--//
sbit LED_RUN = P5^4;
//--Global Function Prototype--//



#endif

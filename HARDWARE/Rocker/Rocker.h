#ifndef _ROCKER_H
#define _ROCKER_H

#include "MAIN.h"

#if (ROCKER_SUM == 1)
sbit Rocker1_Key = P2^2;
#endif
//#if (ROCKER_SUM == 2)
//sbit Rocker1_Key = P2^2;
//sbit Rocker2_Key = P2^3;
//#endif

void Rocker_init(void);//ҡ�������ʼ��
void Get_Rocker(void);//�õ�ҡ������

#endif

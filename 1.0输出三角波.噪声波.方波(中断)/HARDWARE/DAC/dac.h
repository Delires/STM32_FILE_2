#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	    
								    
					    
void GPIOA_4(void); //DAC1 PA4���ų�ʼ��	 	 
void Dac1_Set_Vol(u16 vol);

void Dac1_Init(void);       //DA��ͨ����
void Dac1_ZaoShengBo(void); //����������
void Dac1_SanJiaoBo(void);  //�������ǲ�



#endif


















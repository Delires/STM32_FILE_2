#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	    
								    
					    
void GPIOA_4(void); //DAC1 PA4引脚初始化	 	 
void Dac1_Set_Vol(u16 vol);

void Dac1_Init(void);       //DA普通配置
void Dac1_ZaoShengBo(void); //生成噪声波
void Dac1_SanJiaoBo(void);  //生成三角波



#endif


















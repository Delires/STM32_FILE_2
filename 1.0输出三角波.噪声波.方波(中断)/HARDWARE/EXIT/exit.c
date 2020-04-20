#include "exit.h"
#include "delay.h"
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "dac.h"

void exit_config(void)
{
	
	EXTI_InitTypeDef EXTI_InitStruct;    //结构体定义其实可以写一个 因为每次赋值后都成了新的了
	EXTI_InitTypeDef EXTI_InitStruct_WK_UP;
	NVIC_InitTypeDef NVIC_InitStruct;

	
//使能AFIO	
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, ENABLE); //找了一天错误在这 他妈的
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	KEY_Init();
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);  //key1中断线映射  下降沿
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);   //key0中断线映射   下降沿
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);   //wk_up中断线映射  读上升沿

//配置key1 key0中断 下降沿触发	
	EXTI_InitStruct.EXTI_Line= EXTI_Line5;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line= EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	
//配置wk_up中断 上升沿触发		
	EXTI_InitStruct_WK_UP.EXTI_Line= EXTI_Line0;
	EXTI_InitStruct_WK_UP.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct_WK_UP.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct_WK_UP.EXTI_Trigger = EXTI_Trigger_Rising;   //上升沿触发
	EXTI_Init(&EXTI_InitStruct_WK_UP);
	 
//设置中断优先级  wk_up优先级最低 
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00; //因为设置的中断分组导致
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x03;    //越小优先级越高
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00; //因为设置的中断分组导致
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x02;    //越小优先级越高
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00; 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;   
	NVIC_Init(&NVIC_InitStruct);	
}

//WK_UP中断函数
void EXTI0_IRQHandler(void)  
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
	  delay_ms(10);
    if(WK_UP==1)
	  {
		 LED1=1;
		 LED0=1;
		 Dac1_Init();  //DAC初始化
		 while(1)
				{ 
					Dac1_Set_Vol(3000);  //电压对应数字值函数
				  delay_ms(200);
					Dac1_Set_Vol(0); 
          delay_ms(200);	
				}  
    }
		EXTI_ClearITPendingBit(EXTI_Line0); //
	}
}

//记得要清楚中断
//KEY0中断函数
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
	  delay_ms(10);
	  if(KEY0==0)
	  {
	   Dac1_SanJiaoBo();   
		 LED1=1;
	  }	
		EXTI_ClearITPendingBit(EXTI_Line5); //
	}
	
}

//KEY1中断函数
void EXTI15_10_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line15)!=RESET)
	{
	  delay_ms(10);
	  if(KEY1==0)
	  {
	  	Dac1_ZaoShengBo();  
	   LED1=0;
  	}	
		EXTI_ClearITPendingBit(EXTI_Line15); //
	}
		     
}



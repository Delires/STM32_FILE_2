#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "dac.h"
#include "exit.h"


	int main(void)
	{
		delay_init();	    	//延时函数初始化	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	  GPIOA_4();
		KEY_Init();
		LED_Init();
		exit_config();
		
	  while(1)
		{
			Dac1_SanJiaoBo();
			LED0=0;
			delay_ms(200);
			LED0=1;
			delay_ms(200);
		}
	} 



//int main(void)
//{
//	u8 key=0; //读按键值
//	delay_init();	    	//延时函数初始化	  
//  GPIOA_4();
//	KEY_Init();
//	LED_Init();
//	
//  while(1)
//	{
//		LED0=0;
//		delay_ms(200);
//		LED0=1;
//		delay_ms(200);
//		
//		key=KEY_Scan(0);
//		if(key)
//		{
// 		   switch(key)
//		   {
//		     case KEY0_PRES:  //DA输出三角波
//					     Dac1_SanJiaoBo();   
//				       LED1=1;
//				       LED0=0;
//				       break;
//				
//				 case KEY1_PRES:  //DA输出杂波
//					     Dac1_ZaoShengBo();  
//				       LED1=0;
//				       break;
//				 case WKUP_PRES:  //DA输出循环的高低电平
//					    LED1=1;
//					    Dac1_Init();  //DAC初始化
//				      while(1)
//					  	{ Dac1_Set_Vol(3000);  //电压对应数字值函数
//					  	  delay_ms(200);
//						  	Dac1_Set_Vol(0); 
//                delay_ms(200);	
//			//跳出while(1)循环用
//							key=KEY_Scan(0);
//							if(key==KEY0_PRES || key==KEY1_PRES) return 0;  //break;  //按下其他按键跳出循环
//							}     break;						
//		   }
//		}

//	}
//} 








#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "dac.h"
#include "exit.h"


	int main(void)
	{
		delay_init();	    	//��ʱ������ʼ��	
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
//	u8 key=0; //������ֵ
//	delay_init();	    	//��ʱ������ʼ��	  
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
//		     case KEY0_PRES:  //DA������ǲ�
//					     Dac1_SanJiaoBo();   
//				       LED1=1;
//				       LED0=0;
//				       break;
//				
//				 case KEY1_PRES:  //DA����Ӳ�
//					     Dac1_ZaoShengBo();  
//				       LED1=0;
//				       break;
//				 case WKUP_PRES:  //DA���ѭ���ĸߵ͵�ƽ
//					    LED1=1;
//					    Dac1_Init();  //DAC��ʼ��
//				      while(1)
//					  	{ Dac1_Set_Vol(3000);  //��ѹ��Ӧ����ֵ����
//					  	  delay_ms(200);
//						  	Dac1_Set_Vol(0); 
//                delay_ms(200);	
//			//����while(1)ѭ����
//							key=KEY_Scan(0);
//							if(key==KEY0_PRES || key==KEY1_PRES) return 0;  //break;  //����������������ѭ��
//							}     break;						
//		   }
//		}

//	}
//} 








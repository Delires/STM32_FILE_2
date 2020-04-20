#include "dac.h"

void GPIOA_4(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能PORTA通道时钟
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //模拟输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 输出高
}


void Dac1_Init(void) //DAC初始化无普通输出
{
 	DAC_InitTypeDef DAC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

				
	DAC_InitStruct.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
	DAC_InitStruct.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitStruct.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitStruct);	 //初始化DAC通道1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值

}


void Dac1_SanJiaoBo(void) //DAC配置 三角波
{
	DAC_InitTypeDef DAC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095; //幅值最大
	DAC_InitStruct.DAC_OutputBuffer =DAC_OutputBuffer_Disable;  //输出使能，输出能力强些，但不到0
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_Software;         //软件触发
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_Triangle; //三角波
  DAC_Init(DAC_Channel_1 , &DAC_InitStruct);
		
	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
	DAC_DMACmd(DAC_Channel_1, DISABLE);//关闭DMA
  DAC_SetChannel1Data(DAC_Align_12b_R, 4096); //DAC_DHR8R1 寄存器写满12位
	
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);  //DAC_SWTRIGR DAC软件触发
	
}


void Dac1_ZaoShengBo(void) //DAC配置 三角波
{
	DAC_InitTypeDef DAC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095; //幅值最大
	DAC_InitStruct.DAC_OutputBuffer =DAC_OutputBuffer_Disable;  //输出使能，输出能力强些，但不到0
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_Software;         //软件触发
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_Noise; //三角波
  DAC_Init(DAC_Channel_1 , &DAC_InitStruct);
		
	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
	DAC_DMACmd(DAC_Channel_1, DISABLE);//关闭DMA
  DAC_SetChannel1Data(DAC_Align_12b_R, 4096); //DAC_DHR8R1 寄存器写满12位
	
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);  //DAC_SWTRIGR DAC软件触发
	
}








//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol)
{
 	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}






















































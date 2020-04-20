#include "dac.h"

void GPIOA_4(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
}


void Dac1_Init(void) //DAC��ʼ������ͨ���
{
 	DAC_InitTypeDef DAC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

				
	DAC_InitStruct.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitStruct.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitStruct.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitStruct);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}


void Dac1_SanJiaoBo(void) //DAC���� ���ǲ�
{
	DAC_InitTypeDef DAC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095; //��ֵ���
	DAC_InitStruct.DAC_OutputBuffer =DAC_OutputBuffer_Disable;  //���ʹ�ܣ��������ǿЩ��������0
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_Software;         //�������
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_Triangle; //���ǲ�
  DAC_Init(DAC_Channel_1 , &DAC_InitStruct);
		
	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
	DAC_DMACmd(DAC_Channel_1, DISABLE);//�ر�DMA
  DAC_SetChannel1Data(DAC_Align_12b_R, 4096); //DAC_DHR8R1 �Ĵ���д��12λ
	
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);  //DAC_SWTRIGR DAC�������
	
}


void Dac1_ZaoShengBo(void) //DAC���� ���ǲ�
{
	DAC_InitTypeDef DAC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095; //��ֵ���
	DAC_InitStruct.DAC_OutputBuffer =DAC_OutputBuffer_Disable;  //���ʹ�ܣ��������ǿЩ��������0
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_Software;         //�������
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_Noise; //���ǲ�
  DAC_Init(DAC_Channel_1 , &DAC_InitStruct);
		
	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
	DAC_DMACmd(DAC_Channel_1, DISABLE);//�ر�DMA
  DAC_SetChannel1Data(DAC_Align_12b_R, 4096); //DAC_DHR8R1 �Ĵ���д��12λ
	
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);  //DAC_SWTRIGR DAC�������
	
}








//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol)
{
 	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}






















































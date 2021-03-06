#include "pbdata.h"

AD AD_INDATA_T;

vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];

void ADC_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	DMA_DeInit(DMA1_Channel1);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = Sample_Num*Channel_Num;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);

}

void ADC_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	ADC_InitTypeDef ADC_InitStructure;
	
	//AD                            V_AD
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_DMA_Config();
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = Channel_Num;
	
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,1,ADC_SampleTime_55Cycles5);

	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
}

void POWER_AD_Init(void)
{
	ADC_DMA_Config();            //ADC_DMA Init
	ADC_GPIO_Configuration();    //ADC_DMA Init and Set
}

float ReadADCAverageValue(uint16_t Channel)
{
	uint8_t i;
	uint32_t sum =0;
	
	for(i=0;i<Sample_Num;i++)
	{
		sum += ADC_ConvertedValue[i][Channel];
	}
	
	return ((sum/Sample_Num)*3300/4096);   /*??????????,mv*/
}










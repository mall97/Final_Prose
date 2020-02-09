#include "stm32f10x.h"
#include "adc.h"
extern uint16_t ADC1_Addr[8];

void read_adc(void)
{
	//read_values_from_ADC_pins
	ADC_SoftwareStartConvCmd ( ADC1 , ENABLE );
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
	DMA_ClearFlag(DMA1_FLAG_TC1);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}

#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "lcd.h"
#include "time.h"
#include <math.h>

#include "hsi.h"
#include "init.h"
#include "adc.h"
#include "send.h"

char buff[30];
extern int angulo;
extern int Lux[8];
uint16_t ADC1_Addr[8];

void display(void)
{

		//float volt=3.3-(3.3*ADC1_Addr[i])/4096;
		sprintf(buff,"%d\r\n",angulo);
		for(int a=0; buff[a]!='\0';a++)
		{
			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
			USART_SendData(USART2, buff[a]);
			USART_ClearFlag(USART2,USART_FLAG_TXE);
		}
	//for(int a=0;a<2000000;a++);
}

int main(void)
{
	RCC_Config_HSI_PLL_64MHz();
	init();
	init_adc();
	init_can();
	while(1)
		{
		read_adc();
		calc();
		display();
		prose();
		}
}





#include "hsi.h"
#include "stm32f10x.h"
#include "stm32f10x_can.h"

void RCC_Config_HSI_PLL_64MHz() //HSI com PLL a frequencia maxima
{
	//Reset às configuracões
	RCC_DeInit(); //Faz reset ao sistema e coloca a configuraccao por omissão

	//Ativar Fonte
	RCC_HSICmd(ENABLE); //Ativar a HSI

	//Esperar arranque do clock
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);

	//Configurar Wait States
	FLASH_SetLatency(FLASH_Latency_2);

	//Configurar os prescalers AHB, APB1 e APB2, respetivamente
	RCC_HCLKConfig(RCC_SYSCLK_Div1);//divisor unitario que é o divisor mais baixo possivel
	RCC_PCLK1Config(RCC_HCLK_Div2); //PCLK1 no valor maximo possivel, ou seja, colocar o divisor minimo possivel
	RCC_PCLK2Config(RCC_HCLK_Div1); //PCLK2 no valor maximo possivel, ou seja, colocar o divisor minimo possivel

	//Configuracao da PLL
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16); //Obrigatorio dividir por 2 e multipicar pelo maior valor (x16)

	//Ativar PLL
	RCC_PLLCmd(ENABLE); //Ativar a PLL

	//Esperar pela ativacao da PLL
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);

	//Configurar SYSCLK
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //Selecionar a fonte PLL

	//Aguardar que a fonte estabilize
	while(RCC_GetSYSCLKSource() != 0x08); //Esperar que a fonte PLL(0x08) estabilize

}

/*
 * hwinit.c
 *
 *  Created on: Mar 24, 2011
 *      Author: baron
 */


#include "board.h"

ErrorStatus HSEStartUpStatus;

/*******************************************************************************
 * Function Name  : RCC_Configuration
 * Description    : Configures the different system clocks.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void RCC_Configuration(void)
{
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);

		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);

		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

		/* Enable PLL */
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while (RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
}
/*******************************************************************************
 * Function Name  : NVIC_Configuration
 * Description    : Configures Vector Table base location.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
#ifdef VECT_TAB_RAM
/* vector-offset (TBLOFF) from bottom of SRAM. defined in linker script */
extern uint32_t _isr_vectorsram_offs;
void NVIC_Configuration(void)
{
	/* Set the Vector Table base location at 0x20000000+_isr_vectorsram_offs */
	NVIC_SetVectorTable(NVIC_VectTab_RAM, (uint32_t) &_isr_vectorsram_offs);
}
#else
extern uint32_t _isr_vectorsflash_offs;
void NVIC_Configuration(void)
{
	/* Set the Vector Table base location at 0x08000000+_isr_vectorsflash_offs */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, (uint32_t)&_isr_vectorsflash_offs);
}
#endif /* VECT_TAB_RAM */

#ifdef USE_FULL_ASSERT

#include "term_io.h"

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to thvoid hwInit()
{

}
 * e source file name
 * @param line: assert_param error line source number
 * @retval : None
 */
void assert_failed(const uint8_t* file, const uint8_t* function, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	xprintf("\n !!! Wrong parameter value detected\n");
	xprintf(" - file %s\n", file);
	xprintf(" - function %s\n", function);
	xprintf(" - line %lu\n", line);

#if 0
	/* Infinite loop */
	while (1)
	{
	}
#endif
}
#endif


void hwInit()
{
	/* System Clocks Configuration */
	RCC_Configuration();

	/* NVIC configuration */
	NVIC_Configuration();


}


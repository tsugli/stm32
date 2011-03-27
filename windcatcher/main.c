/*******************************************************************************
 * Project            : STM32 MINI Digital Picture Frame
 * File Name          : main.c
 * Author             : Martin Thomas, main-skeleton based on code from the
 *                      STMicroelectronics MCD Application Team
 * Version            : see VERSION_STRING below
 * Date               : see VERSION_STRING below
 * Description        : Main program body for the SD-Card tests
 ********************************************************************************
 * License: BSD
 *******************************************************************************/
#define VERSION_STRING "V1.0.0 24.03.2011"
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "board.h"
#include "hwinit.h"
#include "FreeRTOS.h"
#include "task.h"
#include "logica.h"
#include "rs485.h"

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);

/* Public functions -- -------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#define vLogicaTask_PRIORITY            ( tskIDLE_PRIORITY + 2 )
#define vRs485Task_PRIORITY            ( tskIDLE_PRIORITY + 1 )

int main(void)
{
	hwInit();
	/* Configure the GPIO ports */
	GPIO_Configuration();

	/* Turn on/off LED(s) */

	xTaskCreate(vLogicaTask, (const signed portCHAR * const ) "Logica",
			vLogicaTask_STACK_SIZE, NULL, vLogicaTask_PRIORITY,
			(xTaskHandle *) NULL);
	/* Start the scheduler. */

	xTaskCreate(vRs485Task, (const signed portCHAR * const ) "RS485",
			vRs485Task_STACK_SIZE, NULL, vRs485Task_PRIORITY,
			(xTaskHandle *) NULL);

	/* Start the scheduler. */

	vTaskStartScheduler();
	while (1)
	{
	};

	return 0;
}

void vApplicationIdleHook(void)
{

}
void vApplicationTickHook(void)
{

}
void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed portCHAR *pcTaskName)
{

	while (1)
		;
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Enable GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Enable GPIOB clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* Configure PC.4 as Output push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure  as Output push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}


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

//	xTaskCreate(vRs485Task, (const signed portCHAR * const ) "RS485",
//			vRs485Task_STACK_SIZE, NULL, vRs485Task_PRIORITY,
//			(xTaskHandle *) NULL);

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
int t1time, t1count;
int t2time, t2count;
int t1oldval, t2oldval;
extern int T1, T2;

void vApplicationTickHook(void)
{
/*
	int t1val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
	int t2val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
	//---------------------------------------------------------
	if (t1val != t1oldval) // Wind Speed tester
	{
			t1count++;
	}
	//---------------------------------------------------------
	if (t2val != t2oldval)
	{
		t2count++;
	}
	//---------------------------------------------------------
	if (t1count >= 20)
	{

		T1 = 4000000 / t1time; // 100 hz - 40000 mm/sec wind speed
		t1count = 0;
		t1time = 0;
	}
	if (t2count >= 2)
	{
		T2 = 60000000 / t2time; // generator rotations per 10 min
		t2count = 0;
		t2time = 0;
	}



	//---------------------------------------------------------
	if(t2time>60000)
	  {
		 T2 = 0;
	   }
	if(t1time>60000)
		  {
			 T1 = 0;
		  }


	t2time++;
	t1time++;
	t1oldval = t1val;
	t2oldval = t2val;
*/
	//---------------------------------------------------------
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
	/* Enable GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Enable GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	/* Configure PC.4 as Output push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure PC.4 as Output push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);



	/* GPIOC Configuration:TIM8 Channel3-4 in Input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}



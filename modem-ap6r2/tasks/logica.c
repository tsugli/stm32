// SPI_BUS
#include <stdlib.h>
/* Scheduler include files. */
#include "logica.h"
#include "FreeRTOS.h"
#include "task.h"


void vLogicaTask(void *pvParameters)
{
	while (1)
	{


		//GPIO_SetBits(GPIOC, GPIO_Pin_5);
		GPIO_SetBits(GPIOB, GPIO_Pin_2);

		/* Insert delay */
		vTaskDelay(100);
		/* Turn off led connected to PC.5 pin */
		//GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_2);

		/* Insert delay */
		vTaskDelay(100);
	}
}

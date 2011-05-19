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


		GPIO_SetBits(GPIOC, GPIO_Pin_5);



		/* Insert delay */
		vTaskDelay(50);
		/* Turn off led connected to PC.5 pin */
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);


		/* Insert delay */
		vTaskDelay(50);
	}
}

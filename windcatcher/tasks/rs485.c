#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"
#include "pwmcapture.h"

#include "uart.h"

/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;

void DMA_Configuration(void);

uint32_t T1, oldT1, cntT1;
uint32_t T2, oldT2, cntT2;

void sendstr(char *str)
{

	uart1Write((uint8_t*) str, strlen(str));
	//	vTaskDelay(100);
	//	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void sendparam(char * name, int value)
{
	char tmp[32] = "";
	int i;
	tmp[0] = '#';
	for (i = 1; *name != 0; i++)
	{
		tmp[i] = *name;
		name++;
	}
	tmp[i] = '(';
#define DNUM 8
	for (int j = DNUM; j > 0; j--)
	{
		tmp[i + j] = value % 10 + '0';
		value /= 10;
	}
	tmp[i + DNUM + 1] = ')';
	tmp[i + DNUM + 2] = ';';
	tmp[i + DNUM + 3] = '\n';
	tmp[i + DNUM + 4] = '\r';
	tmp[i + DNUM + 5] = 0;

	sendstr(tmp);
}

void vRs485Task(void *pvParameters)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* The parameters are not used. */
	(void) pvParameters;

	//	/* Configure USART1 RTS (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8); // allways transive

	ADC_Start();
	pwmcInit();
	T1 = 0;
	T2 = 0;
	uart1Init(115200);
	while (1)
	{

		int32_t adcData[CHANELS_AMOUNT];
		T1 = pwmcGet(0);
		T2 = pwmcGet(1);

		if (T1 == oldT1)
		{
			if (cntT1 > 0)
				cntT1--;
		}
		else
		{
			cntT1 = 8*5; // .4m/s
		}
		if (T2 == oldT2)
		{
			if (cntT2 > 0)
				cntT2--;
		}
		else
		{
			cntT2 = 100; // 20s <3RPM
		}

		if (cntT1 == 0)
		{
			sendparam("T1", 0);
		}
		else
		{
			sendparam("T1", T1);
		}
		if (cntT2 == 0)
		{
			sendparam("T2", 0);
		}
		else
		{
			sendparam("T2", T2);
		}
		oldT1 = T1;
		oldT2 = T2;

		GetADC(adcData);
		sendparam("A1", adcData[0]);
		sendparam("A2", adcData[1]);
		sendparam("A3", adcData[2]);
		vTaskDelay(200);

	}
}


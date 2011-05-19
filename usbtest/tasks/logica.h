#ifndef _LOGICATASK
#define _LOGICATASK
#include "board.h"


#define vLogicaTask_STACK_SIZE	500

extern void vLogicaTask(void *pvParameters )  __attribute__((naked));

#endif

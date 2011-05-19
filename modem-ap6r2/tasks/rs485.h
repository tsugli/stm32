#ifndef _RS485TASK
#define _RS485TASK

#define vRs485Task_STACK_SIZE		500

extern void vRs485Task(void *pvParameters )  __attribute__((naked));


#endif

/*
 * uart.h
 *
 *  Created on: Mar 24, 2011
 *      Author: baron
 */
#ifndef UART_H
#define UART_H

#include "board.h"

#define  USART1_TX_DMA            DMA1_Channel4
#define  USART1_TX_DMA_IRQn       DMA1_Channel4_IRQn
#define  USART1_TX_DMA_IRQHandler DMA1_Channel4_IRQHandler

#define  USART1_RX_DMA          DMA1_Channel6
#define  USART1_RX_DMA_IRQn     DMA1_Channel6_IRQn




#define UARTRX_FIFO_SIZE 1024
#define UARTRX_FIFO_SIZE_MASK (UARTRX_FIFO_SIZE-1)
#define UARTTX_FIFO_SIZE 64

#define UARTTX_FIFO_SIZE_MASK (UARTTX_FIFO_SIZE-1)

#define UARTTX_FIFOB_SIZE UARTRX_FIFO_SIZE
#define UARTTX_FIFOB_SIZE_MASK (UARTTX_FIFOB_SIZE-1)

extern void uart1Init(uint32_t brd);
extern void uart1WriteEscaped(unsigned char *src, unsigned int len);
extern void uart1Write(unsigned char *src, unsigned int len);


extern unsigned int uart1ReadEscaped(unsigned char *dsn, unsigned int max_len);
extern unsigned int uart1Read(unsigned char *dsn, unsigned int max_len);


#endif /*UART_H*/

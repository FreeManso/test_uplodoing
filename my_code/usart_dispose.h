
#ifndef _USART_DISPOSE_H
#define _USART_DISPOSE_H
#include "user_def.h"
#ifdef __cplusplus
extern "C" {
#endif

void X_Start_IDLE_DMA(void);

uint16_t X_UART1_Get_NewBuf(uint8_t *buf);

void X_Uart_IDLE_IT_Dispose(void);


uint8_t X_Uart1_Analyze(uint8_t *recvbuf,X_Order_t *order);


uint8_t X_Uart1_Analyze1(uint8_t *recvbuf,float *order);


uint8_t X_Uart_Analyze_MDBUS(uint8_t *recvbuf,X_Modbus_Order_t *order);

uint16_t X_UART2_Get_NewBuf(uint8_t *buf);

void X_Uart2_IDLE_IT_Dispose(void);

uint8_t X_Uart2_Analyze(uint8_t *recvbuf,X_Modbus_Order_t *order);



uint16_t X_UART3_Get_NewBuf(uint8_t *buf);

void X_Uart3_IDLE_IT_Dispose(void);

uint8_t X_Uart3_Analyze(uint8_t *recvbuf,X_Modbus_Order_t *order);

#endif



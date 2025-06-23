#include <stm32f10x.h>

void UART_Init(int USARTx);
void UART_sendString(int USARTx, char char_toSend[]);
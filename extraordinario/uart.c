#include "uart.h"

void UART_Init(int USARTx)
{
	RCC->APB2ENR|=0x01; //Habilita el reloj para las funciones alternativas
	if(USARTx==3)				//USART3 Tx=PB10 Rx=PB11
	{
		RCC->APB2ENR|=(1<<3);	 //Habilita el reloj al puerto B
		RCC->APB1ENR|=(1<<18); //Habilita el reloj de USART3
		GPIOB->CRH=(0x1B<<8); //Puertos B10 y B11 como AFIO a 50MHz
		
		USART3->CR1=USART_CR1_UE; 	 //Habilita USART3
		USART3->CR2=(0b00<<12); //1 bit de stop
		USART3->BRR=0xEA6;		 //Baud Rate 9600 bps (igual hardcoded y estaría bine cambiarlo pero por ahora estamos bien);
	}
}
void UART_sendString(int USARTx , char char_toSend[])
{
	int u=0;
	
	if(USARTx==3)
		//USART3->SR=(0<<6);
		{
			USART3->CR1|=USART_CR1_TE;
		while(char_toSend[u]!='\0')
		{
					//int tmp=USART3->SR;
					USART3->DR=char_toSend[u];
					//USART3->SR=(0<<6);
					u++;
			while(!(USART3->SR & USART_SR_TC)){};
			}
		}
}


	
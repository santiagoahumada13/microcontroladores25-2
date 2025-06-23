#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>
#include "SysTick_Delay.h"
#include "Teclado4x3.h"
#include "calculadora.h"
#include "uart.h"




int main()
{
	int	op1;
	int	op2;
	int res;
	char op1_send[16];
	char op2_send[16];
	char res_send[32];

	char tecla;
	int pos1=0;
	int pos2=0;
	
	
	SysTick_Init();
	UART_Init(3);
	Teclado_init();
	calc_init();
	while(1)
	{
		GPIOC->ODR=(1<<13);
		tecla=lectura_Teclado();
		if(tecla)
		{
			GPIOC->ODR=(0<<13);
			op1_send[pos1]=tecla;
			pos1++;
			UART_sendString(3,op1_send);
			sscanf(op1_send,"%d",&op1);
			while(lectura_Teclado()!=0)
			{
				delay_s(1);
			}
		}
		if(GPIOA->IDR & (1<<7)) //Suma
		{
			delay_s(1);
			UART_sendString(3,"Suma");
			
			while((GPIOA->IDR & (1<<7))==0)
			{
				
				tecla=lectura_Teclado();
				if(tecla)
				{
					GPIOC->ODR=(0<<13);
					//delay_s(500e-3);
					
					op2_send[pos2]=tecla;
					pos2++;
					UART_sendString(3,op2_send);
					sscanf(op1_send,"%d",&op2);
					while(lectura_Teclado()!=0)
					{
						delay_s(1);
					}
				}
				if(GPIOB->IDR & (1<<3))
				{
					res=Suma(op1,op2);
					sprintf(res_send,"Resultado: %d",res);
					UART_sendString(3,res_send);
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						
					}
				}
				
			}
		}
		
		if(GPIOA->IDR & (1<<8)) //Resta
		{
			delay_s(1);
			UART_sendString(3,"Resta");
			
			while((GPIOA->IDR & (1<<8))==0)
			{
				
				tecla=lectura_Teclado();
				if(tecla)
				{
					GPIOC->ODR=(0<<13);
					//delay_s(500e-3);
					
					op2_send[pos2]=tecla;
					pos2++;
					UART_sendString(3,op2_send);
					sscanf(op2_send,"%d",&op2);
					while(lectura_Teclado()!=0)
					{
						delay_s(1);
					}
				}
				if(GPIOB->IDR & (1<<3))
				{
					res=Resta(op1,op2);
					sprintf(res_send,"Resultado: %d",res);
					
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						delay_s(1);
					}
				}
				
			}
		}
		if(GPIOA->IDR & (1<<9)) //Multiplicacion
		{
			delay_s(1);
			UART_sendString(3,"Multiplicacion");
			
			while((GPIOA->IDR & (1<<9))==0)
			{
				
				tecla=lectura_Teclado();
				if(tecla)
				{
					GPIOC->ODR=(0<<13);
					//delay_s(500e-3);
					
					op2_send[pos2]=tecla;
					pos2++;
					UART_sendString(3,op2_send);
					sscanf(op2_send,"%d",&op2);
					while(lectura_Teclado()!=0)
					{
						delay_s(1);
					}
				}
				if(GPIOB->IDR & (1<<3))
				{
					res=Multiplicacion(op1,op2);
					sprintf(res_send,"Resultado: %d",res);
					
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						delay_s(1);
					}
				}
				
			}
		}
		if(GPIOA->IDR & (1<<10)) //Division
		{
			delay_s(1);
			UART_sendString(3,"Division");
			
			while((GPIOA->IDR & (1<<10))==0)
			{
				
				tecla=lectura_Teclado();
				if(tecla)
				{
					GPIOC->ODR=(0<<13);
					//delay_s(500e-3);
					
					op2_send[pos2]=tecla;
					pos2++;
					UART_sendString(3,op2_send);
					sscanf(op2_send,"%d",&op2);
					while(lectura_Teclado()!=0)
					{
						delay_s(1);
					}
				}
				if(GPIOB->IDR & (1<<3))
				{
					res=Division(op1,op2);
					sprintf(res_send,"Resultado: %d",res);
					
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						delay_s(1);
					}
				}
				
			}
		}
		if(GPIOA->IDR & (1<<11)) //Exponente
		{
			delay_s(1);
			UART_sendString(3,"Exponente");
			
			while((GPIOA->IDR & (1<<11))==0)
			{
				
				tecla=lectura_Teclado();
				if(tecla)
				{
					GPIOC->ODR=(0<<13);
					//delay_s(500e-3);
					
					op2_send[pos2]=tecla;
					pos2++;
					UART_sendString(3,op2_send);
					sscanf(op2_send,"%d",&op2);
					while(lectura_Teclado()!=0)
					{
						delay_s(1);
					}
				}
				if(GPIOB->IDR & (1<<3))
				{
					res=Exponente(op1,op2);
					sprintf(res_send,"Resultado: %d",res);
					
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						delay_s(1);
					}
				}
				
			}
		}
		if(GPIOB->IDR & (1<<5)) //Raiz cuadrada
		{
			delay_s(1);
			UART_sendString(3,"Raiz Cuadrada");
			
			while((GPIOB->IDR & (1<<5))==0)
			{
				if(GPIOB->IDR & (1<<3))
				{
					res=SQRT(op1);
					sprintf(res_send,"Resultado: %d",res);
					
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						delay_s(1);
					}
				}
				
			}
		}
		if(GPIOA->IDR & (1<<15)) //Logaritmo base 4
		{
			delay_s(1);
			UART_sendString(3,"Logaritmo base 4");
			
			while((GPIOA->IDR & (1<<15))==0)
			{
				if(GPIOB->IDR & (1<<3))
				{
					res=logb4(op1);
					sprintf(res_send,"Resultado: %d",res);
					
					while((GPIOB->IDR & (1<<3))!=0)
					{
						delay_s(1);
						UART_sendString(3,res_send);
						delay_s(1);
					}
				}
				
			}
		}
	}
}
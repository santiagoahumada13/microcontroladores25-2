#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>
#include "Teclado4x3.h"

extern int Suma(int a, int b);

extern int Resta(int a, int b);

extern int Multiplicacion(int a, int b);

extern int Division(int a, int b);

extern int Exponente(int a, int b);

extern int SQRT(int a);

extern int logb4(int a);

char tecla;
int pos;

void calc_init()
{
	RCC->APB2ENR|=(1<<3);
	//GPIOA->CRL|=(0x08<<28);
	GPIOA->CRH=0x88888888;
	GPIOB->CRL=(0x808<<12);
}

#include "Teclado4x3.h"

void Teclado_init()
{
	RCC->APB2ENR|=(1<<2); //Activa el reloj para GPIOA
	RCC->APB2ENR|=(1<<4); //PC13 para DEBUG
	
	GPIOC->CRH=(1<<20);
	GPIOA->CRL=0x81111888;// Lineas como salidas, columnas como entradas 
												//PA4-PA7 Lineas, PA3-PA0 Columnas 
	GPIOA->ODR|=0x0000;//PA0-PA3 Pull Down
}	
														//PA		4		5		6		
const unsigned char keys[4][3]=	{{'1','2','3'},		//PA0
																 {'4','5','6'},		//PA1
																 {'7','8','9'},		//PA2
																 {'*','0','#'}};	//PA3

char lectura_Teclado(void)
{
	unsigned char tecla=0,dato=0;
	
	for(int a=0,b=1;a<4;a++)
		{
			//delay_s(2);
			GPIOA->ODR=(b<<3);
			dato=(GPIOA->IDR)&0x7;
			b=b*2;
			if(dato !=0x0)
				tecla=decod_Teclado(dato,a);
		}
		return tecla;
}

static char decod_Teclado(uint8_t col, uint8_t linea)
{
	if (col == 0x1) return keys[linea][0];
	if (col == 0x2) return keys[linea][1];
	if (col == 0x4) return keys[linea][2];
	//if (col == 0x8) return keys[linea][3];
	return 0;
}



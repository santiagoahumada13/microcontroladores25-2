#include <stm32f10x.h>
#include <stdint.h>
#include "SysTick_Delay.h"

void Teclado_init();
char lectura_Teclado(void);
static char decod_Teclado(uint8_t col, uint8_t linea);

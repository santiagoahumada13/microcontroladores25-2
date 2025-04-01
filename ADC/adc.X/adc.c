/* 
 * File:   adc.c
 * Author: santiago
 *
 * Created on 31 de marzo de 2025, 11:00 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4e6
/*
 * 
 */
unsigned int ADC_Read(){
    ADCON0bits.ADCS=0;
    ADCON0bits.CHS=0b000;
    ADCON0bits.ADON=1;
    ADCON1bits.ADFM=1;
    
    __delay_us(6);
    
    ADCON0bits.GO=1;
    
    while(ADCON0bits.nDONE) continue;
    
    return ((int)ADRESH << 8) | ADRESL;
}
void main(){
    unsigned short ADCResult;
    //Salida Digital
    TRISD=0x00;
    PORTD=0;
    //Entrada Analogica
    ANSEL=0x01;
    TRISA=0x01;
    while(1){
        
        ADCResult=ADC_Read();
        PORTD=ADCResult >> 4;
        
    }
  
}


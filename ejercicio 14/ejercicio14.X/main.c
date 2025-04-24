

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



#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ  4e6

unsigned int ADC_Read(){
    ADCON0=0x0D;    //Selecciona:
                    //RA3/AN3 como fuente analogicas
                    //ADON=1 para inicializar el modulo analogico
    __delay_us(25);
    ADCON0bits.GO=1;
    while (ADCON0bits.nDONE==1) continue;
    return ((int)ADRESH<<8)|ADRESL;
}


void main(){
    
    unsigned short  ADCResult;
    
    TRISA=0xFF;//Puerto RA3 como entrada
    ANSEL=0xFF;//Puerto AN3 como entrada analogica
    
    TRISC=0x00;//Puerto C como salida
    PORTC=0x00;
    
    CCP2CON=0x0F; //1100 modo PWM
    
    T2CON=0x04; //TMR2 encencido y  preescaler de 1:16
    PR2=0xFF;   //Periodo de 256us
    
    while(1){
        ADCResult=ADC_Read();
        CCPR2L = (ADCResult>>2);
        CCP2CONbits.DC2B0 = ADCResult & 0x01; 
        CCP2CONbits.DC2B1 = ADCResult & 0x02;
    }
}


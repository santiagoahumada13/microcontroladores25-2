/*
    Santiago Ahumada Sierra 
    Comunicacion serial PIC16F887 Receptor
    Microcontroladores 2809
    M. en C. Jorge Ricardo Gersenowies Rosas
    Semestre 2025-II
    Facultad de Estudios Superiores Cuautitlan
    Universidad Nacional Autonoma de Mexico

*/


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
#define _XTAL_FREQ 4000000//Declare internal OSC Freq as 4MHz

char USARTReadChr(){
    while(PIR1bits.RCIF==0);
    return RCREG;
}

#include <xc.h>

void main() {
    ANSELH=0;
    TRISB=0x00;
    
    PIE1bits.RCIE=1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    
    
    TXSTAbits.TXEN=1;
    TXSTAbits.SYNC=0;
    TXSTAbits.BRGH=1;
    RCSTAbits.SPEN=1;
    RCSTAbits.CREN=1;
    
    SPBRG=25;
    
    PORTB=0x00;
    while(1){
        PORTB=USARTReadChr();
        __delay_ms(100);
    }
}

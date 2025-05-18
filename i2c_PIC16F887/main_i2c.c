/*
 * File:   main.c
 * Author: hammond
 *
 * Created on 11 May 2019, 2:56 PM
 */

#include "common.h"
#include "i2c.h"
#include "ssd1306_unbuffered.h"

void oled_puts(const char* c, uint8_t size) {
    while(*c != '\0') {
        SSD1306_PutStretchC(*c, size);
        c++;
    }
}

void main(void) {
    TRISD ^= 0xFF;
    OSCCONbits.IRCF=0b111;    
    __delay_ms(1000);
    
    
    I2C_Initialize(2000);
    
    SSD1306_Init(SSD1306_EXTERNALVCC, SSD1306_I2C_ADDRESS);
    // clear the display
    SSD1306_ClearDisplay();
        
    
    while(1) {
        PORTD ^= 0xFF;
        SSD1306_GotoXY(1,1);
        oled_puts("SAS", 1);
        
        SSD1306_GotoXY(4,3);
        oled_puts("MC2809", 1);
        
        SSD1306_GotoXY(6,5);
        oled_puts("I2C", 1);
        
        SSD1306_GotoXY(8,7);
        oled_puts("PIC", 1);
        __delay_ms(5000);
        SSD1306_ClearDisplay();
        
    }

    return;
}
#include "i2c.h"

void I2C_Initialize(const unsigned long feq_K){
    TRISCbits.TRISC3=1;
    TRISCbits.TRISC4=1;
    SSPCON=0b00101000;
    SSPCON2=0x00;
    
    SSPADD=(_XTAL_FREQ/(4*feq_K*100))-1;
    SSPSTAT=0x00;
   
}

void I2C_Hold(){
    while((SSPCON2 & 0b00001111)||(SSPSTAT & 0b00000100));
}

void I2C_Begin(){
    I2C_Hold();
    SSPCON2bits.SEN=1;
}

void I2C_End(){
    I2C_Hold();
    SSPCON2bits.PEN=1;
}
void I2C_Write(unsigned data){
    I2C_Hold();
    SSPBUF=data;
}

unsigned short I2C_Read(unsigned short ack){
    unsigned short incoming;
    I2C_Hold();
    SSPCON2bits.RCEN=1;
    
    I2C_Hold();
    incoming=SSPBUF;
    
    I2C_Hold();
    SSPCON2bits.ACKDT=(ack)?0:1;
    ACKEN=1;
    return incoming;
}
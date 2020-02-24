
// * File:   LCD_Instructions.h
// * Author:Juan Gonzalez
// *carne:17594
// * Ejemplo de librerias sacados de ejemplos de Pablo Mazariegos
// * Inicializacion de LCD con ayuda de Rodrigo Figueroa
// * //pasar enteros a Decimales sacados de GEEKS
// * Created on 10 de febrero de 2020, 10:03 PM

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include "LCD.h"

void Recieve(void){
      PIR1bits.RCIF= 1;
       if(PIR1bits.RCIF== 1){
     
        cur(2,13);
        ADCread3();  
        cur(2,14);
        ADCread4();
        PIR1bits.RCIF=0;
    } 
    
    
    
    
    if(PIR1bits.TXIF==1){
     ADCON0bits.CHS = 0b1011;
     ADCON0bits.GO_DONE=1;
    while(ADCON0bits.GO_DONE);
    TXREG= ADRESH;
    PIR1bits.TXIF=0;
    }
    
    }
    
void main(void) {
    TRISA= 0;
    TRISD = 0;
    //TRISCbits.TRISC7 = 1;
    PORTA = 0;
    PORTD = 0;
    PORTC=0;
    TRISC=0;
    
   
    
    /////Com Serial
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH =1;
  
    BAUDCTLbits.BRG16 = 1;
    SPBRG = 25;
    SPBRGH = 0;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    TXSTAbits.TXEN = 1;
    PORTD = 0;
    
    ///
    ADCinit();
    lcd_init();
    lcd_clear();
    __delay_ms(250);
    
    while(1){
     
        cur(1,1);
        word("P1");
        cur(1,7);
        word("P2");
        cur(1,13);
        word("P3");
        
        cur(2,5);
        word("v");
        cur(2,11);
        word("v");
        
        
        
        ADCON0bits.CHS = 0b1101;
        cur(2,2);
        lee1();
        cur(2,1);
       
        lee2();
        __delay_ms(10);
        ADCON0bits.CHS = 0b1011;
        cur(2,8);
        lee1();
        cur(2,7);
        lee2();
        __delay_ms(10);
       

        Recieve();
  
        __delay_ms(50);
        __delay_ms(250);
        
    }
}

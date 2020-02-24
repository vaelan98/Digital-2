//*****************************************************************************
/*
 * File:   main.c
 * Author: Juan Gerardo Gonzalez MOrales carne 17594
 * Ejemplo de implementación de la comunicación SPI 
 * Código Maestro sacado de codigos ePalbo Escobar de Gitgub
 * https://github.com/pdmazariegos-uvg/ie3027/tree/master/Ejemplos/SPI
 * Created on 10 de febrero de 2020, 03:32 PM
 * Ejemplo de SPI master sacado de 
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "LCD2.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

uint8_t valor;
uint8_t valor2;



//*****************************************************************************
// Código Principal
//***************************************
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
     TXREG= valor;
    PIR1bits.TXIF=0;
    }
    
    
   
    
      if(PIR1bits.TXIF==1){
     TXREG= valor2;
    PIR1bits.TXIF=0;
    }
    }

void main(void) {
    setup();
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
    
   
    
    /////Com Serial
    
    PORTD = 0;
    
    ///
    PORTBbits.RB0=0;
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
        Recieve();
        __delay_ms(50);
         PORTCbits.RC2 = 0;       //Slave Select
        spiWrite(1);
 
        valor =spiRead();
        
        cur(2,1);
        lee2(valor);
        cur(2,2);
        lee1(valor); 
        PORTCbits.RC2 = 1;       //Slave Deselect 
         __delay_ms(50);
          PORTCbits.RC2 = 0;  
        spiWrite(0);
        valor2 =spiRead();
        cur(2,7);
        lee4(valor2);
        
        cur(2,8);
        lee3(valor2);
         PORTCbits.RC2 = 1; 
       
        
       
         
        PORTBbits.RB0=1;
        
       
        
        

        
       
        
        

     

        

       
  
       
    }}
    

    
    

//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL=0;
    ANSELH=0;
    TRISA=0;
    PORTA=0;
    TRISC2 = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}
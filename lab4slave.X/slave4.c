//*****************************************************************************
/*
 * File:   main.c
 * Author: Juan Gerardo Gonzalez MOrales carne 17594
 * Ejemplo de implementaci�n de la comunicaci�n SPI 
 * C�digo Maestro sacado de codigos ePalbo Escobar de Gitgub
 * https://github.com/pdmazariegos-uvg/ie3027/tree/master/Ejemplos/SPI
 * Created on 10 de febrero de 2020, 03:32 PM
 * Ejemplo de SPI master sacado de 
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuraci�n
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
// Definici�n e importaci�n de librer�as
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
//*****************************************************************************
// Definici�n de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
uint8_t coso;
uint8_t coso2;

uint8_t valor1;
uint8_t valor2;
uint8_t valor3;
uint8_t valor4;
uint8_t valor5;
//*****************************************************************************
// Definici�n de funciones para que se puedan colocar despu�s del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//**************** *************************************************************
void setup(void);
//*****************************************************************************
// C�digo de Interrupci�n 
//*****************************************************************************

//*****************************************************************************
// C�digo Principal
//**************************
void __interrupt() isr(void){
   if(SSPIF == 1){
       //Recieve();
     PORTD = spiRead();
     if (PORTD==2){
        spiWrite(4);
        
        SSPIF = 0;
        
     }
       }
}
void Recieve(void);
void Recieve(void){
      PIR1bits.RCIF= 1;
       if(PIR1bits.RCIF== 1){
           valor1= RCREG;
           PIR1bits.RCIF=0;
       }
      
        PIR1bits.RCIF=0;
        if(PIR1bits.RCIF== 1){
           valor2= RCREG;
             PIR1bits.RCIF=0;
        }
        PIR1bits.RCIF=0;
        if(PIR1bits.RCIF== 1){
           valor3= RCREG;
             PIR1bits.RCIF=0;
        }
        PIR1bits.RCIF=0;
        if(PIR1bits.RCIF== 1){
           valor4= RCREG;
             PIR1bits.RCIF=0;
        }
        PIR1bits.RCIF=0;
        if(PIR1bits.RCIF== 1){
           valor5= RCREG;
             PIR1bits.RCIF=0;
        }
       
       } 

void main(void) {
    setup();
   
    
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        
     
         
         
    }}
//*****************************************************************************
// Funci�n de Inicializaci�n
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH=1;
    
    TRISB = 1;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    PORTE=0;
    TRISE=0;
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupci�n MSSP
    PIE1bits.SSPIE = 1; 
    // Habilitamos interrupci�n MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    ANSELbits.ANS0=1;
    ANSELbits.ANS1=1;
    ANSELbits.ANS2=1;
    spiInit(SPI_SLAVE_SS_DIS, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}
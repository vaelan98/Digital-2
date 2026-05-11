/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Esclavo
 * Created on 17 de febsacado de http://www.todopic.com.ar/foros/index.php?topic=49049.0ero de 2020, 10:32 AM
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
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
#define CLK RB7
#define Da RB6
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
#define _XTAL_FREQ 4000000
//*****************************************************************************
// Definición de variables
//*****************************************************************************

uint8_t z;
uint8_t dato;
uint8_t a;

uint8_t numero2;
    uint8_t numero;
    char buffer[4];

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
void Lcd_Write_Int(uint8_t numero);
//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
    
    



   if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            
         
            SSPBUF = numero2;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
}
//*****************************************************************************
// Main
//*****************************************************************************



signed long int ReadCount()        /* Function to read measurement from HX711 */
{
    signed long int Count;
    float gram;
    unsigned char i;
    Da=1; 
    CLK = 0;                     /* Clear Clock line to start conversion */
    Count = 0;
    while (Da);      /* Wait for measurement conversion. */
    for (i=0; i<24; i++)
    {
        CLK = 1;           /* Clock signal High */
        __delay_us(10);
        Count = Count << 1;       /* Shift value left */
        
        CLK = 0;            /* Clock signal Low */
        __delay_us(10);
        if(Da) Count++; 
       
    }
    
    
    for (i=0; i<3; i++)
    {   
        CLK = 0;
        __delay_us(300);
        CLK = 0;
        __delay_us(300);
    }
    
    CLK = 1;
    Count = Count^0x800000;
    gram=8388608-Count;
    gram=gram-724000;
    __delay_us(10);
    CLK = 0;
    return gram;
}
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
//    TXSTAbits.SYNC = 0;
//    TXSTAbits.BRGH =1;
//  
//    BAUDCTLbits.BRG16 = 1;
//    SPBRG = 25;
//    SPBRGH = 0;
//    RCSTAbits.SPEN = 1;
//    RCSTAbits.RX9 = 0;
//    RCSTAbits.CREN = 1;
//    TXSTAbits.TXEN = 1;
//    
//    TRISBbits.TRISB0 = 0;
//    TRISBbits.TRISB1 = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    
    ANSELH = 0;
    ANSEL = 0;
    
    //
    uint32_t data;
   
    //
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB6 = 1;
 
    
    
  
    while(1){
        
        
        data = ReadCount()>>13;
        numero2=lcd(data);
       
        
        
        
        
}
       
       
  
        }
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
   
    I2C_Slave_Init(0x80);   
}
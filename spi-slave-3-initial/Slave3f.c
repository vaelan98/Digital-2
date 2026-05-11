/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Esclavo
 * Created on 17 de febrero de 2020, 10:32 AM
 */
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
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
uint8_t z;
uint8_t dato;
uint8_t coso2;
char Temperature[] = "Temp = 00.0 C  ";
char Humidity[]    = "RH   = 00.0 %  ";
unsigned char T_Byte1, T_Byte2, RH_Byte1, RH_Byte2, CheckSum ;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
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
            SSPBUF = Humidity;
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

 
// DHT11 sensor connection (here data pin is connected to RB0)
#define DHT11_PIN      RB0
#define DHT11_PIN_DIR  TRISB0
 

 
#include <xc.h>
#define _XTAL_FREQ 8000000
 
void Start_Signal(void) {
  DHT11_PIN_DIR = 0;     // configure DHT11_PIN as output
  DHT11_PIN = 0;         // clear DHT11_PIN output (logic 0)
 
  __delay_ms(25);        // wait 25 ms
  DHT11_PIN = 1;         // set DHT11_PIN output (logic 1)
 
  __delay_us(30);        // wait 30 us
  DHT11_PIN_DIR = 1;     // configure DHT11_PIN as input
}
 
// Check sensor response
__bit Check_Response() {
  TMR1H = 0;                 // reset Timer1
  TMR1L = 0;
  TMR1ON = 1;                // enable Timer1 module
 
  while(!DHT11_PIN && TMR1L < 100);  // wait until DHT11_PIN becomes high (checking of 80µs low time response)
 
  if(TMR1L > 99)                     // if response time > 99µS  ==> Response error
    return 0;                        // return 0 (Device has a problem with response)
 
  else
  {
    TMR1H = 0;               // reset Timer1
    TMR1L = 0;
 
    while(DHT11_PIN && TMR1L < 100); // wait until DHT11_PIN becomes low (checking of 80µs high time response)
 
    if(TMR1L > 99)                   // if response time > 99µS  ==> Response error
      return 0;                      // return 0 (Device has a problem with response)
 
    else
      return 1;                      // return 1 (response OK)
  }
}
 
// Data read function
__bit Read_Data(unsigned char* dht_data)
{
  *dht_data = 0;
 
  for(char i = 0; i < 8; i++)
  {
    TMR1H = 0;             // reset Timer1
    TMR1L = 0;
 
    while(!DHT11_PIN)      // wait until DHT11_PIN becomes high
      if(TMR1L > 100) {    // if low time > 100  ==>  Time out error (Normally it takes 50µs)
        return 1;
      }
 
    TMR1H = 0;             // reset Timer1
    TMR1L = 0;
 
    while(DHT11_PIN)       // wait until DHT11_PIN becomes low
      if(TMR1L > 100) {    // if high time > 100  ==>  Time out error (Normally it takes 26-28µs for 0 and 70µs for 1)
        return 1;          // return 1 (timeout error)
      }
 
     if(TMR1L > 50)                  // if high time > 50  ==>  Sensor sent 1
       *dht_data |= (1 << (7 - i));  // set bit (7 - i)
  }
 
  return 0;                          // return 0 (data read OK)
}
 
void main(void)
{
    setup();
  OSCCON =  0X70;       // set internal oscillator to 8MHz
  ANSELH = 0;           // configure all PORTB pins as digital
  T1CON  = 0x10;        // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
  TMR1H  = 0;           // reset Timer1
  TMR1L  = 0;
 
           // initialize LCD module
 
  while(1)
  {
    Start_Signal();     // send start signal to the sensor
 
    if(Check_Response())    // check if there is a response from sensor (If OK start reading humidity and temperature data)
    {
      // read (and save) data from the DHT11 sensor and check time out errors
      
 
      
        if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))
        {                                       // if there is no checksum error
          Temperature[7]  = T_Byte1 / 10  + '0';
          Temperature[8]  = T_Byte1 % 10  + '0';
          Temperature[10] = T_Byte2 / 10  + '0';
          Humidity[7]     = RH_Byte1 / 10 + '0';
          Humidity[8]     = RH_Byte1 % 10 + '0';
          Humidity[10]    = RH_Byte2 / 10 + '0';
          Temperature[11] = 223;    // put degree symbol (°)
        
        }
 
        // if there is a checksum error
       
 
      
    }
 
    // if there is a response (from the sensor) problem
    
 
    TMR1ON = 0;        // disable Timer1 module
    
 
  }
 
}
// End of code.
// End of code.
void setup(void){
    
    
    TRISD = 0;
    
    
    PORTD = 0;
    I2C_Slave_Init(0x70);   
}
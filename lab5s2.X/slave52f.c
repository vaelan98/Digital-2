/*
 * File:   Slave_contador.c
 
 *sacado de https://electrosome.com/hc-sr04-ultrasonic-sensor-pic/
 * Created on 23 de febrero de 2020, 05:22 PM
 */

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
#include <xc.h>
#include <stdint.h>
#include "I2C.h"
#include <pic16f887.h>
#define _XTAL_FREQ 8000000

short z;
uint8_t coso2;
uint8_t BmenosO;
uint8_t Contador;
uint8_t masterval;
int a;

void setup(void);
void __interrupt() isr(void)
{
  if(SSPIF == 1)
  {
    SSPCONbits.CKP = 0;

    if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)) //If overflow or collision
    {
      z = SSPBUF; // Read the previous value to clear the buffer
      SSPCONbits.SSPOV = 0; // Clear the overflow flag
      SSPCONbits.WCOL = 0; // Clear the collision bit
      SSPCONbits.CKP = 1;
    }

  if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) //If last byte was Address + Write
  {
    z = SSPBUF;
    PIR1bits.SSPIF = 0;
    SSPCONbits.CKP = 1;
    while(!BF);
    masterval = SSPBUF;
     __delay_us(250);
    
  }
  else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW) //If last byte was Address + Read
  {
    z = SSPBUF;
    BF = 0;
    SSPBUF = a;
    SSPCONbits.CKP = 1;
     __delay_us(250);
    while(SSPSTATbits.BF);
  }

  PIR1bits.SSPIF = 0;
  }
  return;
}


void main(void)
{ 
  
 setup();
  TRISB = 0b00010000;         //RB4 as Input PIN (ECHO)
              // LCD Pins as Output

 

  
 
  T1CON = 0x10;               //Initialize Timer Module
 __delay_ms(3000);
  while(1)
  { 
    TMR1H = 0;                //Sets the Initial Value of Timer
    TMR1L = 0;                //Sets the Initial Value of Timer

    RB0 = 1;                  //TRIGGER HIGH
    __delay_us(10);           //10uS Delay 
    RB0 = 0;                  //TRIGGER LOW

    while(!RB4);              //Waiting for Echo
    TMR1ON = 1;               //Timer Starts
    while(RB4);               //Waiting for Echo goes LOW
    TMR1ON = 0;               //Timer Stops

    a = (TMR1L | (TMR1H<<8)); //Reads Timer Value
    a = a/58.82;              //Converts Time to Distance
    a = a + 1;                //Distance Calibration
     if(a>=2 && a<=400)          //Check whether the result is valid or not
    {
        int b=a;
     }
    __delay_ms(400);
  }
}
void setup(void){
    ANSEL = 0;
    ANSELH=0;
    TRISB=0;
    OSCCONbits.IRCF0=1;
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF1=1;
    PORTB = 0;
    PORTD = 0;
    I2C_Slave_Init(0x60);   
}
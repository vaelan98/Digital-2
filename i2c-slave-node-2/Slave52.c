/*
 * File:   Slave_contador.c
 * Author: rodri
 *
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
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
#define _XTAL_FREQ 8000000
#define Bmas PORTBbits.RB7
#define Bmenos PORTBbits.RB6
short z;
uint8_t BmasO;
uint8_t BmenosO;
uint8_t Contador;
uint8_t masterval;
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
    SSPBUF = Contador ;
    SSPCONbits.CKP = 1;
     __delay_us(250);
    while(SSPSTATbits.BF);
  }

  PIR1bits.SSPIF = 0;
  }
  return;
}


void main(void) {
    ANSEL = 0;
    ANSELH =0;
    TRISB = 0b11000000;
    TRISA = 0;
    PORTA = 0;
    PORTB =0;
    BmasO = 0;
    BmenosO = 0;
    Contador = 0;
     I2C_Slave_Init(0x30); //Initialize as a I2C Slave with address 0x30
  while(1){
      if(Bmas == 0 && BmasO == 1 && Contador < 16 ){
    
          Contador ++;
      
      }
      else if(Bmenos == 0 && BmenosO == 1 && Contador > 0){
         
             Contador --; 
          
          
      }
      PORTA = Contador;// & 0b00001111;
      BmasO = Bmas;
      BmenosO = Bmenos;
  }
}
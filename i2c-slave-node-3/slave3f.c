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
//sacado de https://github.com/Nibed/DS18B20_TempSensor_1Wire_protocol_for_PIC_18F4520_on_XC8.X
#pragma config CONFIG1 = 0x2CD4
#pragma config CONFIG2 = 0x0700   // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I3C.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************


// DS18B20 data pin is connected to pin RB1
#define DS18B20_PIN      RB1
#define DS18B20_PIN_Dir  TRISB1
 

 
#include <xc.h>
#define _XTAL_FREQ 8000000
#include <stdint.h>        // include stdint header
int d;
int a;
int d2;
int b; 
int z;
uint8_t valor3;
uint8_t valor4;
uint16_t raw_temp;
uint16_t raw_temp2;
char     temp[] = "000.0000 C ";
char     temp2[] = "000.0000 C ";
void setup(void);
void __interrupt() isr(void){
   if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF; 
            // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z= SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
           
            SSPBUF=temp2[1];
            
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
} 
__bit ds18b20_start()
{
  DS18B20_PIN = 0;      // send reset pulse to the DS18B20 sensor
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  __delay_us(500);      // wait 500 us
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  __delay_us(100);      // wait 100 us to read the DS18B20 sensor response
 
  if (!DS18B20_PIN)
  {
    __delay_us(400);    // wait 400 us
    return 1;           // DS18B20 sensor is present
  }
 
  return 0;   // connection error
}
 
void ds18b20_write_bit(uint8_t value)
{
  DS18B20_PIN = 0;
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  __delay_us(2);        // wait 2 us
 
  DS18B20_PIN = (__bit)value;
  __delay_us(80);       // wait 80 us
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  __delay_us(2);        // wait 2 us
}
 
void ds18b20_write_byte(uint8_t value)
{
  for(uint8_t i = 0; i < 8; i++)
    ds18b20_write_bit(value >> i);
}
 
__bit ds18b20_read_bit(void)
{
  static __bit value;
 
  DS18B20_PIN = 0;
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  __delay_us(2);
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  __delay_us(5);        // wait 5 us
 
  value = DS18B20_PIN;  // read and store DS18B20 state
  __delay_us(100);      // wait 100 us
 
  return value;
}
 
uint8_t ds18b20_read_byte(void)
{
  uint8_t value = 0;
 
  for(uint8_t i = 0; i < 8; i++)
    value |= ds18b20_read_bit() << i;
 
  return value;
}
 
__bit ds18b20_read(uint16_t *raw_temp_value)
{
  if (!ds18b20_start())   // send start pulse
    return 0;             // return 0 if error
 
  ds18b20_write_byte(0xCC);   // send skip ROM command
  ds18b20_write_byte(0x44);   // send start conversion command
 
  while(ds18b20_read_byte() == 0);  // wait for conversion complete
 
  if (!ds18b20_start())  // send start pulse
    return 0;            // return 0 if error
 
  ds18b20_write_byte(0xCC);  // send skip ROM command
  ds18b20_write_byte(0xBE);  // send read command
 
  // read temperature LSB byte and store it on raw_temp_value LSB byte
  *raw_temp_value  = ds18b20_read_byte();
  // read temperature MSB byte and store it on raw_temp_value MSB byte
  *raw_temp_value |= (uint16_t)(ds18b20_read_byte() << 8);
 
  return 1;   // OK --> return 1
}
 
/*************************** main function *********************/
void main(void)
{
  setup();  
  OSCCON = 0x70;   // set internal oscillator to 8MHz
  ANSELH = 0;      // configure all PORTB pins as digital
 
  z=0;
  b=0;
 
 // put degree symbol ( ° )
 
  
 
 
 
  
    while(1)
  {
    
         
    
      
     if(ds18b20_read(&raw_temp)){
     if(raw_temp & 0x8000)  // if the temperature is negative
      {
        temp[0] = '-';             // put minus sign (-)
        raw_temp = (~raw_temp) + 1;  // change temperature value to positive form
      }
 
      else
      {
        if((raw_temp >> 4) >= 100)  // if the temperature >= 100 °C
          temp[0] = '1';            // put 1 of hundreds
        else                        // otherwise
          temp[0] = ' ';            // put space ' '
      }
 
      // put the first two digits ( for tens and ones)
      temp[1] =((raw_temp >> 4) / 10  % 10) + '0';  // put tens digit
      temp[2] =   (raw_temp  >> 4)         ;  // put ones digit
 
      // put the 4 fraction digits (digits after the point)
      // why 625?  because we're working with 12-bit resolution (default resolution)
      temp[4] = ( (raw_temp & 0x0F) * 625) / 1000 + '0';          // put thousands digit
      temp[5] = (((raw_temp & 0x0F) * 625) / 100 ) % 10 + '0';    // put hundreds digit
      temp[6] = (((raw_temp & 0x0F) * 625) / 10 )  % 10 + '0';    // put tens digit
      temp[7] = ( (raw_temp & 0x0F) * 625) % 10 + '0';            // put ones digit
      
         temp2[1]=temp[2];
         
        
      }
      }
  
      
     }
     
 

    
 
    
void setup(void){
    
    
    TRISB=1;
    PORTD = 0;
    I2C_Slave_Init(0x70);   
}

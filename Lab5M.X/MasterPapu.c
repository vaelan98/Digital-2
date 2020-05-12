/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Master
 * Created on 17 de febrero de 2020, 10:32 AM
 *reloj sacado de https://simple-circuit.com/mplab-xc8-ds1307-ds3231-pic-mcu/
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
#include "LCD2.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

#define CLK RB7
#define Da RB6

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//****************************************************************************
void setup(void);

//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
unsigned short read_ds1307(unsigned short address)
{
unsigned short r_data;
  I2C_Master_Start();
  I2C_Master_Write(0xD0); //address 0x68 followed by direction bit (0 for write, 1 for read) 0x68 followed by 0 --> 0xD0
  I2C_Master_Write(address);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(0xD1); //0x68 followed by 1 --> 0xD1
  r_data=I2C_Master_Read(0);
  I2C_Master_Stop();
  return(r_data);
}

void write_ds1307(unsigned short address,unsigned short w_data)
{
  I2C_Master_Start(); // issue I2C start signal
  //address 0x68 followed by direction bit (0 for write, 1 for read) 0x68 followed by 0 --> 0xD0
  I2C_Master_Write(0xD0); // send byte via I2C (device address + W)
  I2C_Master_Write(address); // send byte (address of DS1307 location)
  I2C_Master_Write(w_data); // send data (data to be written)
  I2C_Master_Stop(); // issue I2C stop signal
}

unsigned char BCD2UpperCh(unsigned char bcd)
{
  return ((bcd >> 4) + '0');
}

unsigned char BCD2LowerCh(unsigned char bcd)
{
  return ((bcd & 0x0F) + '0');
}

int Binary2BCD(int a)
{
  int t1, t2;
  t1 = a%10;
  t1 = t1 & 0x0F;
  a = a/10;
  t2 = a%10;
  t2 = 0x0F & t2;
  t2 = t2 << 4;
  t2 = 0xF0 & t2;
  t1 = t1 | t2;
  return t1;
}
 
int BCD2Binary(int a)
{
  int r,t;
  t = a & 0x0F;
  r = t;
  a = 0xF0 & a;
  t = a >> 4;
  t = 0x0F & t;
  r = t*10 + r;
  return r;
}

int second;
int minute;
int hour;
int hr;
int day;
int dday;
int month;
int year;
int ap;

unsigned short set_count = 0;
short set;
 
char time[] = "00:00:00 PM";
char date[] = "00-00-00";
uint16_t valor;
uint8_t valor2;
uint8_t peso;
uint16_t valor3;
uint16_t valor4;
uint8_t z;
uint16_t raw_temp;
uint16_t raw_temp2;
char     temp[] = "000.00 C ";
char     temp2[] = "000.00 C ";
char     dis[] = "00 ";
char     dis2[] = "0 ";
char     pes[] = "000 ";
int c;
char     pes2[] = "000  ";


   void receive(void);
   void receive(void){
     if(PIR1bits.TXIF==1){
     TXREG= hour;
    PIR1bits.TXIF=0;
    }
      if(PIR1bits.TXIF==1){
     TXREG= valor;
    PIR1bits.TXIF=0;
      }
    if(PIR1bits.TXIF==1){
     TXREG= c;
    PIR1bits.TXIF=0;
    }
      if(PIR1bits.TXIF==1){
     TXREG= pes2[4];
    PIR1bits.TXIF=0;
      }
       if(PIR1bits.TXIF==1){
     TXREG= temp2[1] ;
    PIR1bits.TXIF=0;
    
      }}
//   signed long int ReadCount()        /* Function to read measurement from HX711 */
//{
//    signed long int Count;
//    float gram;
//    unsigned char i;
//    Da=1; 
//    CLK = 0;                     /* Clear Clock line to start conversion */
//    Count = 0;
//    while (Da);      /* Wait for measurement conversion. */
//    for (i=0; i<24; i++)
//    {
//        CLK = 1;           /* Clock signal High */
//        __delay_us(10);
//        Count = Count << 1;       /* Shift value left */
//        
//        CLK = 0;            /* Clock signal Low */
//        __delay_us(10); 
//        if(Da) Count++; 
//       
//    }
//    
//    
//    for (i=0; i<3; i++)
//    {   
//        CLK = 0;
//        __delay_us(300);
//        CLK = 0;
//        __delay_us(300);
//    }
//    
//    CLK = 1;
//    Count = Count^0x800000;
//    gram=8388608-Count;
//    gram=gram-724000;
//    __delay_us(10);
//    CLK = 0;
//    return gram;
//}
//*****************************************************************************
// Main
//*****************************************************************************
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
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
     
    ANSELH = 0;
    ANSEL = 0;
    
    //
//    uint32_t data;
//    char buffer[20];
    //
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB6 = 1;
// 
     lcd_init();
    lcd_clear();
    __delay_ms(250);
//    
   temp[6] = 223;
   while(1){
//        
//        
//        data = ReadCount()>>13;
//        cur(1,1);
//        Lcd_Write_Int(data);
//       
//       
//  
//        }}
        receive();
    set = 0;
  
    if(PORTBbits.RB0 == 1)
    {
      __delay_ms(100);
      if(PORTBbits.RB0 == 1)
      {
        set_count++;
        if(set_count >= 7)
        {
          set_count = 0;
        }
      }
    }
    if(set_count)
    {
      if(PORTBbits.RB1 == 1)
      {
        __delay_ms(100);
        if(PORTBbits.RB1== 1)
          set = 1;
      }
      if(PORTBbits.RB2 == 1)
      {
         __delay_ms(100);
         if(PORTBbits.RB2 == 1)
           set = -1;
      }
      if(set_count && set)
      {
        switch(set_count)
        {
          case 1:
                  hour = BCD2Binary(hour);
                  hour = hour + set;
                  hour = Binary2BCD(hour);
                  if((hour & 0x1F) >= 0x13)
                  {
                    hour = hour & 0b11100001;
                    hour = hour ^ 0x20;
                  }
                  else if((hour & 0x1F) <= 0x00)
                  {
                     hour = hour | 0b00010010;
                     hour = hour ^ 0x20;
                  }
                  write_ds1307(2, hour); //write hour
                  break;
          case 2:
                  minute = BCD2Binary(minute);
                  minute = minute + set;
                  if(minute >= 60)
                    minute = 0;
                  if(minute < 0)
                    minute = 59;
                  minute = Binary2BCD(minute);
                  write_ds1307(1, minute); //write min
                  break;
          case 3:
                  if(abs(set))
                  write_ds1307(0,0x00); //Reset second to 0 sec. and start Oscillator
                  break;
          case 4:
                  day = BCD2Binary(day);
                  day = day + set;
                  day = Binary2BCD(day);
                  if(day >= 0x32)
                    day = 1;
                  if(day <= 0)
                    day = 0x31;
                  write_ds1307(4, day); // write date 17
                  break;
          case 5:
                  month = BCD2Binary(month);
                  month = month + set;
                  month = Binary2BCD(month);
                  if(month > 0x12)
                    month = 1;
                  if(month <= 0)
                    month = 0x12;
                  write_ds1307(5,month); // write month 6 June  
                  break;
          case 6:
                  year = BCD2Binary(year);
                  year = year + set;
                  year = Binary2BCD(year);
                  if(year <= -1)
                    year = 0x99;
                  if(year >= 0x50)
                    year = 0;
                  write_ds1307(6, year); // write year
                  break;
        }
      
      }
    }
    
    second = read_ds1307(0);
    minute = read_ds1307(1);
    hour = read_ds1307(2); 
    hr = hour & 0b00011111; 
    ap = hour & 0b00100000;
    day = read_ds1307(3);
    day = read_ds1307(4);
    month = read_ds1307(5);
    year = read_ds1307(6);

    time[0] = BCD2UpperCh(hr);
    time[1] = BCD2LowerCh(hr);
    time[3] = BCD2UpperCh(minute);
    time[4] = BCD2LowerCh(minute);
    time[6] = BCD2UpperCh(second);
    time[7] = BCD2LowerCh(second);

    date[0] = BCD2UpperCh(day);
    date[1] = BCD2LowerCh(day);
    date[3] = BCD2UpperCh(month);
    date[4] = BCD2LowerCh(month);
    date[6] = BCD2UpperCh(year);
    date[7] = BCD2LowerCh(year);

    if(ap)
    {
      time[9] = 'P';
      time[10] = 'M';
    }
    else
    {
      time[9] = 'A';
      time[10] = 'M';
    } 
    cur(2,6);
    word( time);
   
 
 
 // put degree symbol ( ° )
 
  
 
 
 
  
    
   
   
    {
      if(temp2[1] & 0x8000)  // if the temperature is negative
      {
        temp2[0] = '-';             // put minus sign (-)
        temp2[1] = (~temp2[1]) + 1;  // change temperature value to positive form
      }
 
      else
      {
        if((temp2[1] >> 4) >= 100)  // if the temperature >= 100 °C
          temp2[0] = '1';            // put 1 of hundreds
        else                        // otherwise
          temp2[0] = ' ';            // put space ' '
      }
 
 
      // put the first two digits ( for tens and ones)
      temp[1] =((temp2[1]) / 10  % 10) + '0';  // put tens digit
      temp[2] =   (temp2[1]) % 10 + '0'   ;   // put ones digit
 
      // put the 4 fraction digits (digits after the point)
      // why 625?  because we're working with 12-bit resolution (default resolution)
      temp[4] = ( (temp2[1]& 0x0F) * 625) / 1000 + '0';          // put thousands digit
      temp[5] = (((temp2[1] & 0x0F) * 625) / 100 ) % 10 + '0';    // put hundreds digit
      
    }
    
   
    
//        cur(1,1);
//        word("P1");
//        cur(1,7);
//        word("P2");
//        cur(1,13);
//        word("P3");
     
      //----------------------Sensor 1----------------------------
        PORTDbits.RD3=1;
        I2C_Master_Start();
        I2C_Master_Write(0x51);   
        valor = I2C_Master_Read(0);
        I2C_Master_Stop();
        dis2[0]= (valor) +'0';
        cur(2,3);
        word(dis2 );
        cur(2,1);
        lee2(valor);
//        
////    /----------------------Sensor 2----------------------------   
         I2C_Master_Start();
        I2C_Master_Write(0x61);   
        c = I2C_Master_Read(0);
        I2C_Master_Stop();
       
      
       
        dis[0]= (c/10) %10+'0';
        dis[1]= c %10+'0';
      cur(1,10);
      word(dis );
     
      //----------------------Sensor 3----------------------------
      I2C_Master_Start();
      I2C_Master_Write(0x71); 
      temp2[1] = I2C_Master_Read(0);
      I2C_Master_Stop();
      cur(1,1);
      word(temp);
       //----------------------Sensor 4----------------------------
       I2C_Master_Start();
      I2C_Master_Write(0x81); 
      pes[4] =I2C_Master_Read(0);
      I2C_Master_Stop();
      pes2[2]=(pes[4])%10+'0';
      pes2[1]=(pes[4]/10)%10+'0'; 
      pes2[0]=(pes[4]/100)%10+'0'; 
       cur(1,13);
       word(pes2);
       
       //--------------------MOtor DC-------------------------------
       if(temp[1]==3+'0' && temp[2]==6+'0')
       { 
       I2C_Master_Start();
      I2C_Master_Write(0x91); 
      raw_temp =I2C_Master_Read(0);
      I2C_Master_Stop();
   }
      //--------------------MOtor esteper-------------------------------
       if(dis[0]<=1+'0' || dis2[0]>=8+'0'){
        
       I2C_Master_Start();
      I2C_Master_Write(0x31); 
      raw_temp =I2C_Master_Read(0);
      I2C_Master_Stop();
      
       }
       //---------------------------servo----------------------
       
        if( pes2[1]>=8+'0'){
        
       I2C_Master_Start();
      I2C_Master_Write(0x41); 
      raw_temp2 =I2C_Master_Read(0);
      I2C_Master_Stop();
      
       }
      
      
   }}    

 
        
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    PORTA=0;
    TRISA=0;
    PORTCbits.RC2 = 1;
    PORTCbits.RC2 = 1;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
}
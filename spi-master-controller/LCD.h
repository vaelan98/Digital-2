/* 
 * File:   LCD_Instructions.h
 * Author:Juan Gonzalez
 *carne:17594
 * Ejemplo de librerias sacados de ejemplos de Pablo Mazariegos
 * Inicializacion de LCD con ayuda de Rodrigo Figueroa
 * //pasar enteros a Decimales sacados de GEEKS
 * Created on 10 de febrero de 2020, 10:03 PM
 */

#ifndef __LCD_H_
#define	__LCD_H_
#define RS PORTDbits.RD0
#define EN PORTDbits.RD2

#define _XTAL_FREQ 4000000
#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned char *guardar[10];
unsigned char *guardar2[10];
uint8_t i;
uint8_t Voldc;
uint8_t Voldc2;
uint8_t enviar;

double voltaje;
double voltaje2;

void caracter(uint8_t info);
void ftoa2(float m, char* Q, int puntor);
void ADCinit(void){
    ADCON1bits.ADFM =0;
    ADCON1bits.VCFG0 =0;
    ADCON1bits.VCFG1 =0;
    ADCON0bits.ADCS0 =1;
    ADCON0bits.ADCS1 =0;
    ADCON0bits.ADON = 1;
                   }

void port(char E){
    PORTA = E;
}

void com(char E){
    RS = 0;
    port(E);
    EN = 1;
    __delay_us(5);
    EN = 0;
}

void lcd_clear(void){
	com(0);
	com(1);
}
void cur(char a, char b){
	char tiempo;
	if(a == 1)
	{
	  tiempo = 0x80 + b - 1;
      com(tiempo);
	}
	else if(a == 2)
	{
		tiempo = 0xC0 + b - 1;
		
        com(tiempo);
	}
    __delay_ms(4);
}

void lcd_init()
{
 
   __delay_ms(20);
  com(0x30);
	__delay_ms(10);
  com(0x30);
	__delay_us(110);
  com(0x30);
	__delay_ms(11);
 
  /////////////////////////////////////////////////////
  com(0x38);
  __delay_ms(4);
  com(0x08);
  __delay_ms(4);
  com(0x01);
  __delay_ms(4);
  com(0x06);
  __delay_ms(4);
  com(0x0C);
  __delay_ms(4);
}

void letra(char E)
{
   RS = 1;             // => RS = 1
   port(E);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
}



void word(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   letra(a[i]);
}

void Lcd_Shift_Right()
{
	com(0x01);
	com(0x0C);
}

void Lcd_Shift_Left()
{
	com(0x01);
	com(0x08);
}

void lee1(uint8_t coso){
    __delay_ms(1);
    
    Voldc= coso;
    voltaje=Voldc*5.0/255.0;

    ftoa2(voltaje,guardar,2);

    word(guardar);
    __delay_ms(5);
    
}
void lee2(uint8_t coso){
    __delay_ms(1);
    
    Voldc= coso;
    voltaje=Voldc*5.0/255.0;
     itoa(guardar,voltaje,10);
   

    word(guardar);
    
    __delay_ms(5);
    
    
}
void lee3(uint8_t coso2){
    __delay_ms(1);
    
    Voldc2= coso2;
    voltaje2=Voldc2*5.0/255.0;

    ftoa2(voltaje2,guardar2,2);

    word(guardar2);
    __delay_ms(5);
    
}
void lee4(uint8_t coso2){
    __delay_ms(1);
    
    Voldc2= coso2;
    voltaje2=Voldc2*5.0/255.0;
     itoa(guardar2,voltaje2,10);
   

    word(guardar2);
    
    __delay_ms(5);
    
    
}
void ADCread3(void){
    
   
    enviar= RCREG;
    voltaje=enviar*5.0/255.0;
     itoa(guardar,voltaje,10);
  

    word(guardar);
}
void ADCread4(){
    
   
   enviar= RCREG;
    voltaje=enviar*5.0/255.0;
 // itoa(buffer,voltaje,10);
    ftoa2(voltaje,guardar,2);

    word(guardar);
   }
void caracter (uint8_t info){
    EN =0;
    RS =1;
    PORTAbits.RA7 = (info & 0b10000000)>>7;
    PORTAbits.RA6 = (info & 0b01000000)>>6;
    PORTAbits.RA5 = (info & 0b00100000)>>5;
    PORTAbits.RA4 = (info & 0b00010000)>>4;
    PORTAbits.RA3 = (info & 0b00001000)>>3;
    PORTAbits.RA2 = (info & 0b00000100)>>2;
    PORTAbits.RA1 = (info & 0b00000010)>>1;
    PORTAbits.RA0 = (info & 0b00000001);
    __delay_ms(1);
    EN = 1;
    __delay_ms(3);
    EN = 0;
    __delay_ms(3);
    __delay_ms(3);
    
}

////Tomado de Geeks
void reverse(char* zpr, int len){
    int i = 0, j= len - 1, tiempo;
    while (i<j){
        tiempo = zpr[  i ];
        zpr[i] = zpr[j];
        zpr[j] = tiempo ;
        i++;
        j--;
    }
}
int Dtr (int y, char zpr[], int P){
    int i = 0;
    while(y){
        zpr[i++] = (y% 10) + '0';
        y =y/10;
    }
    while(i<P){
        zpr[i++] = '0';
        reverse(zpr,i);
        zpr[i] = '\0';
        return i;
    }
}


void ftoa2(float m, char* Q, int puntor){
    int coso = (int)m;
    float cosof = m - (float)coso;
    int i = Dtr(coso, Q, 0);
    if(puntor != 0){
        Q[i] = '.';
        cosof= cosof* pow(10,puntor);
        Dtr((int)cosof, Q +1,puntor);
                
    }
}
#endif	/* LCD_INSTRUCTIONS_H */
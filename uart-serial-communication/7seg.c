#include "7seg.h"
#include<stdint.h>
int valor ;
void loid(valor) {
    switch (valor){
    case 0:
        
        PORTD = 0b00111111;
        break;
    case 1:
         
        PORTD= 0b00000110;
        break;
    case 2:
        PORTD= 0b01011011;
        break;
    case 3:
        PORTD= 0b01001111;
        break;
    case 4:
        PORTD = 0b01100110;
        break;
    case 5:
        PORTD= 0b01101101;
        break;
    case 6:
        PORTD = 0b01111101;
        break;
    case 7:
        PORTD= 0b00000111;  
        break;
    case 8:
        PORTD = 0b01111111;
        break;
    case 9:
        PORTD= 0b01100111;
        break;        
    case 10:
        PORTD= 0b01110111;
        break;
    case 11:
        PORTD= 0b01111100;
        break;
    case 12:
        PORTD = 0b00111001;
        break;
    case 13:
        PORTD= 0b01011110;
        break;
    case 14:
        PORTD= 0b011111001;
        break;
    case 15:
        PORTD= 0b01110001;
        break;
        
    }
}  
       
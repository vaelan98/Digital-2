#include "ADC.h"
#include<stdint.h>
int valor2 ;
void loid2(valor2) {
    switch (valor2){
    case 1:
          ADCON0bits.CHS3=0;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=0;	//LECTURA DE AN0
	
    ADCON0bits.GO=1;
        break;
    case 2:
         
          ADCON0bits.CHS3=0;
    ADCON0bits.CHS2=1;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=1;	//LECTURA DE AN0
	
    ADCON0bits.GO=1;
        break;
     case 3:
          ADCON0bits.CHS3=1;
    ADCON0bits.CHS2=1;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=0;	//LECTURA DE AN0
	
    ADCON0bits.GO=1;
        break;
    case 4:
         ADCON0bits.CHS3=1;
    ADCON0bits.CHS2=1;
    ADCON0bits.CHS1=1;
    ADCON0bits.CHS0=1;	//LECTURA DE AN0
	
    ADCON0bits.GO=1;
        break;
    }}
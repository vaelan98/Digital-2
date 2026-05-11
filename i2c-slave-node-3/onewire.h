/* * File:   onewire.h */
#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#define onewire_PORT PORTAbits.RA0
#define onewire_Mask 0x01
#define onewire_TRIS TRISA

int     onewire_reset(void);
int     onewire_read(void);
void    onewire_write(int data);

int onewire_reset(void){
   int present = 0;
   onewire_TRIS = 0;        //Set onewire line to output
   onewire_PORT = 0;
   __delay_us(500);
   onewire_PORT = 1;
   onewire_TRIS = 1;         //Set onewire line to input
   __delay_us(100);
   present = onewire_PORT;               //Read onewire line
   __delay_us(400);
   return present;
}

int onewire_read(void){
   int k, data;
   for(k=0; k<8; ++k) {
      onewire_TRIS = 0;
      onewire_PORT = 0;
      __delay_us(2);
      onewire_PORT = 1;      
      onewire_TRIS = 1;
      __delay_us(8);
      data = data>>1;
      if(onewire_PORT == 1){data = (data|0x80);}
       else {data=(data&0x7F);}
       __delay_us(75);
   }
   return data;
}

void onewire_write(int data){ 
   int k;
   for(k=0; k<8; ++k) {
       onewire_TRIS = 0;
       onewire_PORT = 0;
       __delay_us(4);
       onewire_PORT = (data & 0x1);
       __delay_us(60); 
       onewire_TRIS = 1;
       __delay_us(4); 
       data = (data>>1);
   } 
} 
#endif   //onewire.h
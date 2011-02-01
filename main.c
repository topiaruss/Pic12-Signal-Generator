#include <htc.h>
#define _XTAL_FREQ 4000000 // needed for the delay macros

__CONFIG( FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & 
          BOREN_OFF & CP_OFF & CPD_OFF);

#define SINESLOTS 32
char const sine[SINESLOTS] = {
//0x37,0x37,0x37,0x37
 0x27,  0x12,  0x31,  0x14,  0x16,  0x34,  0x36,  0x37,
 0x37,  0x37,  0x36,  0x34,  0x16,  0x14,  0x31,  0x12,
 0x27,  0x24,  0x05,  0x22,  0x20,  0x02,  0x00,  0x00,
 0x00,  0x00,  0x00,  0x02,  0x20,  0x22,  0x05,  0x24
} ;

//////////////////////////////////////////////////////////////////////
void init_ports(void) {
   CMCON = 7;
   ANSEL=0;
   TRISIO = 0; // set as output
}

// resistor bit : port number
// 0 : GP0
// 1 : GP1
// 2 : GP5
// 3 : GP2
// 4 : GP4
// toggle bit : GP3

//////////////////////////////////////////////////////////////////////
// Start here
void main() {
   unsigned char idx;

   init_ports();
  
   idx = 0;
   while(1) { 
      GPIO = sine[idx];
      idx = ++idx & (SINESLOTS-1);
      __delay_ms(2);
      
  }
}
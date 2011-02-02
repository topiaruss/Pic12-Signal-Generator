#include <htc.h>
#define _XTAL_FREQ 4000000 // needed for the delay macros

__CONFIG( FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & 
          BOREN_OFF & CP_OFF & CPD_OFF);

#define SINESLOTS 64
char const sine[SINESLOTS] = {
 0x0f,  0x11,  0x12,  0x14,  0x15,  0x17,  0x18,  0x19,
 0x1a,  0x1c,  0x1c,  0x1d,  0x1e,  0x1e,  0x1f,  0x1f,
 0x1f,  0x1f,  0x1f,  0x1e,  0x1e,  0x1d,  0x1c,  0x1c,
 0x1a,  0x19,  0x18,  0x17,  0x15,  0x14,  0x12,  0x11,
 0x0f,  0x0e,  0x0c,  0x0b,  0x09,  0x08,  0x06,  0x05,
 0x04,  0x03,  0x02,  0x01,  0x00,  0x00,  0x00,  0x00,
 0x00,  0x00,  0x00,  0x00,  0x00,  0x01,  0x02,  0x03,
 0x04,  0x05,  0x06,  0x08,  0x09,  0x0b,  0x0c,  0x0e
};
char const map[SINESLOTS] = {
 0x00,  0x01,  0x02,  0x03,  0x04,  0x05,  0x06,  0x07,
 0x20,  0x21,  0x22,  0x23,  0x24,  0x25,  0x26,  0x27,
 0x10,  0x11,  0x12,  0x13,  0x14,  0x15,  0x16,  0x17,
 0x30,  0x31,  0x32,  0x33,  0x34,  0x35,  0x36,  0x37
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
   unsigned char nextval;

   init_ports();
  
   idx = 0;
   // Setup Timer
   T0CS = 0; // T0 clock select, in OPTION_REG, 0 means INTERNAL (CLKOUT)
   PSA = 0; // Prescaler assigned to Timer0 module
   PS0=0; PS1=1; PS2=0; // Prescaler 1:4
   T0IF = 0; // clear Timer 0 interrupt flag
   TMR0=100;
   
   nextval=map[sine[0]];
   while(1) {
	  // wait for timer flag
	  while(!T0IF){} // wait for timer to be up
	  
	  // put pre-computed value
	  GPIO = nextval;
	  
	  // set timer count, clear flag
      T0IF = 0; // clear T0 interrupt flag
      TMR0=250;
	  
	  // compute next value
      nextval = map[sine[idx]];
      idx = ++idx & (SINESLOTS-1);
      
  }
}
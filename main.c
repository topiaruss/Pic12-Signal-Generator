#include <htc.h>
#define _XTAL_FREQ 4000000 // needed for the delay macros

__CONFIG( FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & 
          BOREN_OFF & CP_OFF & CPD_OFF);
//0x31b4

#define SINESLOTS 64
char const sine[SINESLOTS] = {
 0x1f,  0x22,  0x25,  0x28,  0x2b,  0x2e,  0x31,  0x33,
 0x35,  0x38,  0x39,  0x3b,  0x3c,  0x3d,  0x3e,  0x3f,
 0x3f,  0x3f,  0x3e,  0x3d,  0x3c,  0x3b,  0x39,  0x38,
 0x35,  0x33,  0x31,  0x2e,  0x2b,  0x28,  0x25,  0x22,
 0x1f,  0x1c,  0x19,  0x16,  0x13,  0x10,  0x0d,  0x0b,
 0x08,  0x06,  0x04,  0x03,  0x01,  0x00,  0x00,  0x00,
 0x00,  0x00,  0x00,  0x00,  0x01,  0x03,  0x04,  0x06,
 0x08,  0x0b,  0x0d,  0x10,  0x13,  0x16,  0x19,  0x1c
};
char const map[] = {
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
   //unsigned int accu;

   init_ports();
  
   idx = 0;
   // Setup Timer
   T0CS = 0; // T0 clock select, in OPTION_REG, 0 means INTERNAL (CLKOUT)
   PSA = 0; // Prescaler assigned to Timer0 module
   PS0=0; PS1=1; PS2=0; // Prescaler 1:4
   TMR0=50;
   T0IF = 0; // clear Timer 0 interrupt flag
   
   nextval=map[sine[0]>>1];
   while(1) {
	  // wait for timer flag
	  while(!T0IF){} // wait for timer to roll-over
	  
	  // put pre-computed value
	  GPIO = nextval;
	  
	  // set timer count, clear flag
      TMR0=250;
      T0IF = 0; // clear T0 interrupt flag
	  
	  // compute next value
	  //accu = 0;
	  //accu += sine[idx];

      //nextval = map[accu >> 1]; 
      nextval = map[sine[idx]>>1]; 
      idx = ++idx & (SINESLOTS-1);
      
  }
}
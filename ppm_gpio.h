#ifndef PPM_H
#define PPM_H

#include "msp430f5529.h"
#include "settings.h"

unsigned int PPM[PPM_ARRAY_LEN];
unsigned int PPM_IND;

unsigned int rising_count;
unsigned int cctl;

int rising = 0;
int falling = 0;

int ppm_setup();
void PPM_ISR(void);


int ppm_setup(){

    // configure rising pin
    P1SEL &= ~BIT2; // pin 1.2 in GPIO mode
    P1DIR &= ~BIT2; // pin 1.2 in input mode
    P1IE  |=  BIT2; // pin 1.2 interrupt enabled
    P1IES &= ~BIT2; // pin 1.2 detects rising edge

    // configure falling pin
    P1SEL &= ~BIT3; // pin 1.3 in GPIO mode
    P1DIR &= ~BIT3; // pin 1.3 in input mode
    P1IE  |=  BIT3; // pin 1.3 interrupt enabled
    P1IES |=  BIT3; // pin 1.3 detects falling edge


    // configure timer
    TA0CCTL1 = CM_3 + CCIS_0 + SCS + CAP; // timer capture ctl, capture on both edges, uses CCI0A (P1.2), synchronize capture signal
    TA0CTL = TASSEL_1 + MC_2 + ID_0 + TACLR; // timer config, continuous mode, 32768Hz, reset timer

    PPM_IND = 0;
  
    return 0;

}

#pragma vector=unused_interrupts
__interrupt void PPM_ISR(void){
    if (P1IV & BIT2) { // if capture signal is currently high i.e. rising edge
        rising++;
        //rising_count = TA0CCR1;
    } else { // else, falling edge
        falling++;
        // PPM[PPM_IND] = TA0CCR1-rising_count; // compute difference and store
        //PPM_IND++; // increment index
        //PPM_IND = PPM_IND & PPM_ARRAY_MOD; // make circular
    }
}

#endif

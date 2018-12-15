#include "ppm.h"
#include "msp430f5529.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;
  
    ppm_setup();
    _BIS_SR(GIE); // enable interrupts
    while (1);
}

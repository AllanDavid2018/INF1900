/**
 * En se basant sur : http://www.groupes.polymtl.ca/inf1900/tp/tp6/,
 *
 * @author Allan BEDDOUK & David Dratwa
 * @created: 2018-10-13
 * @modified: 2018-10-16
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.h"

void ajustementPWM ( uint8_t ratio ) {
    

    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1A0) | _BV(WGM10);
    OCR1A = ratio;
    OCR1B = ratio;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS11);
    TCCR1C = 0;
}


int main()
{
    
    DDRD = 0x30;

    
    TCNT1 = 0;

    // We get the reader for the photoresistor
    can conv;

    for(;;)
    {
        // We get the 8 MSB from the 10 last bits, that will be or ratio x:255
        ajustementPWM(conv.lecture(0)>>2);
    }

    return 0; 
}

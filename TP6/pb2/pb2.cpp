/**
 * According to: http://www.groupes.polymtl.ca/inf1995/tp/tp7/,
 * 
 * TAN MACHINE!!! Check mes pipes!
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-27
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.h"

void ajustementPWM ( uint8_t ratio255 ) {
    
    // COM1A1 | COM1A0: Clear OC1A on Compare Match (Set output to low level)
    // COM1B1:          Clear OC1B on Compare Match (Set output to high level)
    // WGM10:           PWM, Phase Correct, 8-bit
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1A0) | _BV(WGM10);
    OCR1A = ratio255;
    OCR1B = ratio255;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS11);
}


/**
 * The main function. It does the logic.
 *
 * COMMENT BRANCHER LES FILS:
 * Del libre + sur PORTD<4> (OC1B)
 * Del libre - sur PORTD<5> (OC1A)
 * Output du bread board sur PORTA<0>
 * N'importe quel vcc et gnd de la carte sur le vcc et gnd du breadboard
 */
int main()
{
    initialisationUART();
    // Output PWN for the LED
    DDRD = 0x30;

    // We set the timer counter at 0 for the PWM
    TCNT1 = 0;

    // We get the reader for the photoresistor
    can conv;

    for(;;){
        // We get the 8 MSB from the 10 last bits, that will be or ratio x:255
        ajustementPWM(conv.lecture(0)>>2);
    }

    return 0; 
}

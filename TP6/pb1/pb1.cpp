/**
 * According to: http://www.groupes.polymtl.ca/inf1900/tp/tp6/
 *
 * @author Allan BEDDOUK & David DRATWA
 * @created: 2018-10-15
 * @modified: 
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/**
 * Light on the LED in green
 */
void allumerVert()
{
    PORTA = 0x2;
}

/**
 * Light on the LED in red
 */
void allumerRouge()
{
    PORTA = 0x1;
}

/**
 * Light off the LED
 */
void eteindre()
{
    PORTA = 0x0;
}

volatile uint8_t compteur;

void msleep(int ms) {
    for(int i = 0; i < ms; i++){
        _delay_loop_2(2000);
    }
}

ISR (TIMER1_COMPA_vect) {
    compteur++;
}

ISR (INT0_vect) {

    // Anti rebond
    _delay_ms(50);

    if (!(PIND & 0x04)) {
        partirMinuterie(781);
    }

    // Voir la note plus bas pour comprendre cette instruction et son role
    EIFR |= (1 << INTF0);
}

void partirMinuterie ( uint16_t duree ) {
    compteur = 0;
    // mode CTC du timer 1 avec horloge divisee par 1024
    // interruption après la duree specifiee
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10); // 00001101; WGM12 = CTC mode, 
    TIMSK1 |= _BV(OCIE1A); //00000010;
}

void arreterMinuterie() {
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
}

void initialisation ( void ) {

    // Désactive les interruptions
    cli ();

    DDRA = 0x03; // Output A
    DDRD = 0x00; // Input D

    // Permettre les interruptions externes
    EIMSK |= _BV(INT0);

    // Sensibiliser les interruptions externes
    EICRA |= _BV(ISC01); // Falling edge

    // Réactive les interruptions
    sei ();
}


/**
 * The main function. It does the logic.
 * 
 * COMMENT BRANCHER LES FILS:
 * Del libre + sur PORTA<0>
 * Del libre - sur PORTA<1>
 * Output du bread board sur PORTD<2>
 * N'importe quel vcc et gnd de la carte sur le vcc et gnd du breadboard
 */
int main()
{
    initialisation();

    for(;;) {

        do {

        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
        
        //(PIND & _BV(PORTD2)) == true if button is not pressed
        // We want to interate as long as the button is pressed, if it has been pressed (compteur > 1)
        } while (compteur <= 120 && (!(PIND & _BV(PORTD2)) || compteur == 0)); 
        arreterMinuterie();
        
        // Une interruption s'est produite. Arreter toute
        // forme d'interruption. Une seule reponse suffit.
        cli ();

        // Blink green for 1/2 seconds, at 2 Hz
        allumerVert();
        msleep(500);

        // Wait 2 seconds
        eteindre();
        msleep(2000);

        // Blink red (counter/2) times at 2 Hz
        for (uint8_t i = 0; i < compteur/2; i++) {
            allumerRouge();
            msleep(250);
            eteindre();
            msleep(250);
        }

        // Turn on green light for a second
        allumerRouge();
        msleep(1000);
        lightOff();
        compteur = 0;

    // Réactive les interruptions
        sei ();
    }

    return 0; 
}



/**
 * According to: http://www.groupes.polymtl.ca/inf1900/tp/tp6/
 *
 * @author Allan BEDDOUK & David DRATWA
 * @created: 2018-10-15
 * @modified: 
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void partirMinuterie ( uint16_t duree );


void allumerVert()
{
    PORTA = 0x2;
}


void allumerRouge()
{
    PORTA = 0x1;
}


void eteindre()
{
    PORTA = 0x0;
}

volatile uint8_t compteur;


ISR (TIMER1_COMPA_vect) {
    compteur+=10;
}

ISR ( INT0_vect) {

    // Anti rebond
    _delay_ms(50);
   

    if (!(PIND & 0x04)) 
        partirMinuterie(F_CPU/1024);
    

    EIFR |= (1 << INTF0);
}

void partirMinuterie ( uint16_t duree ) {
    compteur = 0;
    // mode CTC du timer 1 avec horloge divisee par 1024
    // interruption après la duree specifiee
      
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10); // 0b00001101; WGM12 = CTC mode, 
    TIMSK1 |= _BV(OCIE1A); //0b00000010;
}

void arreterMinuterie() {
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
}

void initialisation () {
// Désactive les interruptions
    cli();

  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree 

    // Permettre les interruptions externes
    
    EIMSK = _BV(INT0);

    // Interruptions externes sont actives sur n'importe quel rising edge
   
    EICRA =_BV(ISC00);

    // Reactive les interruptions
    sei();
}


int main()
{
	
    initialisation();
	while (compteur <= 120 && (!(PIND & _BV(PORTD2)) || compteur == 0)); 
    arreterMinuterie();
        
	// Une interruption s'est produite. Arreter toute
	// forme d'interruption. Une seule reponse suffit.
	cli ();

	// Allume vert pour 1/2 seconde
	allumerVert();
	_delay_ms(500);

	// pause de 2 secondes
	eteindre();
	_delay_ms(2000);

	// Allume rouge (compteur/2) fois
	for (uint8_t i = 0; i < compteur/2; i++) 
	{
		allumerRouge();
		_delay_ms(250);
		eteindre();
		_delay_ms(250);
	}

	// Turn on green light for a second
	allumerVert();
	_delay_ms(1000);
	eteindre();
	compteur = 0;

	// Réactive les interruptions
	sei ();
    

    return 0; 
}



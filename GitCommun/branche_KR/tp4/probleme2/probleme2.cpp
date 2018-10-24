/* *********************************
 * Nom: 		probleme2.cpp
 * Auteurs : 	Kevin Ciliento & Roman Zhornytskiy
 * Date :		04/09/2018
 * Mise a jour: 07/09/2018
 * Description: La DEL change de couleur en fonction a chaque fois que l'utilisateur appuit sur le boutton-poussoir.
 * Version: 	1.1 
 * Description de l'update // changement de la date 
 **********************************/
// documentation: http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>: Interrupts

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR ( TIMER1_COMPA_vect ) {//Timer/Counter1 Compare Match A

minuterieExpiree = 1;

}

ISR ( INT0_vect ) {

boutonPoussoir = 1;

// anti-rebond
_delay_ms(30); 
}

void initialisation ( void ) {

cli ();

  DDRB = 0xff; // PORT B est en mode sortie
  DDRD = 0x00; // PORT D est en mode ENTREE

EIMSK |= (1 << INT0) ;

EICRA |=  (1 << ISC01) | (1 << ISC00);
 /*
0 0 The low level of INTn generates an interrupt request
0 1 Any edge genere asynchronously interrupt
1 0 The falling edge of INTn generates asynchronously an interrupt request
1 1 The rising edge of INTn generates asynchronously an interrupt request
*/

sei ();

}


void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée

TCNT1 = 0;// on commence de compter à zero. p.135

OCR1A = duree;

TCCR1A |= (1 << COM1A0) ; //option de comparer //Compare Match //on change le "n" pour 1. 
//Toggle OCnA/OCnB on Compare Match. p128


TCCR1B |= (1<< CS12) | (0<< CS11) | (1<< CS10); //on dit au clkI/O /1024  //on change le "n" pour 1
// p.130
TCCR1C = 0;

TIMSK1 |= 1<< OCIE1A ; //option pour compare enable. p.134

}


					
int main()
{
	const uint8_t VERT = 0b10;
	const uint8_t ROUGE = 0b01;
	const uint8_t INCOLORE =0b00;
	initialisation();
	_delay_ms(3000); //3 seconds de delai
	PORTB = ROUGE;
	_delay_ms(100);
	PORTB = INCOLORE;
	partirMinuterie (7812); 
	
	do {

// attendre qu'une des deux variables soit modifiée
// par une ou l'autre des interruptions.

} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

// Une interruption s'est produite. Arrêter toute
// forme d'interruption. Une seule réponse suffit.

cli ();

// Verifier la réponse
if(minuterieExpiree == 1){
	PORTB = ROUGE;
	}
if(boutonPoussoir == 1){
	PORTB = VERT;
	}


	
  return 0; 
}

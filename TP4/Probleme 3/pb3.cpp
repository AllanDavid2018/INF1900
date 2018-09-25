/*
 * Nom: Probleme 1- TP4
*/
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

#include <avr/io.h> 
   




void ajustementPWM ( uint8_t ratio) {

// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

// page 177 de la description technique du ATmega324PA)

OCR1A = ratio;

OCR1B = ratio ;


// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1A = (1<<COM1A1) | (1 << COM1B1) | (1<<WGM10); //0b11110001 ;

TCCR1B = (1<<CS11);

TCCR1C = 0;

}




int main()


{
	
	DDRD=0xff;
	TCNT1=0;
	
	ajustementPWM (0);
	_delay_ms(2000);
	ajustementPWM (64);
	_delay_ms(2000);
	ajustementPWM (128);
	_delay_ms(2000);
	ajustementPWM (191);
	_delay_ms(2000);
	ajustementPWM (255);
	_delay_ms(2000);
	

  return 0; 
}

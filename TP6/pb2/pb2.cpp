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

void allumerRouge() {
	 PORTD = 0b10;
}
void allumerVert() { 
	PORTD = 0b01;
}
void allumerAmbre(){ 
	for (;;){
		PORTD = 0x01;
			_delay_ms (1);
		PORTD= 0b10; 
		_delay_ms (1); 
		
		if (PIND == 0b00) 
			break; 
		}
}

void initialisation () {
// Désactive les interruptions
  DDRA = 0x00; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode entree 
  TCNT1 = 0;
}


int main()
{
    
   initialisation();
   can conv;
   allumerRouge();
   _delay_ms(1000); 

	for(;;)
   {
   
		uint8_t valeur = conv.lecture(0)>>2;
		/*
		if(valeur < 85)
			allumerVert();
		else if(valeur>=85 && valeur<=170)
			allumerAmbre();	
			
		else if(valeur>170)
			allumerRouge();
		*/
		if (valeur==0)
			allumerVert(); 
	
		
   }

    return 0; 
}

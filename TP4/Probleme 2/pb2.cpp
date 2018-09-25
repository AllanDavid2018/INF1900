/*
 * Nom: Probleme 1- TP4
*/
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

#include <avr/io.h> 
   

void allumerRouge() {
	 PORTA = 0b10;
}
void allumerVert() { 
	PORTA = 0b01;
}
void allumerAmbre(){ 
	for (;;){
		PORTA = 0x01;
			_delay_ms (1);
		PORTA= 0b10; 
		_delay_ms (1); 
		
		if (PIND == 0b00) 
			break; 
		}
}


void eteindre() { 
	PORTA = 0b00;
}


enum Etats {
	rougeA,
	ambre, 
	vertA,
	rougeB,  
	eteint, 
	vertB,
};

volatile Etats etat =rougeA;

volatile uint8_t minuterieExpiree;

volatile uint8_t boutonPoussoir; 


ISR ( TIMER1_COMPA_vect) {

minuterieExpiree = 1;

}


ISR ( INT0_vect) {

boutonPoussoir = 1;

// anti-rebond

_delay_ms (30); 

}

void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024

// interruption après la durée spécifiée

TCNT1 |= 0b0 ;

OCR1A = duree;

TCCR1A |= 0b00000001 ;

TCCR1B |= 0b00000101;

TCCR1C |= 0b0;

TIMSK1 |= 0b00000010;

}


void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontroleur n'est pas prêt...

	cli ();


// configurer et choisir les ports pour les entrées

// et les sorties. DDRx... Initialisez bien vos variables



  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree 

// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

	EIMSK |= (1 << INT0) ;


// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA

	EICRA |= 00000001;

// sei permet de recevoir à nouveau des interruptions.



	sei ();

}






int main()


{
	
	
	initialisation(); 
	
	_delay_ms (3000);
	allumerRouge(); 
	_delay_ms(1000);
	eteindre(); 
	partirMinuterie(F_CPU/1024);
	
	do {

	// attendre qu'une des deux variables soit modifiée

	// par une ou l'autre des interruptions.

	} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );


	// Une interruption s'est produite. Arrêter toute

	// forme d'interruption. Une seule réponse suffit.

	cli ();

	// Verifier la réponse

	if (minuterieExpiree) 
		allumerRouge(); 
	else allumerVert();
	for(;;);
	
  return 0; 
}

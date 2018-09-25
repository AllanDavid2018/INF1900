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

// placer le bon type de signal d'interruption

// à prendre en charge en argument

ISR ( INT0_vect) {

// laisser un delai avant de confirmer la réponse du
	uint8_t bouton = PIND & 0x04; 

// bouton-poussoir: environ 30 ms (anti-rebond)
	_delay_ms (30); 

// se souvenir ici si le bouton est pressé ou relâché
	 if(bouton == (PIND & 0x04)){ 
		 if (etat == vertB)
			etat = rougeA; 
		else etat = Etats ((int) etat+1); 
	 }
	

// Voir la note plus bas pour comprendre cette instruction et son rôle

	EIFR |= (1 << INTF0) ;

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
	for(;;){
		switch (etat){
		case rougeA : 
				allumerRouge(); 
				break;
		
		case ambre : 
				PORTA = 0x01;
				_delay_ms (1);
				PORTA= 0b10; 
				_delay_ms (1); 
				break;
				  
		case vertA :  
				allumerVert();
				break;
		case rougeB : 
				allumerRouge();
				break;
		case eteint : 
				eteindre();
				break;
		case vertB : 
				allumerVert();
				break;    
			}
		
	}
  return 0; 
}

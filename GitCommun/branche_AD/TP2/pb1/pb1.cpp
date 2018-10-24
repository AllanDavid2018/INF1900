/*
 * Nom: Probleme 1- TP2
 * 
 * Tableau des Etats
 * 
  * ETAT PRESENT | D2 | ETAT SUIVANT | SORTIE Z
 * INIT			| 0  | INIT			| 0
 * INIT			| 1  | E1			| 0
 * E1			| 0  | E1			| 0
 * E1			| 1  | E2			| 0
 * E2			| 0  | E2			| 0
 * E2			| 1  | E3			| 0
 * E3			| 0  | E3			| 0 
 * E3			| 1  | E4			| 0
 * E4			| 0  | E4			| 0
 * E4			| 1  | E5			| 0
 * E5			| X  | INIT			| 1
 */
#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h> 
      
/*

*/

void allumerRouge(uint8_t tempsSeconde) {
	 PORTA = 0b10;
	 for (uint8_t i = 0; i < tempsSeconde; i++) 
	  _delay_ms (1000);
	  PORTA = 0b00;
  
}

void eteindre() { 
	PORTA = 0b00;
}

bool estAppuye()
{
	if(PIND & 0x04)
		_delay_ms (40);
	return PIND & 0x04;	
}


int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree 

	bool estFerme=1;
	uint8_t compteur = 0; 
	for(;;)
	{
		if(estAppuye() && estFerme){
			compteur++; 
			estFerme=0;
		}
		
		switch (compteur) { 
		case 0 : 
			eteindre();
			break; 
		case 1 : 
			eteindre();
			break; 
		case 2 : 
			eteindre();
			break; 
		case 3 : 
			eteindre();
			break;  
		case 4 : 
			eteindre();
			break;  
		case 5 : 
			allumerRouge(1); 
			compteur = 0; 
			break; 
			
			
		}
	
		if (!(PIND & 0x04))
			estFerme=1;
	}
	
  return 0; 
}

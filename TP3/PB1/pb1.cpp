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

void allumerRouge() {
	 PORTA = 0b10;
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

double tempsDelay = 1/3000; 

void delay(uint16_t temps)
{
	for (uint16_t j = 0; j < temps; j++){
		_delay_us (0.3);
	}
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree 

	bool estFerme=1;
	
	for(;;)
	{
		
	
		if(estAppuye() && estFerme ){
			for(int i = 0; i < 2000; i++)
			{
				allumerRouge(); 
				delay(2000-i);
				
				eteindre(); 
				for (int j = 0; j < i; j++) {
					_delay_us (0.3); 
				}
			}
			estFerme=0;
		}
		
	
		if (!(PIND & 0x04))
			estFerme=1;
			
		eteindre(); 
	}
	
  return 0; 
}

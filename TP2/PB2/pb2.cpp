/*
 * Nom: Probleme 1- TP2
 * 
 * Tableau des Etats
 * 
 * ETAT PRESENT | D2 | ETAT SUIVANT | SORTIE Z
 * INIT			| 0  | INIT			| rouge
 * INIT			| 1  | EA1			| Ambre
 * EA1			| 1  | EA1			| Ambre
 * EA1			| 0  | EV2			| Vert
 * EV2			| 0  | EV2			| Vert
 * EV2			| 1  | ER3			| Rouge
 * ER3			| 1  | ER3			| Rouge
 * ER3			| 0  | EE4			| Eteint
 * EE4			| 0  | EE4			| Eteint
 * EE4			| 1  | EV5			| Vert
 * EV5			| 1  | EV5			| Vert
 * EV5			| 0  | INIT			| Rouge
 */
#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h> 
      
void allumerVert(){
	PORTA = 0b01;

}

void allumerRouge(){
	PORTA = 0b10;

}

void eteindre() { 
	PORTA = 0b00;
}

void allumerAmbre() {
	for (;;){
		PORTA = 0x01;
			_delay_ms (1);
		PORTA= 0b10; 
		_delay_ms (1); 
		if (PIND == 0b00) 
			break; 
		}
} 

void allumerRouge(uint8_t tempsSeconde) {
	 PORTA = 0b10;
	 for (uint8_t i = 0; i < tempsSeconde; i++) 
	  _delay_ms (1000);
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


	uint8_t EtatCouleur=1;
	bool estFerme=1;
	
	for(;;)
	{
		if(estAppuye() && estFerme){
			EtatCouleur++;
			estFerme=0;
}
			
		switch (EtatCouleur){
		case 1 : 
				allumerRouge(); 
				break;
		
		case 2 : 
				allumerAmbre();
				break;
				  
		case 3 :  
				allumerVert();
				break;
		case 4 : 
				allumerRouge();
				break;
		case 5 : 
				eteindre();
				break;
		case 6 : 
				allumerVert();
				break;    
		case 7 : 
				EtatCouleur=1;
				break;

		}
		if (!(estAppuye()) && !estFerme){
			estFerme=1;
			EtatCouleur++;
		}
	
	}
	return 0; 
}

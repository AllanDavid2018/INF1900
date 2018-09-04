/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */
#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h> 

 

void allumerAmbre (int tempsSeconde) {
	 for (int i = 0; i < tempsSeconde * 1000; i++){
		PORTA = 0x01;
			_delay_ms (1);
		PORTA= 0b10; 
		_delay_ms (1); 
	  
		}
		PORTA = 0b00;
}
void allumerRouge(uint8_t tempsSeconde) {
	 PORTA = 0b10;
	 for (uint8_t i = 0; i < tempsSeconde; i++) 
	  _delay_ms (1000);
	  PORTA = 0b00;
  
}


void allumerVert(uint8_t tempsSeconde) {
	 PORTA = 0b01;
	for (uint8_t i = 0; i < tempsSeconde; i++) 
	  _delay_ms (1000);
	 PORTA = 0b00;
}

void allumerVert(){
	PORTA = 0b01;

}

void allumerRouge(){
	PORTA = 0b10;

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


void eteindre() { 
	PORTA = 0b00;
}

void estEteint(){
	for(;;)
	if(!(PIND & 0x04))
		break;
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
      
/*
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
      
    
      
      
      
      
      
      
      
      
      /*    
    for (;;){

		if ( PIND & 0x04 ) 
			allumerAmbre();
		else eteindre(); 
			
	}
          
                       
  for(;;)  // boucle sans fin
  {
	
		
	
	  allumerRouge(1);
	  allumerVert(1);
	  allumerAmbre(1);
	  	
    
  }
  
	
	uint8_t EtatCouleur=0;
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
				  allumerVert();
				  break;
				  
		case 3 : allumerVert();
				 _delay_ms (1);
				 allumerRouge();
				 _delay_ms (1);
				  break;
				   
		case 4 : 
					EtatCouleur=1;
					break;

		}
if (!(PIND & 0x04))
	estFerme=1;
	}
	*/
  
  return 0; 
}

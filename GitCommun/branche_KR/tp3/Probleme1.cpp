// Partie button
/*
 * Nom: Interrupeur

 * Description: 
 * Version: 1.0
 */

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

void attendre(uint16_t nombreDeFois){
	for(uint16_t i=0; i<nombreDeFois; i++){
		_delay_us(10);
		}
}

void lecture()
{
	const uint8_t VERT = 0b10;
	const uint8_t ROUGE = 0b01;
	const uint8_t INCOLORE =0b00;
	
		for(;;){
			uint16_t tempsDAttente1=500;

			for(uint16_t i=0; i<tempsDAttente1; i++ ){
				PORTB=ROUGE;
				attendre(tempsDAttente1-i);
				
				PORTB=INCOLORE;
				attendre(i);
			}
			
			for(uint16_t i=0; i<tempsDAttente1; i++ ){
				PORTB=VERT;
				attendre(tempsDAttente1-i);
				
				PORTB=INCOLORE;
				attendre(i);
			}
		}	
}
					
int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode sortie

	lecture();
	
  return 0; 
}

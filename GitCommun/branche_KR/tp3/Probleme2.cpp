// Partie button
/*
 * Nom: Interrupeur

 * Description: 
 * Version: 1.0
 */

///////////prendre fils orange-jaune et mettre le cote orange vers 
///////////l'exterrieur (la roue droite) et l'autre orange vers le haut. 
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

void attendre(uint16_t nombreDeFois){
	for(uint16_t i=0; i<nombreDeFois; i++){
		_delay_ms(1);
		}
}
void attendreMicro(uint16_t nombreDeFois){
	for(uint16_t i=0; i<nombreDeFois; i++){
		_delay_us(10);
		}
}

void lecture()
{
	const uint8_t ARRIERE = 0b10;
	const uint8_t AVANT   = 0b11;
	const uint8_t ARRET   = 0b01;

	
		for(;;){
			
				PORTB=00; // 0% pour deux secondes
				_delay_ms(2000);
	
			uint16_t tempsDAttente1=120;

			for(uint16_t i=0; i<tempsDAttente1; i++ ){ //25% pour deux secondes
				PORTB=0b11;
				attendre(4);
				
				PORTB=0b00;
				attendre(12);
			}
			
			tempsDAttente1=120;
				for(uint16_t i=0; i<tempsDAttente1; i++ ){ //50% pour deux secondes
				PORTB=0b11;
				attendre(8);
				
				PORTB=0b00;
				attendre(8);
			}
				tempsDAttente1=120;
				for(uint16_t i=0; i<tempsDAttente1; i++ ){ //75% pour deux secondes
				PORTB=0b11;
				attendre(12);
				
				PORTB=0b00;
				attendre(4);
			}
				tempsDAttente1=120;
				for(uint16_t i=0; i<tempsDAttente1; i++ ){ //100% pour deux secondes
				PORTB=0b11;
				attendre(16);
				
				PORTB=0b00;
				attendre(0);
				
			}
			///////////partie 400 hz
				PORTB=00; // 0% pour deux secondes
				_delay_ms(2000);
	
			tempsDAttente1=800;

			for(uint16_t i=0; i<tempsDAttente1; i++ ){ //25% pour deux secondes
				PORTB=0b11;
				attendreMicro(63);
				
				PORTB=0b00;
				attendreMicro(188);
			}
			
			tempsDAttente1=800;
				for(uint16_t i=0; i<tempsDAttente1; i++ ){ //50% pour deux secondes
				PORTB=0b11;
				attendreMicro(125);
				
				PORTB=0b00;
				attendreMicro(125);
			}
				tempsDAttente1=800;
				for(uint16_t i=0; i<tempsDAttente1; i++ ){ //75% pour deux secondes
				PORTB=0b11;
				attendreMicro(188);
				
				PORTB=0b00;
				attendreMicro(63);
			}
				tempsDAttente1=800;
				for(uint16_t i=0; i<tempsDAttente1; i++ ){ //100% pour deux secondes
				PORTB=0b11;
				attendreMicro(250);
				
				PORTB=0b00;
				attendreMicro(0);
				
			}
		}
}
					
int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree

	lecture();
	
  return 0; 
}

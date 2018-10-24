// Partie button
/*
 * Nom: Interrupeur

 * Description: 
 * Version: 1.0
 */


#include <avr/io.h> 

#define F_CPU 8000000
#include <util/delay.h>

void Lecture()
{
	
			for(;;){
				PORTB=0b11;
			if ( PIND & 0x04 )
				{
					_delay_ms (10.0);
					if ( PIND & 0x04 )
					{ while(PIND & 0x04 ){
						PORTB=0b01;
						_delay_ms (10.0);
						PORTB=0b10;
						_delay_ms (10.0);
						}
					}
				}
			}	
}
					
int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode sortie

	Lecture();
	
  return 0; 
}

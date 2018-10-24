/*
 * Nom: test.cpp
 * Version: 0.01
 */


#include <avr/io.h> 

#define F_CPU 8000000
#include <util/delay.h>


int main()
{

  DDRB = 0xff; // PORT B est en mode sortie

  //unsigned long compteur=0; // le compteur est initialise a 0.
                            // c'est un compteur de 32 bits


 for(;;)  // boucle sans fin
  {
    //compteur++;  
     // _delay_ms (900.0);
    PORTB=0b01;              
     _delay_ms (900.0);
     PORTB=0b10; 
       _delay_ms (900.0);
       for(int i=0;i<100;i++) {
			PORTB=0b01;
			_delay_ms (10.0);
			PORTB=0b10;
			_delay_ms (10.0);
		}
     
     
  
  }
  return 0; 
} 

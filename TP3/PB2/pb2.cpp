
#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h> 
      


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

                PORTA = 0b10;
                PORTB = 0b01;
		if(estAppuye() && estFerme ){
                        PORTB = 0b01;

		}
		
	
		if (!(PIND & 0x04))
			estFerme=1;
			
		eteindre(); 
	}
	
  return 0; 
}

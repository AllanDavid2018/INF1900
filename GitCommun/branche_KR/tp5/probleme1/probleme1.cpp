#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#define IN 0x00		//Met le port en entree
#define OUT 0xFF

#include "memoire_24.cpp"

int main() {
	
	DDRA=DDRD=DDRC=IN;
	DDRB=OUT;
	Memoire24CXXX mem;
	uint8_t chaine[45]="*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

	mem.ecriture(0x00, chaine, 45); 
	uint8_t lire[45]; 
	mem.lecture(0x00, lire, 45); 
	
	_delay_ms(10);

	bool bon=1;
	
	for(int i=0; i<45;i++)
	{
		bloc1[i] == lire[i] ? : bon=0;
	}
	
	bon==1 ? PORTB = 0x02 : PORTB =0x01;
		
		
	return 0;
}

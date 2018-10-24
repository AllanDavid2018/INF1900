#include <avr/io.h>

void initialisationUART(void) {

	// 2400 bauds. Nous vous donnons la valeur des deux

	// premier registres pour vous �viter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;


	// r�ception et tranmission 
	UCSR0A = 0; /*tous les bits � 0, on ne veut pas de flag interupt docAtmel p.185-186*/

	UCSR0B |= _BV(RXEN0)	/*enables the USART0 Receiver*/
		| _BV(TXEN0)		/*enables the USART0 Transmitter*/
		/*| _BV(UCSZn2)*/;	/*UCSZn2 bits combined with the UCSZn1:0 bit in UCSRnC | Laisser � 0 pour 8 bits*/

	// Format des trames: 8 bits, 1 stop bits, none parity asynchrone

	//UCSR0C |=  /*|_BV(UPM0)*/; /*Parity Mode d�comment� pour enable | Configuration de base est 8N1*/
}


/*Code venant du docAtmel p.174*/
void transmissionUART(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0))) /*Compare le registre courant � sa valeur s'il serait vide*/
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main() {
	
	initialisationUART();
	
	uint8_t mots[] = "Le robot en INF1900\n";

	/*Permet la concat�nation des char dans le buffer d'UART0*/

	for (uint8_t i = 0; i < sizeof(mots)/sizeof(uint8_t); i++) 
		transmissionUART(mots[i]);
		
	
	return 0;
}





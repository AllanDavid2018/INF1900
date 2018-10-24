
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

void ajustementPWM ( uint8_t duree ) {

// mise à un des sorties OC1A et OC1B sur comparaison
// réussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
// page 177 de la description technique du ATmega324PA)


OCR1A = duree ;

OCR1B = duree ;


// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1A |= 1<<COM1A1 | 1<<COM1B1 | 1<<WGM10; //p.129 et p.130 
//(en mode PWM 8 bits, phase correcte) TRES IMPORTANT!!!!!!!!!!!

TCCR1B |= 0<<CS12 | 1<<CS11 | 0<<CS10 ; // Clock Select bit description on le met à
//clkI/O/8 (From prescaler) dans l'énoncé ca dit "division d'horloge par 8 - implique une frequence de PWM fixe"

TCCR1C = 0;

}
					
int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff & ~(1<<2); // PORT D tous les bits sont en sortie sauf le 3e bit.
  PORTD = 1<<7; // on fait avancer les roues vers l'avant
	
	uint8_t VingtCinq = 64; //65536*0.25
	uint8_t Cinquante = 128; //65535*0.50
	uint8_t SoixanteQuinze = 192; //65536*0.75
	uint8_t Cent = 255;
	
	ajustementPWM(VingtCinq); // 25% pour le rapport a/b pour le PWM
	_delay_ms(2000);
	ajustementPWM(Cinquante); // 50% pour le rapport a/b pour le PWM
	_delay_ms(2000);
	ajustementPWM(SoixanteQuinze);
	_delay_ms(2000);
	ajustementPWM(Cent);
	_delay_ms(2000);
	
	
	
  return 0; 
}



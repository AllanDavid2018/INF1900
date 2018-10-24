/****************************************************************************
* Fichier:		probleme2.cpp
* Auteurs:		Kevin Ciliento et Roman Zhornytskiy
* Date:			07/10/2018
* Description:	Faire un robot pouvant se faire bronzer...
Si la lumière est basse (en cachant la photorésistance), la DEL prendra la couleur verte.
Si la lumière est à un bon niveau (lumière ambiante), la DEL tournera à l'ambré.
Si la lumière est trop forte (photorésistance sous une lampe de poche), la DEL devient rouge.
****************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include"can.cpp"
#include <avr/interrupt.h>: Interrupts

using namespace std;

#define IN 0x00		//Met le port en entree
#define OUT 0xFF	//Met le port en sortie
#define EVER (;;)	//Parametres boucle infinie

/* **********************************
 * Fonction:		initialisation()
 * Description:		ajuste la direction des ports
 * Parametre:		aucun
 * Retour :			aucun
 ************************************/
void initialisation() {
	cli();		// Interrupt disabled

	/*PORT*/
	DDRB = DDRC = DDRD = OUT;
	DDRA = IN;		//On utilise la conversion donc PORTA[7:0] IN
	
	sei();		//interrupt re-enabled
}

/* **********************************
 * Fonction:		readLight()
 * Description:		lit la valeur convertie pas la classe "can" et retourne une valeur sur 8 bits.
 * Parametre:		aucun
 * Retour :			uint8_t : light8b
 ************************************/
uint8_t readLight() 
{
	uint16_t light16b;
	can Can; //appel du constructeur par deffaut permettant l'initlisation
	light16b = Can.lecture(0x00);//16 bits sur position 0 sur le PORTA
	uint8_t light8b;	//plus petit type de variable
	light8b = (light16b >> 2); //on tasse de 2 vers la droite pour effacer les deux derniers bits qui ne sont pas importants.
	light8b = static_cast<uint8_t>((light16b)); //on garde seulement les 8 bits les moins significatifs.
	return light8b;
}

/* **********************************
 * Fonction:		setLED()
 * Description:		Change la LED en fonction de la valeur lue (par la fonction readLight())
 * Parametre:		aucun
 * Retour :			aucun
 ************************************/
void setLED() {
	uint8_t lightVal = readLight(); //Lit la valeur courrante de la cellule photovoltaique et retourne une valeur sur 8bits
	enum etat{
	mod = 115, //255*0.45
	max = 217}; //255*0.85 

	//Couleurs
	static const uint8_t ROUGE = 0x01,VERT = 0x02;

	if (lightVal < mod) {	//Faible de lumiere
		PORTB = VERT;
	}

	else if (lightVal >= mod && lightVal < max) //Bonne lumiere
	{	
		while(lightVal >= mod && lightVal < max) //Couleur ambree
		{
			_delay_ms(10.0);
			PORTB = VERT;
			_delay_ms(10.0);
			PORTB = ROUGE;
			lightVal = readLight();	//verifie la valeur de la cellule photovoltaique
		}
	}

	else if (lightVal >= max)	//Trop de lumiere
		PORTB = ROUGE;
}

int main(){
	initialisation();	
	for EVER {
		setLED();
	}
	return 0;
}
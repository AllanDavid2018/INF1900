/****************************************************************************
* Fichier:		probleme1Scrut.cpp
* Auteurs:		Kevin Ciliento et Roman Zhornytskiy
* Date:			04/10/2018
* Description:	Ce fichier permet de changer la couleur d'une DEL 
				à l'aide d'un bouton poussoir NO. Méthode de montage  
				disponible @ http://www.groupes.polymtl.ca/inf1900/tp/tp6/
****************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

using namespace std;

#define IN 0x00		//Met le port en entrée
#define OUT 0xFF	//Met le port en sortie
#define EVER (;;)	//Parametres boucle infinie
#define PUSHED !(PIND & 0x04) //Bouton poussoir pressé


/****************************************************************************
* Fonction:		initialisation()
* Description:	ajuste la direction des ports
* Parametre:	aucun
* Retour :		aucun
****************************************************************************/
void initialisation(){
	/*PORT*/
  DDRA = DDRB = DDRC = OUT;
  DDRD = IN; 
}

/****************************************************************************
 * Fonction:		antiRebond()
 * Description:		Verifie si le signal entree est le meme apres 10ms
 * Parametre:		aucun
 * Retour :			retourne une valeur booleenne true/false
 ****************************************************************************/
bool antiRebond()
{
	if(PUSHED) //Si bouton poussoir activé
	{ 
		_delay_ms (10.0);
			if (PUSHED)	//anti rebond
				return true;
	}
	return false;
}

int main() {
	initialisation();

	/*COULEURS_DEL*/
	static const uint8_t
	INCOLORE =	0x00,
	ROUGE	 =	0x01,
	VERT	 =	0x02;

	for EVER{

		if(antiRebond()){
			unsigned int compteur = 0;
			while(PUSHED){
				_delay_ms(100.0); //incrementation a 10Hz
				compteur++;
				if(compteur == 120){ //break aussi si PUSHED = false
					break;}
			}

			PORTB = VERT;		
			_delay_ms(500.0);	//clignote pendant 1/2 seconde
			PORTB = INCOLORE;	
			_delay_ms(2000.0); //rien pendant 2 secondes
			PORTB = ROUGE;
			compteur = compteur/2;

			for(unsigned int i = 0; i<compteur; i++){	//clignote a 2Hz en fonction 
				PORTB = ROUGE;						//de la valeur du compteur
				_delay_ms(250.0);
				PORTB = INCOLORE;
				_delay_ms(250.0);
			}
			PORTB = VERT;
			_delay_ms(1000.0);
			PORTB = INCOLORE;	//Retour à l'état initial
		}
	}
	return 0;
}

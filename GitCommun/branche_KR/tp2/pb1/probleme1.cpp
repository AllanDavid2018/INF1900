/* *********************************
 * Nom: 		probleme1.cpp
 * Auteurs : 	Kevin Ciliento & Roman Zhornytskiy
 * Date :		31/08/2018
 * Mise a jour: 07/09/2018
 * Description: Change l'etat de la DEL en fonction du compteur.
 * Le compteur incremente a l'aide du bouton poussoir jusqu'a 5.
 * La DEL adopte une couleur rouge lorsque le bouton poussoir est 
 * utilise 5 fois. 
 * Version: 	1.01
 **********************************/
 
  /*		Etat	 	A	Etat suivant	Sortie
	*		init		0	init			incolore	
	*		init		1	E1				incolore		
	*		E1			0	E1				incolore	
	*		E1			1	E2				incolore	
	*		E2			0	E2				incolore	
	*		E2			1	E3				incolore	
	*		E3			0	E3				incolore	
	*		E3			1	E4				incolore	
	*		E4			0	E4				incolore	
	*		E4			1	fin				incolore	
	*		fin			X	init			rouge 							
  */	

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

/* **********************************
 * Fonction:		ChangementdEtatProbleme1
 * Description:		Change l'etat en fonction du compteur. Le compteur
 * incremente a l'aide du bouton poussoir jusqu'a 5.
 * Parametre:		- (uint8_t) compteur : compte le nombre de fois que 
 * le boutton a ete pousse (IN)
 * Retour :			aucun
 ************************************/
void ChangementdEtatProbleme1(uint8_t compteur)
{
	enum Etat{init, fin = 5};
	
	for(;;){
		PORTB=0b11; // DEL incolore
		if ( PIND & 0x04 ) // anti-rebond
		{
			_delay_ms (10.0); 
 			if ( PIND & 0x04 )
			{
				while(PIND & 0x04){}; // Sucurite pour une incrementation unique
				compteur++; 
			}	
		}
		switch (compteur) 
		{
			case init: 
			{ 
				PORTB=0b11;break;
			} 
				
			case fin:
			{ 
				PORTB=0b01;
				_delay_ms (1000.0);
				compteur=0; break;
			} 
		}
	}	
}
int main()
{
	DDRB = 0xff; // PORT B est en mode sortie
	DDRD = 0x00; // PORT D est en mode ENTREE
	
	uint8_t compteur = 0; 
	ChangementdEtatProbleme1(compteur);
	
	return 0; 
}

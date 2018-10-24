/* *********************************
 * Nom: 		probleme2.cpp
 * Auteurs : 	Kevin Ciliento & Roman Zhornytskiy
 * Date :		04/09/2018
 * Mise a jour: 07/09/2018
 * Description: La DEL change de couleur en fonction a chaque fois que l'utilisateur appuit sur le boutton-poussoir.
 * Version: 	1.1 
 * Description de l'update // changement de la date 
 **********************************/
 
 ///////// fil orange-jaune, cote orange vers l'arriere
 
 /*		Etat	 	A	Etat suivant	Sortie
  *		init	 	0		init		rouge			
  * 	init	 	1		ambre		ambre			
  * 	ambre	 	0		vert		vert			
  * 	ambre	 	1		ambre		ambre			
  * 	vert	 	0		vert 		vert 			
  * 	vert	 	1		rouge		rouge			
  * 	rouge	 	0		incolore	incolore			
  * 	rouge	 	1		rouge		rouge			
  * 	incolore 	0		incolore	incolore				
  * 	incolore 	1		finVert		Vert				
  * 	finVert	 	0		init		init			
  * 	finvert	 	1		finVert		Vert			
  */			 			
 
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>: Interrupts

bool antiRebond()
{
	if(PIND & 0X04) 
	{ 
		_delay_ms (10.0);
		if ( PIND & 0x04 )
			return true;
	}
	return false;
}

volatile uint8_t compteur; 

// selon le nom de votre variable
// placer le bon type de signal d'interruption
// à prendre en charge en argument

ISR ( INT0_vect ) {
	bool presse;
// laisser un delai avant de confirmer la réponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
		_delay_ms (30.0);
// se souvenir ici si le bouton est pressé ou relâché
		if(PIND & 0x04){
			presse=true;
			}
		else 
			presse=false;

			
		if( presse == true)
			compteur++;
		if (presse == false){
			if(compteur == 5)
				compteur=0;
		
		else compteur++;
	}



EIFR |= (1 << INTF0) ;

}

void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'être interrompu alors que
// le microcontroleur n'est pas prêt...

cli ();

// configurer et choisir les ports pour les entrées
// et les sorties. DDRx... Initialisez bien vos variables

  DDRB = 0xff; // PORT B est en mode sortie
  DDRD = 0x00; // PORT D est en mode ENTREE


// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;


// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA

EICRA |=  (0 << ISC01) | (1 << ISC00);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

void changementdEtatProbleme2(uint8_t compteur)
{
	const uint8_t VERT = 0b10;
	const uint8_t ROUGE = 0b01;
	const uint8_t INCOLORE =0b00;
	
	enum Etat{init, ambre, vert, rouge, incolore, finVert,test};
	
	//for(;;)
	//{
		switch (compteur) 
		{
				case init:
				{
					PORTB = ROUGE; 
					//if (antiRebond()== 1)
					//{
						//compteur++;  
					//}
					break;
				}
				case ambre:
				{ 
					while (PIND & 0X04) // affiche couleur ambree
					{
						_delay_ms (10.0); 
						PORTB = VERT;
						_delay_ms (10.0); 
						PORTB = ROUGE;
					}
					//compteur++; 
					break; 
				}
				case vert:
				{
					PORTB = VERT;
					//if ( antiRebond()== 1 )
					//{
						//compteur++;
					//}
						break; 
				}
				case rouge:
				{
					while (PIND & 0X04){
						PORTB = ROUGE;} 
					//compteur++; 
					break;
				}
					
				case incolore:
				{
					PORTB = INCOLORE;
					//if ( antiRebond()== 1 )
					//{
						//compteur++; 
					//}
						break;
				}
				case finVert:
				{
					while(PIND & 0X04){ 
						PORTB = VERT;}
					break;
						
				} 
				
		}
	//}	
			
}

					
int main()
{
	initialisation();
	for(;;){
	changementdEtatProbleme2(compteur);
}
	
  return 0; 
}

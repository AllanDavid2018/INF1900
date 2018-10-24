/* *********************************
 * Nom: 		probleme2.cpp
 * Auteurs : 	Kevin Ciliento & Roman Zhornytskiy
 * Date :		04/09/2018
 * Mise a jour: 07/09/2018
 * Description: La DEL change de couleur en fonction de l'etat a chaque fois que 
 * l'utilisateur appuit sur le boutton-poussoir.
 * Version: 	1.01
 **********************************/
 
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

/* **********************************
 * Fonction:		AntiRebond
 * Description:		Verifie si le signal entre est le meme apres 10ms
 * Parametre:		aucun
 * Retour :			retourne une valeur booleenne true/false
 ************************************/
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

/* **********************************
 * Fonction:		changementdEtatProbleme2
 * Description:		Change l'etat en fonction du compteur. 
 * Le compteur incremente a l'aide du bouton poussoir jusqu'a 5.
 * Parametre:		- (uint8_t) compteur : compte le nombre de fois que
 * le boutton a ete pousse (IN)
 * Retour :			aucun
 ************************************/
void changementdEtatProbleme2(uint8_t compteur)
{
	const uint8_t VERT = 0b10;
	const uint8_t ROUGE = 0b01;
	const uint8_t INCOLORE =0b00;
	
	enum Etat{init, ambre, vert, rouge, incolore, finVert};
	
	for(;;)
	{
		switch (compteur) 
		{
			case init:
			{
				PORTB = ROUGE; 
				if (antiRebond()== 1)
				{
					compteur++;  
				}
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
				compteur++; break; 
			}
			case vert:
			{
				PORTB = VERT;
				if ( antiRebond()== 1 )
				{
					compteur++;
				}
				break; 
			}
			case rouge:
			{
				while (PIND & 0X04){
					PORTB = ROUGE;} 
				compteur++; break;
			}
			
			case incolore:
			{
				PORTB = INCOLORE;
				if ( antiRebond()== 1 )
				{
					compteur++; 
				}
				break;
			}
			case finVert:
			{
				while(PIND & 0X04){ 
					PORTB = VERT;}
				compteur = 0; break;
			} 
		}
	}			
}

					
int main()
{
 
  DDRB = 0xff; // PORT B est en mode sortie
  DDRD = 0x00; // PORT D est en mode ENTREE
	
	uint8_t compteur = 0;
	changementdEtatProbleme2(compteur);
	
  return 0; 
}

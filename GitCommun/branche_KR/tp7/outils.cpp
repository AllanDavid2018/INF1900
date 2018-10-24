/****************************************************************************
* Fichier:outils.cpp 
* Auteurs: Allan Deddouk, Kevin Ciliento, David Dratwa, Roman Zhornytskiy
* Date de création: 16 octobre 2018
* Modifications: n/a
* Description: Ce fichier est contient des fonctions générales.
****************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#define IN 0x00		//Met le port en entrée
#define OUT 0xFF	//Met le port en sortie
#define EVER (;;)	//Parametres boucle infinie
#define PUSHED (PIND & 0X04)

bool antiRebond()
{
	if (PUSHED)
	{
		_delay_ms(10.0);
		if (PUSHED)
			return true;
	}
	return false;
}
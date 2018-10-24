/****************************************************************************
 * Fichier:inf1900lib.cpp // ou hpp ? 
 * Auteurs: Allan Deddouk, Kevin Ciliento, David Dratwa, Roman Zhornytskiy
 * Date de cr�ation: 16 octobre 2018
 * Modifications: n/a
 * Description: Ce fichier est une librairie contenant toutes les fonctions 
 *				pertinentes affectant le robot du cours INF1900.
 ****************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h> // On garde ? 
//inclure le fichier de memoire et can

#define IN 0x00		//Met le port en entr�e
#define OUT 0xFF	//Met le port en sortie
#define EVER (;;)	//Parametres boucle infinie
#define PUSHED !(PIND & 0x04) //Bouton poussoir press�
#define AVANCE //� D�FINIR--------------------------------
#define RECULE //� D�FINIR--------------------------------
#define SETLED PORTB=

/*Registres*/
void resetRegistres
void setRegistreTimer1() {}
/*--------------------------------------------------------------------------*/

/*Timer*/

/*--------------------------------------------------------------------------*/

/*DEL*/
void setDel(uint8_t couleur) {} // PORT en param�tre ?
void setDelAmbree(uint8_t conditionSortie) {} //Type de la condition template? bool?
/*--------------------------------------------------------------------------*/
 
/*PWM*/
setPWMdirection(uint8_t sens) {}// utilise avance recule
setPWMintensitee(uint8_t intensitee) {} // intensitee en pourcentage
/*--------------------------------------------------------------------------*/

/*Memoire & USART*/
//Partie Memoire
// Il faut d�finir si prend des tranches de 8 bits ou des char un � un. 
// La derni�re semble plus interessante pour la flexibilit�e
void writeMem(uint16_t tableau) {} //16 bits d�pendament de la taille l'instruction
uint8_t readMem() {} // devrait-on utiliser les fonctions de mem_24XXX? car m�mes param�tres

//Partie USART
void afficherMessage() {} //fonction pouvant �tre utile dans le futur pour afficher des �l�ments stock�es dans l'EEROAM
/*--------------------------------------------------------------------------*/

/*Mode analogique*/
/*--------------------------------------------------------------------------*/



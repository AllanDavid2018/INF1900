/****************************************************************************
 * Fichier:inf1900lib.cpp // ou hpp ? 
 * Auteurs: Allan Deddouk, Kevin Ciliento, David Dratwa, Roman Zhornytskiy
 * Date de création: 16 octobre 2018
 * Modifications: n/a
 * Description: Ce fichier est une librairie contenant toutes les fonctions 
 *				pertinentes affectant le robot du cours INF1900.
 ****************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h> // On garde ? 
//inclure le fichier de memoire et can

#define IN 0x00		//Met le port en entrée
#define OUT 0xFF	//Met le port en sortie
#define EVER (;;)	//Parametres boucle infinie
#define PUSHED !(PIND & 0x04) //Bouton poussoir pressé
#define AVANCE //À DÉFINIR--------------------------------
#define RECULE //À DÉFINIR--------------------------------
#define SETLED PORTB=

/*Registres*/
void resetRegistres
void setRegistreTimer1() {}
/*--------------------------------------------------------------------------*/

/*Timer*/

/*--------------------------------------------------------------------------*/

/*DEL*/
void setDel(uint8_t couleur) {} // PORT en paramètre ?
void setDelAmbree(uint8_t conditionSortie) {} //Type de la condition template? bool?
/*--------------------------------------------------------------------------*/
 
/*PWM*/
setPWMdirection(uint8_t sens) {}// utilise avance recule
setPWMintensitee(uint8_t intensitee) {} // intensitee en pourcentage
/*--------------------------------------------------------------------------*/

/*Memoire & USART*/
//Partie Memoire
// Il faut définir si prend des tranches de 8 bits ou des char un à un. 
// La dernière semble plus interessante pour la flexibilitée
void writeMem(uint16_t tableau) {} //16 bits dépendament de la taille l'instruction
uint8_t readMem() {} // devrait-on utiliser les fonctions de mem_24XXX? car mêmes paramètres

//Partie USART
void afficherMessage() {} //fonction pouvant être utile dans le futur pour afficher des éléments stockées dans l'EEROAM
/*--------------------------------------------------------------------------*/

/*Mode analogique*/
/*--------------------------------------------------------------------------*/



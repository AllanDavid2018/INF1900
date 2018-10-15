/**
 * En se basant sur : http://www.groupes.polymtl.ca/inf1900/tp/tp6/,
 *
 * @author Allan BEDDOUK & David Dratwa
 * @created: 2018-10-06
 * @modified: 2018-10-16
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.h"


/*
 Methode qui allume la lumiere en rouge (configure sur le port D)
 */
void allumerRouge() {
	 PORTD = 0b10;
}

/*
 Methode qui allume la lumiere en vert (configure sur le port D)
 */
void allumerVert() { 
	PORTD = 0b01;
}

/*
 Methode qui allume la lumiere en ambre (configure sur le port D)
 */
void allumerAmbre(){ 
	for ( uint8_t i=0 ; i<60 ; i++ )
    {
        _delay_us (100);
        allumerRouge();
		_delay_us (10);
        allumerVert();
    }
}

void initialisation () {
// Désactive les interruptions
  DDRA = 0x00; // PORT A est en mode entree
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie
}


int main()
{
    
   initialisation();

//On declare un objet de type can pour pouvoir lire la valeur convertie par le convertisseur Analogigue vers numerique
   can convertisseur;
    

	for(;;)
    {
		uint8_t valeurConvertie = convertisseur.lecture(0)>>2; // On decale la valeur pour obtenir une valeur en 8bits a partir d'une 10bits initialement
		
		if(valeurConvertie <= 30) // on considere que si la valeur convertie est plus petite ou egale a 30 on est en lumiere basse (donc DEL verte)
			allumerVert();
       
		else if(valeurConvertie>30 && valeurConvertie<=50) // on considere que si elle est comprise entre 31 et 50 on est en lumiere a un bon niveau (donc DEL ambre)
			allumerAmbre();	
			
		else if(valeurConvertie>50)// on considere que si elle est plus grande strictement a 50 on est en lumiere basse (donc DEL rouge)
			allumerRouge();
    }

    return 0; 
}

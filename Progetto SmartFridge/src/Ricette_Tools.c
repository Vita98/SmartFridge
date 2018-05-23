/*
 * Ricette_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"


int Scelta_Opzioni_Ricette(){

	int NumScelta;

	do{
		NumScelta=FaiScelta(MenuRicette);

		switch(NumScelta){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 0:
				//case di uscita dal sottomenu
				break;
			default:
				printf("Scelta errata! Riprova!\n");
		}

	}while(NumScelta!=0);

	return 0;
}

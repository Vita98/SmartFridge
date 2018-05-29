/*
 * Ricette_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"


int Scelta_Opzioni_Ricette(ricetta ricette[],int lunghezza_vettore_ricette){

	int NumScelta;

	do{
		NumScelta=FaiScelta(MenuRicette);

		switch(NumScelta){
			case 1:

				//viualizza lista ricette

				break;
			case 2:

				//aggiungi ricetta

				break;
			case 3:

				//modifica ricetta

				break;
			case 4:

				//cancella ricetta

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

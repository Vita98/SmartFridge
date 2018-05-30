/*
 * Ricette_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <String.h>



int Visualizza_Ricette(ricetta ricette[], int Lunghezza_Vettore) {

	int i;

	printf("Ricette presenti:\n");
	for (i = 0; i < Lunghezza_Vettore - 1; i++) {

		if (ricette[i].Visibilita){
			printf("%d - %s \t| Kcal per porzione: %f \t| Id: %d  \n", i,
							ricette[i].Nome, ricette[i].Kcal_Porzione, ricette[i].ID_Ricetta);
		}

	}
	return 1;
}


int Ordina_Ricette(ricetta ricette[],char stringa[],int Vett_Ordinato[],int Lunghezza_Vettore){



	return 1;
}




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

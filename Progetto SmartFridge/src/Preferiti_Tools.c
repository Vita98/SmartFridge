/*
 * Preferiti_Tools.c
 *
 *  Created on: 06 giu 2018
 *      Author: giutu
 */
#include "Tipi_Dato.h"
#include "Ricette_Tools.h"
#include <String.h>

int Scelta_Opzioni_Preferiti(ricetta ricette[]){


	int NumScelta;

		do {
			NumScelta = FaiScelta(MENU_GESTISCI_PREFERTI);

			switch (NumScelta) {

			case 1:
				//Visualizza PREFERITI

				break;

			case 2:
				//Aggiungi preferito

				break;

			case 3:
				//Cancella Preferito

				break;

			default:
				printf("Scelta errata! Riprova!\n");

			}
		}while(NumScelta != 0);

		return 0;


}

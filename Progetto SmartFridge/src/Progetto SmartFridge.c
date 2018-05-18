/*
 ============================================================================
 Name        : Progetto.c
 Author      : Vitandrea Sorino
 Version     :
 Copyright   : Your copyright notice
 Description : Hel1lo World in C, Ansi-style
 ============================================================================
 */

#include "Tipi_Dato.h"
#include "Gen_File.h"
#include "Spesa_Tools.h"


void pressToContinue();

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);


	int NumScelta;
	Carica_Configurazione();

	printf("Benvenuto in SMARTFRIDGE\n");
	do {
		NumScelta = FaiScelta(MenuPrincipale);

		switch (NumScelta) {
			case 1:		//Suggerimento spesa

				Scelte_Spesa();

				break;

			case 2:		//Suggerimento Ricette

				break;

			case 3:		//Ricerca Ricette

				break;
			case 4:		//Opzioni Alimenti
				//NumScelta = FaiScelta(MenuAlimenti);

				break;
			case 5:		//Opzioni Ricette
				//NumScelta = FaiScelta(MenuRicette);

				break;
			case 6:		//Opzioni Pasti
				//NumScelta = FaiScelta(MenuPasti);

				break;

			case 7:
				break;

			default:
				printf("\nScelta non valida!\n");
		}

	} while (NumScelta != 7);

	system("pause");

	return 0;
}


/*FUNZIONE CHE SI METTE IN ATTESA CHE   *
 *L'UTENTE PREMA QUALCHE TASTO			*/
void pressToContinue() {
	printf("Premi per continuare....");
	getchar();
}








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
#include "Ricette_Tools.h"
#include "Alimenti_Tools.h"

void pressToContinue();

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	int NumScelta;

	//HO FATTO SOLO QUESTO, si capisce, e nella console funziona (bug sull'ultimo)
	lunghezza_vettore_alimenti = Get_Lunghezza_File_Alimenti();
	alimento alimenti[lunghezza_vettore_alimenti];
	Carica_Alimenti(alimenti);


	//Caricamento delle impostazioni dal file di configurazione
	Carica_Configurazione();

	printf("Benvenuto in SMARTFRIDGE\n");
	do {
		NumScelta = FaiScelta(MenuPrincipale);

		switch (NumScelta) {
		case 1:		//Suggerimento spesa

			Scelte_Spesa(alimenti,lunghezza_vettore_alimenti);

			break;

		case 2:		//Suggerimento Ricette



			break;

		case 3:		//Ricerca Ricette

			break;
		case 4:		//Opzioni Alimenti

			Scelta_Opzioni_Alimenti(alimenti,lunghezza_vettore_alimenti);

			break;
		case 5:		//Opzioni Ricette

			Scelta_Opzioni_Ricette();

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

	//system("pause");

	return 0;
}





/*FUNZIONE CHE SI METTE IN ATTESA CHE   *
 *L'UTENTE PREMA QUALCHE TASTO			*/
void pressToContinue() {
	printf("Premi per continuare....");
	getchar();
	system("cls");
}


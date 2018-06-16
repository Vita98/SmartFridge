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
#include "Ricette_Tools.h"
#include "Alimenti_Tools.h"
#include "Lista_Spesa_Tools.h"
#include "Spesa_Tools.h"
#include "Data_Tools.h"
#include "Pasti_Tools.h"
#include "Ricerca_Ricette_Tools.h"


void pressToContinue();

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	int numScelta;


	//creazione e caricamento del vettore di alimenti
	int lunghezzaVettoreAlimenti = Get_Lunghezza_File_Alimenti();
	alimento *alimenti=(alimento*) calloc(lunghezzaVettoreAlimenti,sizeof(alimento));
	Carica_Alimenti(alimenti);


	//creazione e caricamento del vettore di ricette
	int lunghezzaVettoreRicette=Get_Lunghezza_File_Ricette();
	ricetta *ricette=(ricetta*) calloc(lunghezzaVettoreRicette,sizeof(ricetta));
	Carica_Ricette(ricette);


	//Caricamento delle impostazioni dal file di configurazione
	Carica_Configurazione();


	int nuovoIndirizzoAlimenti;
	int nuovoIndirizzoRicette;
	printf("Benvenuto in SMARTFRIDGE\n");
	do {

		numScelta = fai_scelta(MENU_PRINCIPALE);

		switch (numScelta) {
		case 1:		//Suggerimento spesa

			scelte_spesa(alimenti,lunghezzaVettoreAlimenti);

			break;

		case 2:		//Suggerimento Ricette

			suggerimento_ricette_in_scadenza(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;

		case 3:		//Ricerca Ricette per alimento

			ricerca_ricette_per_alimenti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);


			break;
		case 4:		//Opzioni Alimenti

			scelta_opzioni_alimenti(alimenti,lunghezzaVettoreAlimenti);

			break;
		case 5:		//Opzioni Ricette

			lunghezzaVettoreRicette=scelta_opzioni_ricette(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,&nuovoIndirizzoRicette);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di una nuovo ricetta
			ricette=(ricetta *)nuovoIndirizzoRicette;

			break;
		case 6:		//Opzioni Pasti

			scelta_opzioni_pasti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;

		case 7: //Inserisci Spesa


			lunghezzaVettoreAlimenti=scelta_opzioni_spesa(alimenti,lunghezzaVettoreAlimenti,&nuovoIndirizzoAlimenti);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di un nuovo alimento
			alimenti=(alimento *)nuovoIndirizzoAlimenti;


			break;

		case 8:
			break;

		default:
			printf("\nScelta non valida!\n");
		}

	} while (numScelta != 8);

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


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


void pressToContinue();

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	int NumScelta;


	//creazione e caricamento del vettore di alimenti
	int lunghezza_vettore_alimenti = Get_Lunghezza_File_Alimenti();
	alimento *alimenti=(alimento*) calloc(lunghezza_vettore_alimenti,sizeof(alimento));
	Carica_Alimenti(alimenti);



	//creazione e caricamento del vettore di ricette
	int lunghezza_vettore_ricette=Get_Lunghezza_File_Ricette();
	ricetta ricette[lunghezza_vettore_ricette];
	Carica_Ricette(ricette);


	//Caricamento delle impostazioni dal file di configurazione
	Carica_Configurazione();

	//int *NuovoIndirizzoAlimenti=(int*) calloc(1,sizeof(int));
	int NuovoIndirizzoAlimenti;
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

			Scelta_Opzioni_Ricette(ricette,lunghezza_vettore_ricette,alimenti,lunghezza_vettore_alimenti);

			break;
		case 6:		//Opzioni Pasti
			//NumScelta = FaiScelta(MenuPasti);

			break;

		case 7: //Inserisci Spesa


			lunghezza_vettore_alimenti=Scelta_Opzioni_Spesa(alimenti,lunghezza_vettore_alimenti,&NuovoIndirizzoAlimenti);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di un nuovo alimento
			alimenti=(alimento *)NuovoIndirizzoAlimenti;


			break;

		case 8:
			break;

		default:
			printf("\nScelta non valida!\n");
		}

	} while (NumScelta != 8);

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


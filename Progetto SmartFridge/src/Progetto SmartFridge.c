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
#include "Messaggi_Menu.h"

int FaiScelta(char[]);

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);


	int NumScelta;

	printf("Benvenuto in SMARTFRIDGE\n");
	do {
		NumScelta = FaiScelta(MenuPrincipale);

		switch (NumScelta) {

		case 1:		//Suggerimento spesa

			NumScelta = FaiScelta(MenuSuggerimentoSpesa);



			break;

		case 2:		//Suggerimento Ricette

			break;

		case 3:		//Ricerca Ricette

			break;
		case 4:		//Opzioni Alimenti
			NumScelta = FaiScelta(MenuAlimenti);

			break;
		case 5:		//Opzioni Ricette
			NumScelta = FaiScelta(MenuRicette);

			break;
		case 6:		//Opzioni Pasti
			NumScelta = FaiScelta(MenuPasti);

			break;

		default:
			printf("\nScelta non valida!\n");
			break;
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








/*FUNZIONE UTILIZZATA PER PRENDERE IN INPUT				*
 *UN VALORE INTERO										*
 *														*
 *LA FUNZIONE VISUALIZZA IL MESSAGGIO PASSATO COME 		*
 *PARAMETRO E CHIEDE IN INPUT UN NUMERO DI CUI VENGONO	*
 *FATTI TUTTI I CONTROLLI								*
 *														*
 *LA FUNZIONE RITORNA IL NUMERO INTERO CHIESTO			*
 *IN INPUT ALL'UTENTE									*/
int FaiScelta(char text[]) {

	char scelta[LUNGHEZZA_STRINGA];

	do {
		//Stampo il messaggio passato come parametro
		printf(text);
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);

		//Svuoto il buffer nel caso venga inserita una stringa piu grande della lunghezza massima
		fflush(stdin);

		//Se la stringa presa in input non e' un numero scrivo un messaggio di errore
		//altrimenti la funzione ritorna il numero preso in input convertito in intero
		if (!isNumber(scelta))
			printf("Scelta errata!\n");
		else
			return toNumber(scelta);

		//continuo a chiedere in input la scelta fino a che non e' valida
	} while (!isNumber(scelta));
	return 0;
}

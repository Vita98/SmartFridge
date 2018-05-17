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

int FaiScelta(char[]);

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	char MenuPrincipale[] =
			"\nCosa desidera scegliere?\n****************************************\n"
					"1 - Suggerimento della Lista della Spesa\n"
					"2 - Suggerimento delle Ricette\n3 - Ricerca Ricette\n"
					"4 - Opzioni Alimenti\n5 - Opzioni Ricette\n6 - Opzioni Pasti\n\n"
					"7 - Uscita\n****************************************\nScelta: ";

	char MenuSuggerimentoSpesa[] =
			"\n****************************************\n"
					"La Lista generata rispetterà una soglia minima stabilita\n"
					"1 - Genera la Lista della Spesa\n2 - Visualizza l'ultima Lista generata\n"
					"3 - Modifica soglia limite\n\n0 - Indietro\n****************************************\nScelta: ";

	char MenuAlimenti[] =
			"\n****************************************\n"
					"1 - Visualizza la Lista degli Alimenti\n2 - Aggiungi Alimento\n3 - Modifica Alimento"
					"\n\n0 - Indietro\n****************************************\nScelta: ";

	char MenuRicette[] =
			"\n****************************************\n"
					"1 - Visualizza la Lista delle Ricette\n2 - Aggiungi Ricetta\n3 - Modifica Ricetta\n"
					"4 - Cancella Ricetta\n\n0 - Indietro\n****************************************\nScelta: ";

	char MenuSuggerimentoAlimenti[] =
			"\n****************************************\n"
					"Come desidera visualizzare gli Alimenti?\n1 - Alimenti più usati\n2 - Alimenti presenti\n"
					"\n0 - Indietro\n****************************************\nScelta: ";

	char MenuOrdinamentoRicette[] =
			"\n****************************************\n"
					"Come desidera Ordinare le Ricette?\n1 - Ordinamento per kcal\n2 - Ordinamento per frequenza\n"
					"\n0 - Indietro\n****************************************\nScelta: ";

	char MenuPasti[] =
			"\n****************************************\n"
					"1 - Visualizza il Menù Settimanale\n2 - Aggiungi Pasto\n3 - Modifica Pasto\n"
					"4 - Cancella Pasto\n\n0 - Indietro\n****************************************\nScelta: ";


	int NumScelta;

	printf("Benvenuto in SMARTFRIDGE\n");
	do {
		NumScelta = FaiScelta(MenuPrincipale);

		switch (NumScelta) {

		case 1:		//Suggerimento spesa

			NumScelta = FaiScelta(MenuSuggerimentoSpesa);

			do{
				switch (NumScelta) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					NumScelta = FaiScelta("Riprova: ");
					break;
				}
			 }while (NumScelta != 0);


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

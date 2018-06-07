/*
 * Preferiti_Tools.c
 *
 *  Created on: 06 giu 2018
 *      Author: giutu
 */
#include "Tipi_Dato.h"
#include "Ricette_Tools.h"
#include <String.h>

boolean Controllo_Preferiti(ricetta ricette[], int Lunghezza_vettore_ricette,
		char scelta[], int* IndiceRicetta, boolean controllo) {

	//controllo se la ricetta inserita in input esiste nel vettore di ricette
	if ((*IndiceRicetta = getRicetta(ricette, Lunghezza_vettore_ricette, scelta,
			false)) > -1) {

		FILE *file_preferiti;

		if ((file_preferiti = fopen("src/Preferiti.sf", "rb")) == NULL) {
			return false;

		} else {

			ricetta ric;
			while (!feof(file_preferiti)) {

				fread(&ric, sizeof(ricetta), 1, file_preferiti);

				if (strcmp(ric.Nome, ricette[*IndiceRicetta].Nome) == 0) {
					return true;
					break;
				}

			}

			fclose(file_preferiti);

		}

	} else {
		printf("\nLa Ricetta \"%s\" non esiste!\n", scelta);

	}

	return false;

}

int Aggiungi_Preferito(ricetta ricette[], int Lunghezza_vettore_ricette) {

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta da aggiungere: ");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int IndiceRicetta;
	boolean controllo = false;

	FILE *file_preferiti;
	controllo = Controllo_Preferiti(ricette, Lunghezza_vettore_ricette, scelta,
			&IndiceRicetta, controllo);

	if (controllo == true) {
		printf("\nLa Ricetta è già presente nei Preferiti.\n");
		return 0;

	} else {
		if (((file_preferiti = fopen("src/Preferiti.sf", "ab")) == NULL)
				|| (IndiceRicetta < 0)) {
			return 0;

		} else {

			fwrite(&ricette[IndiceRicetta], sizeof(ricetta), 1, file_preferiti);
			printf("Preferito aggiunto  (%s | Frequenza: %d \t| Id: %d)\n",
					ricette[IndiceRicetta].Nome,
					ricette[IndiceRicetta].Frequenza,
					ricette[IndiceRicetta].ID_Ricetta);

		}

		fclose(file_preferiti);

		return 1;
	}

}

//NON PERFETTAMENTE FUNZIONANTE _ NON PARTE IL PRIMO ELSE

int Cancella_Preferito(ricetta ricette[], int Lunghezza_vettore_ricette) {

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta da Cancellare: ");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int IndiceRicetta, i = 0;;
	boolean controllo = false;

	FILE *file_preferiti;
	controllo = Controllo_Preferiti(ricette, Lunghezza_vettore_ricette, scelta,
			&IndiceRicetta, controllo);

	if (controllo == false) {
		printf("\nLa Ricetta non è presente nei Preferiti.\n");
		return 0;

	} else {
		if ((file_preferiti = fopen("src/Preferiti.sf", "rb")) == NULL) {
			printf("Step 0\n");
			return 0;
			printf("Step 00\n");

		} else {


			while (!feof(file_preferiti)) {
				i++;
			}

			printf("Step 1\n");

			ricetta ric[i - 1];
			i = 0;

			while (!feof(file_preferiti)) {

				fread(&ric[i], sizeof(ricetta), 1, file_preferiti);
				i++;
				printf("Step 2\n");

				if (ric[i].ID_Ricetta == ricette[IndiceRicetta].ID_Ricetta) {
					i--;
					printf("Step 3\n");
				}

				printf("Step 4\n");

			}

			fclose(file_preferiti);
			i = 0;

			if ((file_preferiti = fopen("src/Preferiti.sf", "wb")) == NULL) {
				return 0;

			} else {
				while (!feof(file_preferiti)) {

					fwrite(&ric[i], sizeof(ricetta), 1, file_preferiti);
					printf(
							"Preferito aggiunto  (%s | Frequenza: %d \t| Id: %d)\n",
							ric[i].Nome,
							ric[i].Frequenza,
							ric[i].ID_Ricetta);
				}

			}

			fclose(file_preferiti);

			return 1;
		}

	printf ("EPIC FAIL\n");

	}


}



int Visualizza_Preferiti(ricetta ricette[]) {

FILE *file_preferiti;

if ((file_preferiti = fopen("src/Preferiti.sf", "rb")) == NULL)
return 0;
else {

ricetta ric;
int i = 0;

printf("\nLe Ricette poste nella lista dei preferiti sono:\n");

while (!feof(file_preferiti)) {	//stampa l'ultimo 2 volte_ ORA NON PIU con l'IF(!feof)

	fread(&ric, sizeof(ricetta), 1, file_preferiti);

	if (!feof(file_preferiti)) {
		printf("%d - %s \t| frequenza: %d \t| Id: %d\n", i, ric.Nome,
				ric.Frequenza, ric.ID_Ricetta);
		i++;
	}

}

fclose(file_preferiti);
return 1;
}

}

int Scelta_Opzioni_Preferiti(ricetta ricette[], int Lunghezza_vettore_ricette) {

int NumScelta;

do {
NumScelta = FaiScelta(MENU_GESTISCI_PREFERTI);

switch (NumScelta) {

case 1:
	//Visualizza PREFERITI
	Visualizza_Preferiti(ricette);
	break;

case 2:
	//Aggiungi preferito
	Aggiungi_Preferito(ricette, Lunghezza_vettore_ricette);
	break;

case 3:
	//Cancella Preferito
	Cancella_Preferito(ricette, Lunghezza_vettore_ricette);
	break;

case 0:
	//case di uscita dal sottomenu
	break;

default:
	printf("Scelta errata! Riprova!\n");

}
} while (NumScelta != 0);

return 0;

}

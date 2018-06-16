/*
 * Preferiti_Tools.c
 *
 *  Created on: 06 giu 2018
 *      Author: giutu
 */
#include "Tipi_Dato.h"
#include "Ricette_Tools.h"
#include <String.h>







boolean exist_preferito(ricetta ricette[], int* indiceRicetta){
	//controllo se la ricetta inserita in input esiste nel vettore di ricette
	FILE *filePreferiti;

	if ((filePreferiti = fopen("src/Preferiti.sf", "rb")) == NULL) {
		return false;

	} else {

		ricetta ric;
		while (!feof(filePreferiti)) {

			if(fread(&ric, sizeof(ricetta), 1, filePreferiti) > 0){
				if (strcmp(ric.Nome, ricette[*indiceRicetta].Nome) == 0) {
					return true;
					break;
				}
			}
		}

		fclose(filePreferiti);

	}
	return false;
}





/*	FUNZIONE CHE PERMETTE DI CONTROLLARE SE UNA DATA RICETTA PASSATA TRAMITE STRINGA 	*
 * 	SIA PRESENTE ALL'INTERNO DEL FILE DEI PREFERITI										*
 *																						*
 * 	SONO PASSATI COME PARAMETRI IL VETTORE DI RICETTE E LA SUA LUNGHEZZA, LA STRINGA 	*
 *	CONTENENTE IL VALORE DA CERCARE, UN PUNTATORE DI INTERI (ALLA QUALE VARIABILE SARA'	*
 * 	PASSATO L'INDICE DELL'ELEMENTO TROVATO, SE ESISTE) 									*
 *																						*
 * 	LA FUNZIONE RESTITUISCE UN VALORE DI TIPO BOOLEANO, RESTITUIRA' VERO SE LA RICETTA 	*
 * 	CERCATA ESISTE, RESTITUIRA FALSO ALTRIMENTI											*/
boolean controllo_preferiti(ricetta ricette[], int lunghezzaVettoreRicette,
		char scelta[], int* indiceRicetta) {

	//controllo se la ricetta inserita in input esiste nel vettore di ricette
	if ((*indiceRicetta = get_ricetta(ricette, lunghezzaVettoreRicette, scelta,
			false)) > -1) {

		if(exist_preferito(ricette,indiceRicetta) == true) return true;
		else return false;

	} else {
		printf("\nLa Ricetta \"%s\" non esiste!\n", scelta);

	}

	return false;

}












/*	FUNZIONE CHE ACQUISISCE UNA STRINGA (UNA RICETTA), VERIFICA SE LA RICETTA INSERITA	*
 * 	ESISTA ALL'INTERNO DEL FILE DEI PREFERITI E SE NON E' PRESENTE VIENE SCRITTA 		*
 * 	IN CODA ALLA FINE DEL FILE															*/
int aggiungi_preferito(ricetta ricette[], int lunghezzaVettoreRicette) {

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta da aggiungere: ");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indiceRicetta;
	boolean controllo = false;

	FILE *filePreferiti;
	controllo = controllo_preferiti(ricette, lunghezzaVettoreRicette, scelta,
			&indiceRicetta);

	if (controllo == true) {
		printf("\nLa Ricetta è già presente nei Preferiti.\n");
		return 0;

	} else {
		if (((filePreferiti = fopen("src/Preferiti.sf", "ab")) == NULL)
				|| (indiceRicetta < 0)) {
			return 0;

		} else {

			fwrite(&ricette[indiceRicetta], sizeof(ricetta), 1, filePreferiti);
			printf("\nLa Ricetta '%s' è stata aggiunta ai Preferiti.\n",
					ricette[indiceRicetta].Nome);

		}

		fclose(filePreferiti);

		return 1;
	}

}









/*	FUNZIONE CHE PERMETTE DI CANCELLARE DAL FILE DEI PREFERITI LA RICETTA VOLUTA	*
 * 	LEGGENDO IL FILE E CARICANDO UN VETTORE DI RICETTE DI LUNGHEZZA PARI AL NUMERO	*
 * 	DI RICETTE DEL FILE MENO 1, IL NUOVO VETTORE SARA PRIVO DELLA RICETTA DA 		*
 * 	CANCELLARE
 *
 * 	INFINE, IL FILE DEI PREFERITI SARA' RIEMPITO DAGLI ELEMENTI DEL VETTORE APPENA 	*
 * 	RISULTANDO UGUALE ALLA VERSIONE PRECEDENTE, SOLO PRIVA DELLA RICETTA CANCELLATA	*/
int cancella_preferito(ricetta ricette[], int lunghezzaVettoreRicette) {

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta da Cancellare: ");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indiceRicetta;
	boolean controllo = false;

	FILE *filePreferiti;
	controllo = controllo_preferiti(ricette, lunghezzaVettoreRicette, scelta,&indiceRicetta);

	//Controllo se la ricetta è preente nel file dei preferiti
	if (controllo == false) {
		printf("\nLa Ricetta non è presente nei Preferiti.\n");
		return 0;

	} else {

		if ((filePreferiti = fopen("src/Preferiti.sf", "rb")) == NULL)
			return 0;
		else {

			ricetta ric;
			int j, i = 0;

			//Calcolo il numero di ricette presenti sul file
			while (!feof(filePreferiti)) {

				fread(&ric, sizeof(ricetta), 1, filePreferiti);
				if (!feof(filePreferiti)) {
					i++;
				}

			}

			ricetta preferiti[i - 1];
			i = 0;

			fseek(filePreferiti, 0 * sizeof(ricetta), SEEK_SET);

			//Assegnazione dei preferiti nel vettore contenente tutti i preferiti, escluso quello da cancellare
			while (!feof(filePreferiti)) {

				fread(&ric, sizeof(ricetta), 1, filePreferiti);

				if (!feof(filePreferiti)) {
					if (ric.ID_Ricetta != ricette[indiceRicetta].ID_Ricetta) {
						preferiti[i] = ric;
						i++;
					}
				}

			}

			fclose(filePreferiti);

			if ((filePreferiti = fopen("src/Preferiti.sf", "wb")) == NULL) {
				return 0;

			} else {

				//Scrittura del nuovo file con i preferiti aggiornati
				for (j = 0; j < i; j++) {

					fwrite(&preferiti[j], sizeof(ricetta), 1, filePreferiti);

				}

				fclose(filePreferiti);

				printf("\nLa Ricetta è stata cancellata.\n");
				return 1;
			}



		}

	}

}









/*	FUNZIONE CHE LEGGENDO IL FILE DEI PREFERITI, RIPRODUCE IN OUTPUT LE RICETTE SALVATE	*/
int visualizza_preferiti(ricetta ricette[]) {

	FILE *filePreferiti;

	if ((filePreferiti = fopen("src/Preferiti.sf", "rb")) == NULL)
		return 0;
	else {

		ricetta ric;
		int i = 0;

		printf("\nLe Ricette poste nella lista dei preferiti sono:\n");

		while (!feof(filePreferiti)) {

			if (fread(&ric, sizeof(ricetta), 1, filePreferiti) > 0) {
				printf("%d - %s \t| frequenza: %d \t| Id: %d\n", i, ricette[ric.ID_Ricetta].Nome,
						ricette[ric.ID_Ricetta].Frequenza, ric.ID_Ricetta);
				i++;
			}

		}

		fclose(filePreferiti);
		return 1;
	}

}











int scelta_opzioni_preferiti(ricetta ricette[], int lunghezzaVettoreRicette) {

	int NumScelta;

	do {
		NumScelta = fai_scelta(MENU_GESTISCI_PREFERTI);

		switch (NumScelta) {

		case 1:
			//Visualizza PREFERITI
			visualizza_preferiti(ricette);
			break;

		case 2:
			//Aggiungi preferito
			aggiungi_preferito(ricette, lunghezzaVettoreRicette);
			break;

		case 3:
			//Cancella Preferito
			cancella_preferito(ricette, lunghezzaVettoreRicette);
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

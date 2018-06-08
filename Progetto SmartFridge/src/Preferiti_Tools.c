/*
 * Preferiti_Tools.c
 *
 *  Created on: 06 giu 2018
 *      Author: giutu
 */
#include "Tipi_Dato.h"
#include "Ricette_Tools.h"
#include <String.h>



/*	FUNZIONE CHE PERMETTE DI CONTROLLARE SE UNA DATA RICETTA PASSATA TRAMITE STRINGA 	*
 * 	SIA PRESENTE ALL'INTERNO DEL FILE DEI PREFERITI										*
 *																						*
 * 	SONO PASSATI COME PARAMETRI IL VETTORE DI RICETTE E LA SUA LUNGHEZZA, LA STRINGA 	*
 *	CONTENENTE IL VALORE DA CERCARE, UN PUNTATORE DI INTERI (ALLA QUALE VARIABILE SARA'	*
 * 	PASSATO L'INDICE DELL'ELEMENTO TROVATO, SE ESISTE) 									*
 *																						*
 * 	LA FUNZIONE RESTITUISCE UN VALORE DI TIPO BOOLEANO, RESTITUIRA' VERO SE LA RICETTA 	*
 * 	CERCATA ESISTE, RESTITUIRA FALSO ALTRIMENTI											*/
boolean Controllo_Preferiti(ricetta ricette[], int Lunghezza_vettore_ricette,
		char scelta[], int* IndiceRicetta) {

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







/*	FUNZIONE CHE ACQUISISCE UNA STRINGA (UNA RICETTA), VERIFICA SE LA RICETTA INSERITA	*
 * 	ESISTA ALL'INTERNO DEL FILE DEI PREFERITI E SE NON E' PRESENTE VIENE SCRITTA 		*
 * 	IN CODA ALLA FINE DEL FILE															*/
int Aggiungi_Preferito(ricetta ricette[], int Lunghezza_vettore_ricette) {

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta da aggiungere: ");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int IndiceRicetta;
	boolean controllo = false;

	FILE *file_preferiti;
	controllo = Controllo_Preferiti(ricette, Lunghezza_vettore_ricette, scelta,
			&IndiceRicetta);

	if (controllo == true) {
		printf("\nLa Ricetta è già presente nei Preferiti.\n");
		return 0;

	} else {
		if (((file_preferiti = fopen("src/Preferiti.sf", "ab")) == NULL)
				|| (IndiceRicetta < 0)) {
			return 0;

		} else {

			fwrite(&ricette[IndiceRicetta], sizeof(ricetta), 1, file_preferiti);
			printf("\nLa Ricetta '%s' è stata aggiunta ai Preferiti.\n",
					ricette[IndiceRicetta].Nome);

		}

		fclose(file_preferiti);

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
int Cancella_Preferito(ricetta ricette[], int Lunghezza_vettore_ricette) {

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta da Cancellare: ");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int IndiceRicetta;
	boolean controllo = false;

	FILE *file_preferiti;
	controllo = Controllo_Preferiti(ricette, Lunghezza_vettore_ricette, scelta,&IndiceRicetta);

	//Controllo se la ricetta è preente nel file dei preferiti
	if (controllo == false) {
		printf("\nLa Ricetta non è presente nei Preferiti.\n");
		return 0;

	} else {

		if ((file_preferiti = fopen("src/Preferiti.sf", "rb")) == NULL)
			return 0;
		else {

			ricetta ric;
			int j, i = 0;

			//Calcolo il numero di ricette presenti sul file
			while (!feof(file_preferiti)) {

				fread(&ric, sizeof(ricetta), 1, file_preferiti);
				if (!feof(file_preferiti)) {
					i++;
				}

			}

			ricetta preferiti[i - 1];
			i = 0;

			fseek(file_preferiti, 0 * sizeof(ricetta), SEEK_SET);

			//Assegnazione dei preferiti nel vettore contenente tutti i preferiti, escluso quello da cancellare
			while (!feof(file_preferiti)) {

				fread(&ric, sizeof(ricetta), 1, file_preferiti);
				printf("1___ ric: %s\n", ric.Nome);

				if (!feof(file_preferiti)) {
					if (ric.ID_Ricetta != ricette[IndiceRicetta].ID_Ricetta) {
						preferiti[i] = ric;
						printf("Aggiunto ric: %s	| preferiti[%d]: %s\n",
								ric.Nome, i, preferiti[i].Nome);
						i++;
					}
				}

				printf("Giro di While \n");

			}

			fclose(file_preferiti);

			if ((file_preferiti = fopen("src/Preferiti.sf", "wb")) == NULL) {
				return 0;

			} else {

				//Scrittura del nuovo file con i preferiti aggiornati
				for (j = 0; j < i; j++) {

					fwrite(&preferiti[j], sizeof(ricetta), 1, file_preferiti);
					printf(
							"Preferito aggiunto  (%s | Frequenza: %d \t| Id: %d)\n",
							preferiti[j].Nome, preferiti[j].Frequenza,
							preferiti[j].ID_Ricetta);
				}

				fclose(file_preferiti);

				return 1;
			}

		}

	}

}









/*	FUNZIONE CHE LEGGENDO IL FILE DEI PREFERITI, RIPRODUCE IN OUTPUT LE RICETTE SALVATE	*/
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

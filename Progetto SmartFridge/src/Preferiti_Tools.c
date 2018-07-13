/**
 *  @file 	   Preferiti_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Preferiti_Tools.h
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include "Tipi_Dato.h"
#include "Ricette_Tools.h"
#include <String.h>






/**
 * Dato il vettore di ricette, la funzione apre il file di ricette preferite(Preferiti.sf)
 * e controlla se la ricetta inserita sia presente al suo interno.
 *
 * @pre il vettore di ricette deve essere pieno o inizializzato.
 * @pre l'indice passato deve essere un indice valido.
 *
 */
boolean exist_preferito(ricetta ricette[], int* indiceRicetta){
	//controllo se la ricetta inserita in input esiste nel vettore di ricette
	FILE *filePreferiti;

	if ((filePreferiti = fopen("Preferiti.sf", "rb")) == NULL) {
		return false;

	} else {

		ricetta ric;
		while (!feof(filePreferiti)) {

			if(fread(&ric, sizeof(ricetta), 1, filePreferiti) > 0){
				if (strcmp(ric.Nome, ricette[*indiceRicetta].Nome) == 0) {
					fclose(filePreferiti);
					return true;
					break;
				}
			}
		}

		fclose(filePreferiti);

	}
	return false;
}






/**
* Dato il vettore di ricette, la funzione controlla se la ricetta inserita sia esistenze
 * e presente all'interno dei preferiti.
 *
 * @pre il vettore di ricette deve essere pieno o inizializzato.
 *
 * @warning la lunghezza del vettore deve essere la lunghezza effettiva
 * in quanto una discordanza potrebbe causare una lettura di porzioni
 * di memoria non allocate.
 */
boolean controllo_preferiti(ricetta ricette[], int lunghezzaVettoreRicette,
		char scelta[], int* indiceRicetta) {

	//controllo se la ricetta inserita in input esiste nel vettore di ricette
	if ((*indiceRicetta = get_ricetta(ricette, lunghezzaVettoreRicette, scelta,
			true)) > -1) {

		if(exist_preferito(ricette,indiceRicetta) == true) return true;
		else return false;

	} else {
		printf("\nLa Ricetta \"%s\" non esiste!\n", scelta);

	}

	return false;

}












/**
 * Data la ricetta inserita da tastiera, la funzione lo aggiunge in coda
 * al file dei preferiti una volta controllato se non e' gia' presente.
 *
 * @pre il vettore di ricette deve essere pieno o inizializzato.
 *
 * @warning la lunghezza del vettore deve essere la lunghezza effettiva
 * in quanto una discordanza potrebbe causare una lettura di porzioni
 * di memoria non allocate.
 */
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
		printf("\nLa Ricetta e' gia' presente nei Preferiti.\n");
		return 0;

	} else {
		if (((filePreferiti = fopen("Preferiti.sf", "ab")) == NULL) || (indiceRicetta < 0)) {
			return 0;
		}else{
			fwrite(&ricette[indiceRicetta], sizeof(ricetta), 1, filePreferiti);
			printf("\nLa Ricetta '%s' e' stata aggiunta ai Preferiti\n",ricette[indiceRicetta].Nome);
		}
		fclose(filePreferiti);
		return 1;
	}

}









/**
 * Data la ricetta passata come parametro, la funzione lo cancella dal
 * file dei preferiti una volta controllato se e' presente.
 *
 * @pre il vettore di ricette deve essere pieno o inizializzato.
 *
 * @warning la lunghezza del vettore deve essere la lunghezza effettiva
 * in quanto una discordanza potrebbe causare una lettura di porzioni
 * di memoria non allocate.
 */
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
		printf("\nLa Ricetta non e' presente nei Preferiti.\n");
		return 0;

	} else {

		if ((filePreferiti = fopen("Preferiti.sf", "rb")) == NULL)
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

			if ((filePreferiti = fopen("Preferiti.sf", "wb")) == NULL) {
				return 0;

			} else {

				//Scrittura del nuovo file con i preferiti aggiornati
				for (j = 0; j < i; j++) {

					fwrite(&preferiti[j], sizeof(ricetta), 1, filePreferiti);

				}

				fclose(filePreferiti);

				printf("\nLa Ricetta e' stata cancellata.\n");
				return 1;
			}



		}

	}

}









/**
  * Funzione che permette di visualizzare tutte le ricette preferite
 * nell'ordine in cui sono state inserite.
 *
 */
int visualizza_preferiti(ricetta ricette[]) {

	FILE *filePreferiti;

	if ((filePreferiti = fopen("Preferiti.sf", "rb")) == NULL)
		return 0;
	else {

		ricetta ric;
		int i = 0;

		printf("\nLe Ricette poste nella lista dei preferiti sono:\n");

		while (!feof(filePreferiti)) {

			if (fread(&ric, sizeof(ricetta), 1, filePreferiti) > 0) {
				printf("%5d - %30s \t| frequenza: %5d\n", i, ricette[ric.ID_Ricetta].Nome,
						ricette[ric.ID_Ricetta].Frequenza);
				i++;
			}

		}

		fclose(filePreferiti);
		return 1;
	}

}










/**
 * Funzione che gestisce il menu riguardante tutte le opzioni
 * relative alle ricette preferite.
 * Chiede all'utente di fare una scelta e richiama le opportune funzioni
 * per svolgere quel determinato compito.
 *
 * @pre il vettore di ricette deve essere inizializzato.
 * @pre la lunghezza del vettore di ricette deve corrispondere con
 * la reale lunghezza del vettore.
 */
int scelta_opzioni_preferiti(ricetta ricette[], int lunghezzaVettoreRicette) {

	int numScelta;

	do {

		//pulisco lo schermo
		system("cls");

		printf("\nGESTIONE DEI PREFERITI\n");

		numScelta = fai_scelta(MENU_GESTISCI_PREFERTI);

		switch (numScelta) {

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

		if(numScelta != 0 || numScelta > 3) {
			char c[LUNGHEZZA_STRINGA];
			printf("\nPremi per continuare....");
			fgets(c,LUNGHEZZA_STRINGA,stdin);
		}

	} while (numScelta != 0);

	return 0;

}

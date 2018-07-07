/**
 *  @file 	   Caricamento_Vettori_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Caricamento_Vettori_Tools.h.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */

#include "Tipi_Dato.h"
#include <string.h>
#include <time.h>




/**
 * Funzione che gestisce il file di configurazione: lo apre,se esiste, e carica
 * le impostazioni.
 * Se non esiste lo crea e imposta la configurazione predefinita.
 *
 */
int Carica_Configurazione() {
	FILE *file;

	if ((file = fopen("src/Config.txt", "r+")) == NULL) {
																//In caso di errore, apre il file in scrittura (lo crea)
		if((file = fopen("src/Config.txt", "w")) == NULL) return 0;
		else{
			limite_spesa = SOGLIA_SPESA;											//stabilisce la soglia e la scrive sul file
			fprintf(file,"%d ",limite_spesa);
		}
	} else 	fscanf(file,"%d ",&limite_spesa);								//lettura della soglia da file

	fclose(file);

	return 1;

}







/**
 * La funzione apre il file di alimenti(Alimenti.sf) per calcolare
 * il numero di alimenti che ne sono stati memorizzati all'interno.
 * La funzione legge le dimensioni del file e le divide per le dimensioni
 * di una singola struct Alimenti.
 *
 * @warning il file Alimenti.sf deve avere all'interno la memorizzazione di
 * struct alimenti, altrimenti la lettura del numero di alimenti
 * sara' inesatta.
 */
int Get_Lunghezza_File_Alimenti(){

	FILE *file;

	if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
		return 0;
	} else {
		//mi posiziono alla fine del file
		fseek(file,0,SEEK_END);

		//divido il numero di byte del file (ftell) per la dimensione di un alimento
		return (int)(ftell(file)/sizeof(alimento));
		fclose(file);
	}
}







/**
 * La funzione apre il file di ricette(Ricette.sf) per calcolare
 * il numero di ricette che ne sono stati memorizzati all'interno.
 * La funzione legge le dimensioni del file e le divide per le dimensioni
 * di una singola struct Alimenti.
 *
 * @warning il file Ricette.sf deve avere all'interno la memorizzazione di
 * struct ricette, altrimenti la lettura del numero di ricette
 * sara' inesatta.
 */
int Get_Lunghezza_File_Ricette(){

	FILE *file;

	if ((file = fopen("src/Ricette.sf", "rb")) == NULL) {
		return 0;
	} else {
		//mi posiziono alla fine del file
		fseek(file,0,SEEK_END);

		//divido il numero di byte del file (ftell) per la dimensione di una ricetta
		return (int)(ftell(file)/sizeof(ricetta));
		fclose(file);
	}
}







/**
 * La funzione apre il file di pasti(Storico_Pasti.sf) per calcolare
 * il numero di pasti che ne sono stati memorizzati all'interno.
 *
 * @warning il file Storico_Pasti.sf deve avere all'interno la memorizzazione di
 * struct pasti, altrimenti la lettura del numero di pasti
 * sara' inesatta.
 */
int Get_Lunghezza_File_Storico_Pasti(){

	FILE *file;

	if ((file = fopen("src/Storico_Pasti.sf", "rb")) == NULL) {
		return 0;
	} else {
		//mi posiziono alla fine del file
		fseek(file,0,SEEK_END);

		//divido il numero di byte del file (ftell) per la dimensione di un pasto
		return (int)(ftell(file)/sizeof(pasto));
		fclose(file);
	}
}




/**
 * Dato il vettore di ricette come parametro, la funzione apre il file di ricette(Ricette.sf)
 * e carica tutte le ricette dal file al vettore.
 *
 * @pre ricette[] deve essere della lunghezza giusta quindi per crearlo
 * bisogna necessariamente richiamare la funzione Get_Lunghezza_File_Ricette
 * prima di richiamare questa funzione.
 */
int Carica_Ricette(ricetta ricette[]){

	FILE *file;
	int i = 0;

	if ((file = fopen("src/Ricette.sf", "rb")) == NULL) {
		return 0;
	} else {

		while (!feof(file)) {
			if(fread(&ricette[i], sizeof(ricetta), 1, file) > 0) i++;
		}

		if(i != 0) return 1;
		else return 0;
		fclose(file);
	}
}






/**
 * Dato il vettore di alimenti, la funzione apre il file di alimenti(Alimenti.sf)
 * e carica tutti gli alimenti dal file al vettore.
 *
 * @pre alimenti[] deve essere della lunghezza giusta quindi per crearlo
 * bisogna necessariamente richiamare la funzione Get_Lunghezza_File_Alimenti
 * prima di richiamare questa funzione.
 */
int Carica_Alimenti(alimento alimenti[]){

	FILE *file;
	int i = 0;

	if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
		return 0;
	} else {

		while (!feof(file)) {
			if(fread(&alimenti[i], sizeof(alimento), 1, file) > 0) i++;
		}

		if(i != 0) return 1;
		else return 0;
		fclose(file);
	}
}

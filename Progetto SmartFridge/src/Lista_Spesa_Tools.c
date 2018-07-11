/**
 *  @file 	   Lista_Spesa_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Lista_Spesa_Tools.h
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */








#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include <string.h>
#include <time.h>
#include "Data_Tools.h"







/**
 * Dato il vettore di alimenti, la funzione leggera tutti gli alimenti
 * presenti in frigo e scrivera' sul file (Lista_Spesa.sf)
 * le informazioni relative a quelli aventi una quantita'
 * inferiore alla soglia minima stabilta.
 *
 * @pre il vettore degli alimenti deve essere pieno o inizializzato.
 *
 * @warning la lunghezza del vettore deve essere la lunghezza effettiva
 * in quanto una discordanza potrebbe causare una lettura di porzioni
 * di memoria non allocate.
 */
int genera_lista_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti) {


	FILE *fileSpesa;
	int i, quantita = 0;
	int flag=false;

	if ((fileSpesa = fopen("Lista_Spesa.sf", "wb+")) == NULL) return 0;
	else {

		elemento_spesa elemento;

		printf("\nGli Alimenti che si trovano sotto la soglia prevista, sono:\n");

		for(i=0;i<lunghezzaVettoreAlimenti;i++) {

			quantita=get_quantita(alimenti[i]);


			if (quantita < limite_spesa && alimenti[i].Visibilita == true) {
				flag=true;
				elemento.Quantita = quantita;
				elemento.ID_Alimento = alimenti[i].ID_Alimento;

				elemento.Data_Ora.Giorno=get_data('D');
				elemento.Data_Ora.Mese=get_data('M');
				elemento.Data_Ora.Anno=get_data('Y');

				fwrite(&elemento, sizeof(elemento_spesa), 1, fileSpesa);
				printf("%3d - %25s \t| quantità: %3d \t| Id: %3d\n", i, alimenti[i].Nome,
						elemento.Quantita, elemento.ID_Alimento);
			}
		}

		fclose(fileSpesa);
	}

	if(flag==false){
		printf("\n\nNon ci sono elementi sotto la soglia!\n\n");
		return 0;
	}
	return 1;

}






/**
 * Funzione che legge il file (Lista_Spesa.sf) e visualizza l'ultima lista generata, se presente.
 *
 */
int visualizza_lista_spesa(alimento alimenti[]) {

	FILE *fileSpesa;
	boolean flag=false;


	if ((fileSpesa = fopen("Lista_Spesa.sf", "rb")) == NULL) return 0;
	else {

		elemento_spesa elemento;
		int i = 0;

		printf("\nGli alimenti sotto la soglia prevista nella scorsa lista generata erano:\n");

		while (!feof(fileSpesa)) {

			if(fread(&elemento, sizeof(elemento_spesa), 1, fileSpesa) > 0){
				flag=true;
				printf("%d - %s \t| quantità: %d \t| Id: %d\n", i, alimenti[elemento.ID_Alimento].Nome,
						elemento.Quantita, elemento.ID_Alimento);
				i++;
			}
		}

		fclose(fileSpesa);
	}

	if(flag==false)
		printf("\n\nNon e' presente nessuna lista della spesa precedente!\n\n");

	return 1;

}








/**
 * Funzione che permette di modificare la quantita' minima degli alimenti
 * in base alla quale viene generata la lista, e salvarla sul file di configurazione (Config.txt).
 *
 * @pre In assenza di modifica lo soglia prevista e' quella di preimpostata.
 */
int modifica_soglia_spesa() {

	FILE *file;
	char scelta[LUNGHEZZA_STRINGA];

	printf("\nL'attuale soglia stabilita è : %d\n", limite_spesa);
	printf("Inserici la nuova soglia limite : ");


	do {
		//Stampo il messaggio passato come parametro
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);

		//Svuoto il buffer nel caso venga inserita una stringa piu grande della lunghezza massima
		fflush(stdin);

		//Se la stringa presa in input non e' un numero scrivo un messaggio di errore
		//altrimenti la funzione ritorna il numero preso in input convertito in intero
		if (!is_number(scelta))
			printf("\nSoglia errata, riprova: ");
		else
			limite_spesa = to_number(scelta);

		//continuo a chiedere in input la scelta fino a che non e' valida
	} while (!is_number(scelta));


	if ((file = fopen("Config.txt", "w")) == NULL) return 0;
	else {
		fprintf(file, "%d ", limite_spesa);
		printf("\nNuova soglia limite impostata \n");
	}

	fclose(file);
	return 1;
}






/**
 * Funzione che gestisce il menu riguardante tutte le opzioni
 * relative alla lsta della spesa.
 * Chiede all'utente di fare una scelta e richiama le opportune funzioni
 * per svolgere quel determinato compito.
 *
 * @pre il vettore degli alimenti deve essere pieno o inizializzato.
 *
 * @warning la lunghezza del vettore deve essere la lunghezza effettiva
 * in quanto una discordanza potrebbe causare una lettura di porzioni
 * di memoria non allocate.
 *
 */
int scelte_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti){

	int numScelta;

	do{
		//pulisco lo schermo
		system("cls");

		printf("\nSUGGERIMENTO DELLA SPESA\n");

		numScelta=fai_scelta(MENU_SUGGERIMENTO_SPESA);

		switch(numScelta){
			case 1:
				if(!genera_lista_spesa(alimenti, lunghezzaVettoreAlimenti)) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");
				break;
			case 2:
				if(!visualizza_lista_spesa(alimenti)) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");
				break;
			case 3:
				if(!modifica_soglia_spesa()) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");\
				break;
			case 0:
				//case di uscita dal sottomenu
				break;
			default:
				printf("Scelta errata! Riprova!\n");
		}

		if(numScelta != 0) {
			char c[LUNGHEZZA_STRINGA];
			printf("\nPremi per continuare....");
			fgets(c,LUNGHEZZA_STRINGA,stdin);
		}


	}while(numScelta!=0);

	return 0;
}













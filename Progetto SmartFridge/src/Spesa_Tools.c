/*
 * Spesa_Tools.c
 *
 *  Created on: 17 mag 2018
 *      Author: giutu
 */

#include "Tipi_Dato.h"
#include <string.h>
#include <time.h>

void Genera_Lista_Spesa() {

	FILE *file;
	FILE *file_spesa;
	int i,j=0, quantita = 0;

	if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file!\n");

	} else if ((file_spesa = fopen("src/Lista_Spesa.sf", "wb+")) == NULL) {
		printf("Errore nell'apertura del file LISTA!\n");

	} else {
		alimento alimento;
		elemento_spesa elemento;

		printf("\nGli Alimenti che si trovano sotto la soglia prevista, sono:\n");

		while (!feof(file)) {
			fread(&alimento, sizeof(alimento), 1, file);

			for (i = 0; i < LUNGHEZZA_VET_SCADENZE; i++) {//calcolo delle quantità, solo che non è inizializzato tutto a 0
				quantita += alimento.Scadenze[i].Quantita;
			}


			if (quantita < SOGLIA_SPESA) {

				elemento.Quantita = quantita;
				elemento.ID_Alimento = alimento.ID_Alimento;
				strcpy(elemento.Nome, alimento.Nome);
				//elemento.Data_Ora = 			//aggiungere con date_Time,

				fwrite(&elemento, sizeof(elemento_spesa), 1, file_spesa);
				printf("%d - %s \t| quantità: %d \t| Id: %d\n", j, elemento.Nome,
						elemento.Quantita, elemento.ID_Alimento);
				j++;
			}

		}

		fclose(file_spesa);
		fclose(file);
	}

}

//Sono commentate le righe antecedenti l'introduzione di "Nome" nella Struct "elemeto_spesa", in caso di cambio
void Visualizza_Lista_Spesa() {

	//FILE *file;
	FILE *file_spesa;

	/*if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
	 printf("Errore nell'apertura del file!\n");

	 } else */

	if ((file_spesa = fopen("src/Lista_Spesa.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file LISTA!\n");

	} else {
		//alimento alimento;
		elemento_spesa elemento;
		int i = 0;

		printf("\nGli alimenti sotto la soglia prevista nella scorsa lista generata erano:\n");		//Qui l'ultimo viene visualizzato 2 volte!?

		while (!feof(file_spesa)) {

			//bisogna visualizzare anche la data e l'ora della generazione
			fread(&elemento, sizeof(elemento_spesa), 1, file_spesa);
			printf("%d - %s \t| quantità: %d \t| Id: %d\n", i, elemento.Nome,
					elemento.Quantita, elemento.ID_Alimento);
			i++;

		}

		fclose(file_spesa);
		//fclose(file);
	}

}

//E impostato al momento solo sulla prima riga dato che l'unico parametro sino ad ora visto è la soglia degli alimenti
void Modifica_Soglia_Spesa() {

	FILE *file;
	char scelta[LUNGHEZZA_STRINGA];		//penso che questa lunghezza sia un po eccessiva e si può introdurre una lunghezza minore per questi controlli

	printf("\nL'attuale soglia stabilita è : %d\n", limite_spesa);
	printf("Inserici la nuova soglia limite : ");


	do {
			//Stampo il messaggio passato come parametro
			fgets(scelta, LUNGHEZZA_STRINGA, stdin);

			//Svuoto il buffer nel caso venga inserita una stringa piu grande della lunghezza massima
			fflush(stdin);

			//Se la stringa presa in input non e' un numero scrivo un messaggio di errore
			//altrimenti la funzione ritorna il numero preso in input convertito in intero
			if (!isNumber(scelta))
				printf("\nSoglia errata, riprova: ");
			else
				limite_spesa = toNumber(scelta);

			//continuo a chiedere in input la scelta fino a che non e' valida
		} while (!isNumber(scelta));


	if ((file = fopen("src/Config.txt", "w")) == NULL) {
		printf("Errore nell'apertura del file!\n");

	} else {
		fprintf(file, "%d ", limite_spesa);
		printf("\nNuova soglia limite impostata \n");
	}

	fclose(file);
}












/*
 * Spesa_Tools.c
 *
 *  Created on: 17 mag 2018
 *      Author: giutu
 */
#include "Tipi_Dato.h"
#include <string.h>
#include <time.h>
//#include "Messaggi_Menu.h"

int Genera_Lista_Spesa() {

	FILE *file_alimenti;
	FILE *file_spesa;
	int i,j=0, quantita = 0;

	if ((file_alimenti = fopen("src/Alimenti.sf", "rb")) == NULL) return 0;
	else if ((file_spesa = fopen("src/Lista_Spesa.sf", "wb+")) == NULL) return 0;
	else {

		alimento alimento;
		elemento_spesa elemento;

		printf("\nGli Alimenti che si trovano sotto la soglia prevista, sono:\n");

		while (!feof(file_alimenti)) {
			fread(&alimento, sizeof(alimento), 1, file_alimenti);

			quantita=0;

			for (i = 0; i < LUNGHEZZA_VET_SCADENZE; i++) {//calcolo delle quantità, solo che non è inizializzato tutto a 0
				quantita += alimento.Scadenze[i].Quantita;
				//printf("\nQuantita: %d\n",alimento.Scadenze[i].Quantita);
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
		fclose(file_alimenti);
		return 1;
	}

}






//Sono commentate le righe antecedenti l'introduzione di "Nome" nella Struct "elemeto_spesa", in caso di cambio
int Visualizza_Lista_Spesa() {

	FILE *file_spesa;


	if ((file_spesa = fopen("src/Lista_Spesa.sf", "rb")) == NULL) return 0;
	else {

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
		return 1;
	}

}








//E impostato al momento solo sulla prima riga dato che l'unico parametro sino ad ora visto è la soglia degli alimenti
int Modifica_Soglia_Spesa() {

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


	if ((file = fopen("src/Config.txt", "w")) == NULL) return 0;
	else {
		fprintf(file, "%d ", limite_spesa);
		printf("\nNuova soglia limite impostata \n");
	}

	fclose(file);
	return 1;
}




int Scelte_Spesa(){

	int NumScelta;

	do{
		NumScelta=FaiScelta(MenuSuggerimentoSpesa);

		switch(NumScelta){
			case 1:
				if(!Genera_Lista_Spesa()) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");
				break;
			case 2:
				if(!Visualizza_Lista_Spesa()) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");
				break;
			case 3:
				if(!Modifica_Soglia_Spesa()) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");\
				break;
			case 0:
				//case di uscita dal sottomenu
				break;
			default:
				printf("Scelta errata! Riprova!\n");
		}

	}while(NumScelta!=0);

	return 0;
}












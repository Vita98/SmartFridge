/*
 * Spesa_Tools.c
 *
 *  Created on: 17 mag 2018
 *      Author: giutu
 */
#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include <string.h>
#include <time.h>
#include "Data_Tools.h"
















int Genera_Lista_Spesa(alimento alimenti[],int n) {


	FILE *file_spesa;
	int i, quantita = 0;

	if ((file_spesa = fopen("src/Lista_Spesa.sf", "wb+")) == NULL) return 0;
	else {

		elemento_spesa elemento;

		printf("\nGli Alimenti che si trovano sotto la soglia prevista, sono:\n");

		for(i=0;i<n;i++) {

			quantita=getQuantita(alimenti[i]);


			if (quantita < limite_spesa) {
				elemento.Quantita = quantita;
				elemento.ID_Alimento = alimenti[i].ID_Alimento;
				strcpy(elemento.Nome, alimenti[i].Nome);

				elemento.Data_Ora.Giorno=getData('D');
				elemento.Data_Ora.Mese=getData('M');
				elemento.Data_Ora.Anno=getData('Y');

				fwrite(&elemento, sizeof(elemento_spesa), 1, file_spesa);
				printf("%d - %s \t| quantità: %d \t| Id: %d\n", i, elemento.Nome,
						elemento.Quantita, elemento.ID_Alimento);
			}
		}


		fclose(file_spesa);
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




int Scelte_Spesa(alimento alimenti[],int n){

	int NumScelta;

	do{
		NumScelta=FaiScelta(MenuSuggerimentoSpesa);

		switch(NumScelta){
			case 1:
				if(!Genera_Lista_Spesa(alimenti, n)) printf("Si e' verificato un errore nell'apertura dei file! Controllarli!\n");
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













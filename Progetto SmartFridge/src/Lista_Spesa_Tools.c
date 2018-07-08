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
	}
	return 1;

}







int visualizza_lista_spesa(alimento alimenti[]) {

	FILE *fileSpesa;
	boolean flag=false;


	if ((fileSpesa = fopen("Lista_Spesa.sf", "rb")) == NULL) return 0;
	else {

		elemento_spesa elemento;
		int i = 0;

		printf("\nGli alimenti sotto la soglia prevista nella scorsa lista generata erano:\n");

		while (!feof(fileSpesa)) {

			//bisogna visualizzare anche la data e l'ora della generazione
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








//E impostato al momento solo sulla prima riga dato che l'unico parametro sino ad ora visto è la soglia degli alimenti
int modifica_soglia_spesa() {

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




int scelte_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti){

	int NumScelta;

	do{
		NumScelta=fai_scelta(MENU_SUGGERIMENTO_SPESA);

		switch(NumScelta){
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

	}while(NumScelta!=0);

	return 0;
}













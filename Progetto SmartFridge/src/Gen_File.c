/*
 * Gen_File.c
 *
 *  Created on: 17 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <string.h>
#include <time.h>

void Generazione_Alimenti() {

	FILE *file;

	if ((file = fopen("src/Alimenti.sf", "wb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
	} else {
		srand(time(NULL));
		int i;
		alimento alimento;
		for (i = 0; i < 10; i++) {
			fflush(stdin);

			printf("Nome: ");
			gets(alimento.Nome);

			printf("\nKcal Per pezzo: ");
			scanf("%lf", &alimento.Kcal_Pezzo);

			printf("\nPeso: ");
			scanf("%d", &alimento.Peso);

			printf("\nUtilizzo: ");
			scanf("%d", &alimento.Utilizzo);

			int visibil;
			printf("\nVisibilita: ");
			scanf("%d", &visibil);

			alimento.Visibilita = (visibil == 1) ? true : false;

			int NumeroScadenze;
			printf("\nQuante Scadenze?: ");
			scanf("%d", &NumeroScadenze);

			int j;
			for (j = 0; j < LUNGHEZZA_VET_SCADENZE; j++) {

				if(j<NumeroScadenze){
					printf("\nQuantita: ");
					scanf("%d", &alimento.Scadenze[j].Quantita);

					alimento.Scadenze[j].Data_Scadenza.Anno = 2018 + (rand() % 10);
					alimento.Scadenze[j].Data_Scadenza.Mese = (rand() % 12) + 1;
					alimento.Scadenze[j].Data_Scadenza.Giorno = (rand() % 31) + 1;

				}else{
					alimento.Scadenze[j].Quantita=0;
					alimento.Scadenze[j].Data_Scadenza.Anno = 0;
					alimento.Scadenze[j].Data_Scadenza.Mese = 0;
					alimento.Scadenze[j].Data_Scadenza.Giorno = 0;
				}


			}

			alimento.ID_Alimento = i;
			fwrite(&alimento, sizeof(alimento), 1, file);
		}

		fclose(file);
	}

}

void Read_Alimenti() {

	FILE *file;

	if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
	} else {
		alimento pasta;

		while (!feof(file)) {
			fread(&pasta, sizeof(alimento), 1, file);
			printf("Nome: %s Anno %d Id: %d\n", pasta.Nome,
					pasta.Scadenze[0].Data_Scadenza.Mese, pasta.ID_Alimento);
		}

		fclose(file);
	}

}

void Genera_Ricette() {

	FILE *file;

	if ((file = fopen("src/Ricette.sf", "wb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
	} else {

		ricetta ricc;
		int i;

		for (i = 0; i < 4; i++) {
			fflush(stdin);
			printf("\nNome ricetta: ");
			gets(ricc.Nome);

			ricc.ID_Ricetta = i;

			printf("\nKcal Per porzione: ");
			scanf("%lf", &ricc.Kcal_Porzione);


			ricc.Frequenza = 0;

			int visibil;
			printf("\nVisibilita: ");
			scanf("%d", &visibil);

			ricc.Visibilita = (visibil == 1) ? true : false;

			printf("\nNumero alimenti che la formano: ");
			int numeroAlim;
			scanf("%d", &numeroAlim);

			int j;
			for (j = 0; j < NUMERO_MAX_ALIMENTI; j++) {
				if(j<numeroAlim){
					printf("\nId Alimento: ");
					scanf("%d", &ricc.Alimenti_Quantita[0][j]);

					printf("\nQuantita alimento: ");
					scanf("%d", &ricc.Alimenti_Quantita[1][j]);
				}else{
					ricc.Alimenti_Quantita[0][j]=-1;
					ricc.Alimenti_Quantita[1][j]=0;
				}
			}
			fwrite(&ricc, sizeof(ricetta), 1, file);

		}
	}

	fclose(file);

}

void Visualizza_RicetteF() {
	FILE *file;

	if ((file = fopen("src/Ricette.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
	} else {
		ricetta ricc;

		while (!feof(file)) {
			fread(&ricc, sizeof(ricetta), 1, file);
			printf("Nome: %s Alimento 1 Id %d Id: %d\n", ricc.Nome,
					ricc.Alimenti_Quantita[0][1], ricc.ID_Ricetta);
		}

		fclose(file);
	}
}



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












//Leggo il file solo per sapere la lunghezza, da poter poi dichiarare il vettore alimenti, una BOIATA ma per ora va così
//bisognerà aggiungere poi un TOT in più per le possibili AGGIUNTE, altrimenti bisogna dichiararlo tutte le volte da 0 il vettore
int Get_Lunghezza_File_Alimenti(){

	FILE *file;

	if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
		return 0;
	} else {
		fseek(file,0,SEEK_END);
		return (int)(ftell(file)/sizeof(alimento));
		fclose(file);
	}
}




//Leggo il file solo per sapere la lunghezza, da poter poi dichiarare il vettore alimenti, una BOIATA ma per ora va così
//bisognerà aggiungere poi un TOT in più per le possibili AGGIUNTE, altrimenti bisogna dichiararlo tutte le volte da 0 il vettore
int Get_Lunghezza_File_Ricette(){

	FILE *file;

	if ((file = fopen("src/Ricette.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
		return 0;
	} else {
		fseek(file,0,SEEK_END);
		return (int)(ftell(file)/sizeof(ricetta));
		fclose(file);
	}
}




//Leggo il file solo per sapere la lunghezza, da poter poi dichiarare il vettore alimenti, una BOIATA ma per ora va così
//bisognerà aggiungere poi un TOT in più per le possibili AGGIUNTE, altrimenti bisogna dichiararlo tutte le volte da 0 il vettore
int Get_Lunghezza_File_Storico_Pasti(){

	FILE *file;

	if ((file = fopen("src/Storico_Pasti.sf", "rb")) == NULL) {
		printf("Errore nell'apertura del file!\n");
		return 0;
	} else {
		fseek(file,0,SEEK_END);
		return (int)(ftell(file)/sizeof(pasto));
		fclose(file);
	}
}




//Legge il file e carica il vettore che viene passato dal MAIN
//Gli errori vedi se non li trovi ahah, sono stanco
int Carica_Ricette(ricetta ricette[]){

	FILE *file;
	int i = 0;

		if ((file = fopen("src/Ricette.sf", "rb")) == NULL) {
			printf("Errore nell'apertura del file!\n");
			return 0;
		} else {

			while (!feof(file)) {
				fread(&ricette[i], sizeof(ricetta), 1, file);
				i++;
			}

			return 1;
			fclose(file);
		}
}





//Legge il file e carica il vettore che viene passato dal MAIN
//Gli errori vedi se non li trovi ahah, sono stanco
int Carica_Alimenti(alimento alimenti[]){

	FILE *file;
	int i = 0;

		if ((file = fopen("src/Alimenti.sf", "rb")) == NULL) {
			printf("Errore nell'apertura del file!\n");
			return 0;
		} else {

			while (!feof(file)) {
				fread(&alimenti[i], sizeof(alimento), 1, file);
				i++;
			}

			return 1;
			fclose(file);
		}
}


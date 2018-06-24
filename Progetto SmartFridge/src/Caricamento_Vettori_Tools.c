 /*
 * Caricamento_Vettori_Tools.c
 *
 *  Created on: 22 giu 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <string.h>
#include <time.h>



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
			return 0;
		} else {

			while (!feof(file)) {
				if(fread(&ricette[i], sizeof(ricetta), 1, file) > 0) i++;
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
			return 0;
		} else {

			while (!feof(file)) {
				if(fread(&alimenti[i], sizeof(alimento), 1, file) > 0) i++;
			}

			return 1;
			fclose(file);
		}
}

/*
 * Gen_File.c
 *
 *  Created on: 17 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <string.h>


void Generazione_Alimenti(){

	FILE *file;

	if((file=fopen("src/Alimenti.sf","wb")) == NULL){
		printf("Errore nell'apertura del file!\n");
	}else{
		scadenza Scadenze[LUNGHEZZA_VET_SCADENZE];
		Scadenze[0].Quantita=1;
		Scadenze[0].Data_Scadenza.Anno=2019;
		Scadenze[0].Data_Scadenza.Mese=9;
		Scadenze[0].Data_Scadenza.Giorno=19;

		alimento pasta;
		strcpy(pasta.Nome,"Pasta");
		pasta.Kcal_Pezzo=200.0;
		pasta.Peso=500;
		*pasta.Scadenze=*Scadenze;
		pasta.Utilizzo=0;
		pasta.Visibilita=true;

		fwrite(&pasta,sizeof(alimento),1,file);

		fclose(file);
	}

}


void Read_Alimenti(){

	FILE *file;

	if((file=fopen("src/Alimenti.sf","rb")) == NULL){
		printf("Errore nell'apertura del file!\n");
	}else{
		alimento pasta;

		fread(&pasta,sizeof(alimento),1,file);

		printf("Nome: %s\n Anno %d ",pasta.Nome,pasta.Scadenze[0].Data_Scadenza.Mese);

		fclose(file);
	}

}

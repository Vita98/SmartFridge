/*
 * Gen_File.c
 *
 *  Created on: 17 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <string.h>
#include <time.h>


void Generazione_Alimenti(){

	FILE *file;

	if((file=fopen("src/Alimenti.sf","ab")) == NULL){
		printf("Errore nell'apertura del file!\n");
	}else{
		srand(time(NULL));
		int i;
		alimento alimento;
		for(i=0;i<10;i++){
			fflush(stdin);

			printf("Nome: ");
			gets(alimento.Nome);

			printf("\nKcal Per pezzo: ");
			scanf("%lf",&alimento.Kcal_Pezzo);

			printf("\nPeso: ");
			scanf("%d",&alimento.Peso);


			printf("\nUtilizzo: ");
			scanf("%d",&alimento.Utilizzo);


			int visibil;
			printf("\nVisibilita: ");
			scanf("%d",&visibil);

			alimento.Visibilita= (visibil==1)? true:false;


			int NumeroScadenze;
			printf("\nQuante Scadenze?: ");
			scanf("%d",&NumeroScadenze);


			int j;
			for(j=0;j<NumeroScadenze;j++){
				printf("\nQuantita: ");
				scanf("%d",&alimento.Scadenze[j].Quantita);


				alimento.Scadenze[j].Data_Scadenza.Anno=2018+(rand()%10);
				alimento.Scadenze[j].Data_Scadenza.Mese=(rand()%12)+1;
				alimento.Scadenze[j].Data_Scadenza.Giorno=(rand()%31)+1;

			}

			alimento.ID_Alimento=i;
			fwrite(&alimento,sizeof(alimento),1,file);
		}



		fclose(file);
	}

}


void Read_Alimenti(){

	FILE *file;

	if((file=fopen("src/Alimenti.sf","rb")) == NULL){
		printf("Errore nell'apertura del file!\n");
	}else{
		alimento pasta;

		while(!feof(file)){
			fread(&pasta,sizeof(alimento),1,file);
			printf("Nome: %s Anno %d Id: %d\n",pasta.Nome,pasta.Scadenze[0].Data_Scadenza.Mese,pasta.ID_Alimento);
		}

		fclose(file);
	}

}






void Genera_Ricette(){

	FILE *file;

	if((file=fopen("src/Ricette.sf","wb")) == NULL){
		printf("Errore nell'apertura del file!\n");
	}else{

		ricetta ricc;
		int i;

		for(i=0;i<4;i++){
			fflush(stdin);
			printf("\nNome ricetta: ");
			gets(ricc.Nome);

			ricc.ID_Ricetta=i;

			printf("\nKcal Per porzione: ");
			scanf("%lf",&ricc.Kcal_Porzione);

			ricc.Frequenza=0;

			int visibil;
			printf("\nVisibilita: ");
			scanf("%d",&visibil);

			ricc.Visibilita= (visibil==1)? true:false;

			printf("\nNumero alimenti che la formano: ");
			int numeroAlim;
			scanf("%d",&numeroAlim);

			int j;
			for(j=0;j<numeroAlim;j++){
				printf("\nId Alimento: ");
				scanf("%d",&ricc.Alimenti_Quantita[0][j]);

				printf("\nQuantita alimento: ");
				scanf("%d",&ricc.Alimenti_Quantita[1][j]);
			}
			fwrite(&ricc,sizeof(ricetta),1,file);

		}
	}

	fclose(file);

}




void Visualizza_Ricette(){
	FILE *file;

		if((file=fopen("src/Ricette.sf","rb")) == NULL){
			printf("Errore nell'apertura del file!\n");
		}else{
			ricetta ricc;

			while(!feof(file)){
				fread(&ricc,sizeof(ricetta),1,file);
				printf("Nome: %s Alimento 1 Id %d Id: %d\n",ricc.Nome,ricc.Alimenti_Quantita[0][1],ricc.ID_Ricetta);
			}

			fclose(file);
		}
}

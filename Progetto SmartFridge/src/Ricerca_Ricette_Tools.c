/*
 * Ricerca_Ricette_Tools.c
 *
 *  Created on: 09 giu 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include <string.h>





boolean isParametroRicerca(int vettore[],int lunghezzaVettore,int valore){

	int i;
	for(i=0;i<lunghezzaVettore-1;i++){
		if(vettore[lunghezzaVettore-1] == vettore[i]){
			return true;
		}
	}
	return false;

}






int* getRicettePerAlimenti(alimento alimenti[],int lunghezza_vettore_alimenti,int VettoreIndiciAlimenti[],int lunghezza_vettore_indici,ricetta ricette[],int lunghezza_vettore_ricette,int *NumeroRicetteTrovate){

	int i,j,k;
	int contatore;
	int IndiciRicetteOK[lunghezza_vettore_ricette];
	int IndiceVettoreRicetteOK=0;

	//for che scorre il vettore di ricette
	for(i=0;i<lunghezza_vettore_ricette;i++){
		contatore=0;
		//for che scorre gli alimenti della ricetta
		for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
			//for che scorre gli alimenti da cercare nella ricetta
			for(k=0;k<lunghezza_vettore_indici;k++){
				//controllo se l'alimento da cercare e' presente nella ricetta

				//creo i vettori che conterranno le sringhe derivanti l'esplosione dei nomi degli alimenti
				char StringheEsploseAlimentoRicetta[LUNGHEZZA_STRINGA/2][LUNGHEZZA_STRINGA];
				char StringheEsploseAlimento[LUNGHEZZA_STRINGA/2][LUNGHEZZA_STRINGA];

				//esplodo i nomi delle ricette per avere un matching piu accurato
				int quantitaStringaEsplosaAlimentoRicetta=explodeString(alimenti[ricette[i].Alimenti_Quantita[0][j]].Nome,StringheEsploseAlimentoRicetta);
				int quantitaStringaEsplosaAlimento=explodeString(alimenti[VettoreIndiciAlimenti[k]].Nome,StringheEsploseAlimento);


				int f,g;
				boolean flag=false;

				//cicli for che confrontano tutte le stringhe derivanti l'esplosione dei due nomi di alimenti tra di loro
				for(f=0;f<quantitaStringaEsplosaAlimento;f++){

					removeFirstLastSpace(StringheEsploseAlimento[f],StringheEsploseAlimento[f],LUNGHEZZA_STRINGA);
					toLowerString(StringheEsploseAlimento[f],StringheEsploseAlimento[f]);

					for(g=0;g<quantitaStringaEsplosaAlimentoRicetta;g++){

						removeFirstLastSpace(StringheEsploseAlimentoRicetta[g],StringheEsploseAlimentoRicetta[g],LUNGHEZZA_STRINGA);

						toLowerString(StringheEsploseAlimentoRicetta[g],StringheEsploseAlimentoRicetta[g]);

						if(strcmp(StringheEsploseAlimento[f],StringheEsploseAlimentoRicetta[g]) == 0){
							flag=true;
							contatore++;
							break;
						}

					}
					if(flag==true) break;
				}
			}

			//se il numero di matching effettuati e' uguale al numero di alimenti inseriti dall'utente
			//vuol dire che la ricetta puo essere preparata con quelli ingredienti
			if(contatore==lunghezza_vettore_indici){
				//salvo l'indice della ricetta nel vettore IndiceRicetteOK
				IndiciRicetteOK[IndiceVettoreRicetteOK]=i;
				IndiceVettoreRicetteOK++;
				break;
			}
		}
	}


	//salvo le ricette trovate nel vettore e passo il suo indirizzo nel punatore
	//passato come parametro che ha la funzionalita anche di valore di ritorno
	int *c=(int*) calloc(IndiceVettoreRicetteOK-1,sizeof(int));
	for(i=0;i<IndiceVettoreRicetteOK;i++){
		c[i]=IndiciRicetteOK[i];
	}
	(*NumeroRicetteTrovate)=IndiceVettoreRicetteOK;
	return c;

}







int Ricerca_Ricette_Per_Alimenti(ricetta ricette[],int lunghezza_vettore_ricette,alimento alimenti[],int lunghezza_vettore_alimenti){

	boolean flag;
	//alimento alimentiRicerca[];

	//creo un vettore che conterra gli indici degli alimenti chiesti all'utente
	int VettoreIndici[lunghezza_vettore_alimenti];
	int IndiceVettoreIndici=0;

	int indice=0,i;
	char AlimentoInput[LUNGHEZZA_STRINGA];

	printf("\n\nRicerca delle ricette in base agli alimenti\n%s\n",STRINGASTERISCHI);

	do{
		flag=false;

		printf("Inserisci il nome dell'alimento numero %d:",(indice+1));
		fgets(AlimentoInput,LUNGHEZZA_STRINGA,stdin);

		//controllo se l'alimento inserito esiste nel vettore alimenti
		if((VettoreIndici[IndiceVettoreIndici++]=getAlimento(alimenti,lunghezza_vettore_alimenti,AlimentoInput,true)) > -1){

			//se esiste nel vettore alimenti controllo se e' gia stato inserito come parametro di ricerca della ricetta
			if(isParametroRicerca(VettoreIndici,IndiceVettoreIndici,VettoreIndici[IndiceVettoreIndici-1]) == true){
				printf("\nL'alimento che stai tentando di inserire e' stato gia inserito!\n");
				IndiceVettoreIndici--;
			}else indice++;


		}else{
			printf("\nL'alimento che stai tentando di inserire non esiste!\n");
			IndiceVettoreIndici--;
		}

		if(FaiSceltaBooleana("\nVuoi cercare le ricette con altri alimenti oltre a quelli gia inseriti? ") == true) flag=true;
		else if(IndiceVettoreIndici==0) printf("\nDevi inserire almeno un alimento per cercare le ricette!\n");


	}while(flag==true || IndiceVettoreIndici==0);


	//richiamo la funzione che ricerca tutte le ricette con quei alimenti
	int NumeroRicetteTrovate=0;
	int *IndiciRicette=getRicettePerAlimenti(alimenti,lunghezza_vettore_alimenti,VettoreIndici,IndiceVettoreIndici,ricette,lunghezza_vettore_ricette,&NumeroRicetteTrovate);

	if(NumeroRicetteTrovate == 0) printf("\n\nNon e' possibile preparare nessuna ricetta con gli alimenti inseriti!\n\n");
	else{
		printf("\n\nRicette che e' possibile preparare con gli alimenti inseriti:\n");
		printf("%20s | %20s\n","Nome","Kcal per porzione");
		printf("-----------------------------------------------------\n");

		for(i=0;i<NumeroRicetteTrovate;i++){
			printf("%20s | %18.2f\n",ricette[IndiciRicette[i]].Nome,ricette[IndiciRicette[i]].Kcal_Porzione);
		}
	}


	return 1;
}


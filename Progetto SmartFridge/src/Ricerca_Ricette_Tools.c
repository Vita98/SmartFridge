/*
 * Ricerca_Ricette_Tools.c
 *
 *  Created on: 09 giu 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include <string.h>
#include "Data_Tools.h"
#include "Ricette_Tools.h"
#include "Preferiti_Tools.h"





boolean is_parametro_ricerca(int vettore[],int lunghezzaVettore,int valore){

	int i;
	for(i=0;i<lunghezzaVettore-1;i++){
		if(vettore[lunghezzaVettore-1] == vettore[i]){
			return true;
		}
	}
	return false;

}






int* get_ricette_per_alimenti(alimento alimenti[],int lunghezzaVettoreAlimenti,int vettoreIndiciAlimenti[],int lunghezzaVettoreIndici,ricetta ricette[],int lunghezzaVettoreRicette,int *numeroRicetteTrovate){

	int i,j,k;
	int contatore;
	int IndiciRicetteOK[lunghezzaVettoreRicette];
	int IndiceVettoreRicetteOK=0;

	//for che scorre il vettore di ricette
	for(i=0;i<lunghezzaVettoreRicette;i++){
		contatore=0;
		//for che scorre gli alimenti della ricetta
		for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
			//for che scorre gli alimenti da cercare nella ricetta
			for(k=0;k<lunghezzaVettoreIndici;k++){
				//controllo se l'alimento da cercare e' presente nella ricetta

				//creo i vettori che conterranno le sringhe derivanti l'esplosione dei nomi degli alimenti
				char StringheEsploseAlimentoRicetta[LUNGHEZZA_STRINGA/2][LUNGHEZZA_STRINGA];
				char StringheEsploseAlimento[LUNGHEZZA_STRINGA/2][LUNGHEZZA_STRINGA];

				//esplodo i nomi delle ricette per avere un matching piu accurato
				int quantitaStringaEsplosaAlimentoRicetta=explode_string(alimenti[ricette[i].Alimenti_Quantita[0][j]].Nome,StringheEsploseAlimentoRicetta);
				int quantitaStringaEsplosaAlimento=explode_string(alimenti[vettoreIndiciAlimenti[k]].Nome,StringheEsploseAlimento);


				int f,g;
				boolean flag=false;

				//cicli for che confrontano tutte le stringhe derivanti l'esplosione dei due nomi di alimenti tra di loro
				for(f=0;f<quantitaStringaEsplosaAlimento;f++){

					remove_first_last_space(StringheEsploseAlimento[f],StringheEsploseAlimento[f],LUNGHEZZA_STRINGA);
					to_lower_string(StringheEsploseAlimento[f],StringheEsploseAlimento[f]);

					for(g=0;g<quantitaStringaEsplosaAlimentoRicetta;g++){

						remove_first_last_space(StringheEsploseAlimentoRicetta[g],StringheEsploseAlimentoRicetta[g],LUNGHEZZA_STRINGA);

						to_lower_string(StringheEsploseAlimentoRicetta[g],StringheEsploseAlimentoRicetta[g]);

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
			if(contatore==lunghezzaVettoreIndici){
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
	(*numeroRicetteTrovate)=IndiceVettoreRicetteOK;
	return c;

}







int ricerca_ricette_per_alimenti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	boolean flag;

	//creo un vettore che conterra gli indici degli alimenti chiesti all'utente
	int vettoreIndici[lunghezzaVettoreAlimenti];
	int indiceVettoreIndici=0;

	int indice=0,i;
	char alimentoInput[LUNGHEZZA_STRINGA];

	printf("\n\nRicerca delle ricette in base agli alimenti\n%s\n",STRINGASTERISCHI);

	do{
		flag=false;

		printf("Inserisci il nome dell'alimento numero %d:",(indice+1));
		fgets(alimentoInput,LUNGHEZZA_STRINGA,stdin);

		//controllo se l'alimento inserito esiste nel vettore alimenti
		if((vettoreIndici[indiceVettoreIndici++]=get_alimento(alimenti,lunghezzaVettoreAlimenti,alimentoInput,true)) > -1){

			//se esiste nel vettore alimenti controllo se e' gia stato inserito come parametro di ricerca della ricetta
			if(is_parametro_ricerca(vettoreIndici,indiceVettoreIndici,vettoreIndici[indiceVettoreIndici-1]) == true){
				printf("\nL'alimento che stai tentando di inserire e' stato gia inserito!\n");
				indiceVettoreIndici--;
			}else indice++;


		}else{
			printf("\nL'alimento che stai tentando di inserire non esiste!\n");
			indiceVettoreIndici--;
		}

		if(fai_scelta_booleana("\nVuoi cercare le ricette con altri alimenti oltre a quelli gia inseriti? ") == true) flag=true;
		else if(indiceVettoreIndici==0) printf("\nDevi inserire almeno un alimento per cercare le ricette!\n");


	}while(flag==true || indiceVettoreIndici==0);


	//richiamo la funzione che ricerca tutte le ricette con quei alimenti
	int numeroRicetteTrovate=0;
	int *indiciRicette=get_ricette_per_alimenti(alimenti,lunghezzaVettoreAlimenti,vettoreIndici,indiceVettoreIndici,ricette,lunghezzaVettoreRicette,&numeroRicetteTrovate);

	if(numeroRicetteTrovate == 0) printf("\n\nNon e' possibile preparare nessuna ricetta con gli alimenti inseriti!\n\n");
	else{
		printf("\n\nRicette che e' possibile preparare con gli alimenti inseriti:\n");
		printf("%20s | %20s\n","Nome","Kcal per porzione");
		printf("-----------------------------------------------------\n");

		for(i=0;i<numeroRicetteTrovate;i++){
			printf("%20s | %18.2f\n",ricette[indiciRicette[i]].Nome,ricette[indiciRicette[i]].Kcal_Porzione);
		}
	}


	return 1;
}







int* get_ricette_in_scadenza(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int *numeroRicetteTrovate){

	int *vettoreRicetteScadenza = (int*) calloc(lunghezzaVettoreRicette,sizeof(int));
	int indiceVetRicetteScadenza=-1;

	int i,j,k;
	data_ora dataAttuale;
	get_data_pointer(&dataAttuale);
	boolean flag;

	for(i=0;i<lunghezzaVettoreRicette;i++){
		if(ricette[i].Visibilita == true)

		//controllo se la iesima ricetta ha la possibilita di essere preparata
		if(get_numero_porzioni_possibili_ricetta(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,i) > 0){
			flag=false;
			//vettore che scorre gli alimenti della ricetta
			//per ferificare se qualcuno e' in scadenza
			for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
				if(ricette[i].Alimenti_Quantita[1][j] != 0)
				for(k=0;k<LUNGHEZZA_VET_SCADENZE;k++){ //vettore che scorre le date di scadenza dell'alimento
					if(alimenti[ricette[i].Alimenti_Quantita[0][j]].Scadenze[k].Quantita != 0){
						int distanza=get_distanza_in_giorni(dataAttuale,alimenti[ricette[i].Alimenti_Quantita[0][j]].Scadenze[k].Data_Scadenza,0);
						if(distanza >= 0 && distanza <= DISTANZAGIORNISCADENZA ){
							indiceVetRicetteScadenza++;
							vettoreRicetteScadenza[indiceVetRicetteScadenza]=i;
							flag=true;
							break;
						}
					}
				}

				if(flag==true) break;
			}
		}
	}

	//salvo le ricette trovate nel vettore e passo il suo indirizzo nel punatore
	//passato come parametro che ha la funzionalita anche di valore di ritorno
	int *c=(int*) calloc(indiceVetRicetteScadenza+1,sizeof(int));
	for(i=0;i<indiceVetRicetteScadenza+1;i++){
		c[i]=vettoreRicetteScadenza[i];
	}
	(*numeroRicetteTrovate)=indiceVetRicetteScadenza+1;
	return c;

}






int suggerimento_ricette_in_scadenza(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	printf("\n\nSuggerimento delle ricette in scadenza\n%s\nLe ricette saranno ordinate prima\nper i preferiti e poi per frequenza\n\n",STRINGASTERISCHI);

	int numeroRicetteInScadenza=0;

	int *vettoreRicetteScadenza=get_ricette_in_scadenza(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,&numeroRicetteInScadenza);
	merge_sort_ricette(ricette,0,numeroRicetteInScadenza-1,vettoreRicetteScadenza,4);

	int i;
	boolean flag=false;

	if(numeroRicetteInScadenza == 0) printf("\nNon ci sono ricette con alimenti in scadenza\n");
	else{
		printf("\nLe ricette che hanno degli alimenti in scadenza sono:\n");
		for(i=0;i<numeroRicetteInScadenza;i++){
			if(exist_preferito(ricette,&vettoreRicetteScadenza[i]) == false && flag==false){
				merge_sort_ricette(ricette,i,numeroRicetteInScadenza-1,vettoreRicetteScadenza,3);
				flag=true;
			}
			printf("%d - %25s \t| Kcal per porzione: %5.2f \t| %s\n", i,
										ricette[vettoreRicetteScadenza[i]].Nome, ricette[vettoreRicetteScadenza[i]].Kcal_Porzione,(exist_preferito(ricette,&vettoreRicetteScadenza[i]) == true)? "PREF":"");
		}
	}

	return 1;
}




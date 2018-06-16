/*
 * Spesa_Tools.c
 *
 *  Created on: 30 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include "Data_Tools.h"
#include <string.h>






/* FUNZIONE PER LA VISUALIZZAZIONE DI TUTTO LO STORICO SPESA	*
 * E QUINDI DI TUTTE LE SPESE EFFETTUATE						*/
void visualizza_storico_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti){
	FILE *fileStoricoSpesa;

	elemento_spesa elemento;

	boolean flag=false;

	if ((fileStoricoSpesa = fopen("src/Storico_Spesa.sf", "rb")) != NULL)
	{
		printf("\n\nStorico Spesa\n%s\n",STRINGASTERISCHI);
		printf("%20s | %20s | %20s","Alimento Acquistato","Quantita Acquistata","Data di Acquisto");
		printf("\n-----------------------------------------------------------------");

		do{
			int a=fread(&elemento,sizeof(elemento_spesa),1,fileStoricoSpesa);
			if(a>0){
				flag=true;
				printf("\n%20s | %20d | ",alimenti[elemento.ID_Alimento].Nome,elemento.Quantita);
				printf("%d/%d/%d %d:%d",elemento.Data_Ora.Giorno,elemento.Data_Ora.Mese,elemento.Data_Ora.Anno,elemento.Data_Ora.Ora,elemento.Data_Ora.Minuti);
			}
		}while(!feof(fileStoricoSpesa));

		if(!flag) printf("\n\nNon e' mai stata effettuata la spesa! Registro Vuoto!\n\n");
		else printf("\n\n");

		fclose(fileStoricoSpesa);
	}
}






/* FUNZIONE CHE MEMORIZZA LA SPESA FATTA ALL'INTERNO	*
 * DEL FILE IN CUI VENGONO MEMORIZZATE TUTTI I 			*
 * CHE RIGUARDANO LA SPESA								*
 * 														*
 * LA FUNZIONE HA COME PARAMETRI L'INDICE DELL'ALIMENTO *
 * E LA QUANTITA CHE È STATA AGGIUNTA O RIMOSSA			*
 * E RITORNA 1 SE E' ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int memorizza_in_storico_spesa(int indiceAlimento,int quantita){
	FILE *fileStoricoSpesa;
	elemento_spesa elemento;

	elemento.ID_Alimento=indiceAlimento;

	elemento.Data_Ora.Anno=get_data('Y');
	elemento.Data_Ora.Mese=get_data('M');
	elemento.Data_Ora.Giorno=get_data('D');
	elemento.Data_Ora.Ora=get_data('H');
	elemento.Data_Ora.Minuti=get_data('m');
	elemento.Data_Ora.Secondi=get_data('S');

	elemento.Quantita=quantita;

	if ((fileStoricoSpesa = fopen("src/Storico_Spesa.sf", "ab+")) == NULL) return 0;
	else {

		fwrite(&elemento,sizeof(elemento_spesa),1,fileStoricoSpesa);

		fclose(fileStoricoSpesa);
		return 1;
	}
}







/* FUNZIONE CHE SI OCCUPA DI TUTTO QUELLO CHE RIGUARDA 	*
 * L'AGGIUNTA DEGLI ALIMENTI ALL'INTERNO DEL VETTORE	*
 * E ALL'INTERNO DEL FILE								*
 * 														*
 * LA FUNZIONE RICEVE COME PARAMETRI IL VETTORE DI 		*
 * ALIMENTI E LA SUA LUNGHEZZA E INOLTRE UN PUNTATORE 	*
 * AD INTERO PER LA MEMORIZZAZIONE DELL'INDIRIZZO 		*
 * DOVE RISIEDE IL NUONO VETTORE DI ALIMENTI IN CASO DI	*
 * AGGIUNTA DI UN ALIMENTO IN CODA AL VETTORE*/
int inserimento_alimenti_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoAlimenti){

	char scelta[LUNGHEZZA_STRINGA];
	int i=0,j;
	int indiceAlimento;
	int indiceScadenza;
	int quantita;
	boolean flagRipetizione;

	printf("\n\n            Inserimento Spesa\n**********************************\n\n");

	do{

		printf("Inserisci il nome dell'alimento acquistato numero %d: ",(i+1));
		fgets(scelta,LUNGHEZZA_STRINGA,stdin);

		//controllo se l'alimento che deve essere inserito è gia presente
		//se lo e' devo andare ad aggiornare le quantita di quel alimento
		if((indiceAlimento=get_alimento(alimenti,lunghezzaVettoreAlimenti,scelta,false)) != -1){
			printf("\nAlimento gia' presente nel database!\nMi serve sapere solo la quantita acquistata e la data di scadenza!");

			quantita=fai_scelta("\n\nInserisci la quantita acquistata: ");

			data_ora data;

			get_data_input(&data.Giorno,&data.Mese,&data.Anno,"\nInserisci la data di scadenza:");

			if(alimenti[indiceAlimento].Visibilita==false) alimenti[indiceAlimento].Visibilita=true;


			//se la scadenza è gia presente vuol dire che devo andare a sommare la quantita nella
			//scadenza trovata
			if((indiceScadenza=get_data_scadenza(alimenti[indiceAlimento],data)) > -1){
				alimenti[indiceAlimento].Scadenze[indiceScadenza].Quantita += quantita;
			}else{

				//altrimenti devo aggiungere la scadenza e la quantita
				for(j=0;j<LUNGHEZZA_VET_SCADENZE;j++){
					if(alimenti[indiceAlimento].Scadenze[j].Quantita == 0){
						alimenti[indiceAlimento].Scadenze[j].Quantita = quantita;
						alimenti[indiceAlimento].Scadenze[j].Data_Scadenza.Anno=data.Anno;
						alimenti[indiceAlimento].Scadenze[j].Data_Scadenza.Mese=data.Mese;
						alimenti[indiceAlimento].Scadenze[j].Data_Scadenza.Giorno=data.Giorno;
						break;
					}
				}
				if(j==LUNGHEZZA_VET_SCADENZE) printf("\nHai raggiunto il numero massimo di scadenze disponibili!\n"
						"Accedi alle Opzioni Alimenti per modificare le scadenze!\n");
			}

			//come NuovoIndirizzoImposto quello di se stesso
			(*nuovoIndirizzoAlimenti)=(int)alimenti;



			//memorizzo l'aggiunta anche nello storico spesa
			if(!memorizza_in_storico_spesa(indiceAlimento,quantita)) printf("\nErrore nell'aggiunta dell'alimento nello storico spesa!\n");


			//applico le modifica apportate al vettore anche su file
			if(modifica_alimento_su_file(alimenti[indiceAlimento])) printf("\nAggiunta dell'alimento nel frigo avvenuta con successo!\n");
			else printf("\nErrore nell'aggiunta dell'alimento su file!\n");



		}else{

			alimento alim;
			int j;
			quantita=0;


			//chiedo tutti i dati dell'alimento
			//chiedo il peso
			alim.Peso =fai_scelta("\nInserisci il peso dell'alimento: ");
			alim.Kcal_Pezzo =fai_scelta_double("\nInserisci le Kcal per pezzo dell'alimento: ");

			boolean flag=fai_scelta_booleana("\nCi sono confezioni con date di scadenza diversa? ");
			int NumeroScadenze=1;
			if(flag==true){

				do{
					NumeroScadenze=fai_scelta("\nQuante sono le date di scadenza diverse?: ");
					if(NumeroScadenze>LUNGHEZZA_VET_SCADENZE) printf("\nErrore! Puoi inserire al massimo %d date di scadenza!\n",LUNGHEZZA_VET_SCADENZE);
				}while(NumeroScadenze>LUNGHEZZA_VET_SCADENZE || NumeroScadenze<1);

			}

			for(j=0;j<LUNGHEZZA_VET_SCADENZE;j++){

				if(j<NumeroScadenze){
					printf("\nScadenza %d\n",(j+1));
					alim.Scadenze[j].Quantita=fai_scelta("\nInserisci la quantita acquistata dell'alimento:");
					quantita+=alim.Scadenze[j].Quantita;
					get_data_input(&alim.Scadenze[j].Data_Scadenza.Giorno,&alim.Scadenze[j].Data_Scadenza.Mese,&alim.Scadenze[j].Data_Scadenza.Anno,"\nInserisci la data di scadenza dell'alimento:");
				}else{
					alim.Scadenze[j].Quantita=0;
					alim.Scadenze[j].Data_Scadenza.Giorno=0;
					alim.Scadenze[j].Data_Scadenza.Mese=0;
					alim.Scadenze[j].Data_Scadenza.Anno=0;
				}


			}

			alim.Visibilita=true;
			alim.Utilizzo=0;
			alim.ID_Alimento=lunghezzaVettoreAlimenti;
			strcpy(alim.Nome,scelta);



			//se l'alimento non è presente devo andare ad aggiungerlo al vettore
			//prova di allungamento del vettore
			lunghezzaVettoreAlimenti++;

			alimento *alimenti2= (alimento*) calloc(lunghezzaVettoreAlimenti,sizeof(alimento));

			for(j=0;j<lunghezzaVettoreAlimenti-1;j++) alimenti2[j]=alimenti[j];

			//Libero la memoria del vecchio vettore
			free(alimenti);

			alimenti2[lunghezzaVettoreAlimenti-1]=alim;

			(*nuovoIndirizzoAlimenti)=(int)alimenti2;



			//memorizzo l'aggiunta anche nello storico spesa
			if(!memorizza_in_storico_spesa(lunghezzaVettoreAlimenti-1,quantita)) printf("\nErrore nell'aggiunta dell'alimento nello storico spesa!\n");



			//aggiungo l'alimento anche su file
			if(aggiungi_alimento_su_file(alim)) printf("\nAlimento aggiunto nel frigo con successo!\n");
			else printf("\nErrore nell'aggiunta dell'alimento su file!\n");


		}


		flagRipetizione=fai_scelta_booleana("\nVuoi inserire un altro alimento?");
		i++;

	}while(flagRipetizione==true);

	return lunghezzaVettoreAlimenti;
}












/* FUNZIONE CHE GESTISCE IL MENU RELATIVO AGLI ALIMENTI		*
 * CHIEDE ALL'UNTETE DI FARE UNA SCELTA E CONTROLLA CHE		*
 * LA SCELTA SIA VALIDA; 									*
 * SE LO E' RICHIAMA LE OPPORTUNE FUNZIONI CHE ESEGUONO		*
 * IL PARTOCOLARE COMPITO									*
 *
 * Ha come parametro anche un puntatore chiamato 			*
 * NuovoIndirizzoAlimenti per la gestione dell'aggiunta		*
 * degli alimenti e del vettore di Alimenti*/
int scelta_opzioni_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoAlimenti) {
	int NumScelta=1;

	//come NuovoIndirizzoImposto quello di se stesso nel caso non venisse mai richiamata
	//la funzionalita di Inserimento degli alimenti
	(*nuovoIndirizzoAlimenti)=(int)alimenti;

	do {
		printf("\nOpzioni Spesa\n");
		NumScelta = fai_scelta(MENU_OPZIONI_SPESA);

		switch(NumScelta){
			case 1:
				//Inserimento della spesa
				lunghezzaVettoreAlimenti=inserimento_alimenti_spesa(alimenti,lunghezzaVettoreAlimenti,nuovoIndirizzoAlimenti);

				//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di un nuovo alimento
				alimenti=(alimento *)(*nuovoIndirizzoAlimenti);

				break;

			case 2:
				//visualizzazione dello storico spese
				visualizza_storico_spesa(alimenti,lunghezzaVettoreAlimenti);
				break;

			case 0:
				//case di uscita dal menu seguente
				break;

			default:
				printf("\nScelta errata!\n");
		}

	} while (NumScelta != 0);

	return lunghezzaVettoreAlimenti;
}

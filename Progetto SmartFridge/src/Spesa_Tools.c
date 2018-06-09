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
void Visualizza_Storico_Spesa(alimento alimenti[],int lunghezza_vettore_alimenti){
	FILE *file_storico_spesa;

	elemento_spesa elemento;

	boolean flag=false;

	if ((file_storico_spesa = fopen("src/Storico_Spesa.sf", "rb")) != NULL)
	{
		printf("\n\nStorico Spesa\n%s\n",STRINGASTERISCHI);
		printf("%20s | %20s | %20s","Alimento Acquistato","Quantita Acquistata","Data di Acquisto");
		printf("\n-----------------------------------------------------------------");

		do{
			int a=fread(&elemento,sizeof(elemento_spesa),1,file_storico_spesa);
			if(a>0){
				flag=true;
				printf("\n%20s | %20d | ",alimenti[elemento.ID_Alimento].Nome,elemento.Quantita);
				printf("%d/%d/%d %d:%d",elemento.Data_Ora.Giorno,elemento.Data_Ora.Mese,elemento.Data_Ora.Anno,elemento.Data_Ora.Ora,elemento.Data_Ora.Minuti);
			}
		}while(!feof(file_storico_spesa));

		if(!flag) printf("\n\nNon e' mai stata effettuata la spesa! Registro Vuoto!\n\n");
		else printf("\n\n");

		fclose(file_storico_spesa);
	}
}






/* FUNZIONE CHE MEMORIZZA LA SPESA FATTA ALL'INTERNO	*
 * DEL FILE IN CUI VENGONO MEMORIZZATE TUTTI I 			*
 * CHE RIGUARDANO LA SPESA								*
 * 														*
 * LA FUNZIONE HA COME PARAMETRI L'INDICE DELL'ALIMENTO *
 * E LA QUANTITA CHE È STATA AGGIUNTA O RIMOSSA			*
 * E RITORNA 1 SE E' ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int Memorizza_In_Storico_Spesa(int IndiceAlimento,int quantita){
	FILE *file_storico_spesa;
	elemento_spesa elemento;

	elemento.ID_Alimento=IndiceAlimento;

	elemento.Data_Ora.Anno=getData('Y');
	elemento.Data_Ora.Mese=getData('M');
	elemento.Data_Ora.Giorno=getData('D');
	elemento.Data_Ora.Ora=getData('H');
	elemento.Data_Ora.Minuti=getData('m');
	elemento.Data_Ora.Secondi=getData('S');

	elemento.Quantita=quantita;

	if ((file_storico_spesa = fopen("src/Storico_Spesa.sf", "ab+")) == NULL) return 0;
	else {

		fwrite(&elemento,sizeof(elemento_spesa),1,file_storico_spesa);

		fclose(file_storico_spesa);
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
int Inserimento_Alimenti_Spesa(alimento alimenti[],int Lunghezza_Vettore_Alimenti,int *NuovoIndirizzoAlimenti){

	char scelta[LUNGHEZZA_STRINGA];
	int i=0,j;
	int IndiceAlimento;
	int IndiceScadenza;
	int quantita;
	boolean FlagRipetizione;

	printf("\n\n            Inserimento Spesa\n**********************************\n\n");

	do{

		printf("Inserisci il nome dell'alimento acquistato numero %d: ",(i+1));
		fgets(scelta,LUNGHEZZA_STRINGA,stdin);

		//controllo se l'alimento che deve essere inserito è gia presente
		//se lo e' devo andare ad aggiornare le quantita di quel alimento
		if((IndiceAlimento=getAlimento(alimenti,Lunghezza_Vettore_Alimenti,scelta,false)) != -1){
			printf("\nAlimento gia' presente nel database!\nMi serve sapere solo la quantita acquistata e la data di scadenza!");

			quantita=FaiScelta("\n\nInserisci la quantita acquistata: ");

			data_ora data;

			getDataInput(&data.Giorno,&data.Mese,&data.Anno,"\nInserisci la data di scadenza:");

			if(alimenti[IndiceAlimento].Visibilita==false) alimenti[IndiceAlimento].Visibilita=true;


			//se la scadenza è gia presente vuol dire che devo andare a sommare la quantita nella
			//scadenza trovata
			if((IndiceScadenza=getDataScadenza(alimenti[IndiceAlimento],data)) > -1){
				alimenti[IndiceAlimento].Scadenze[IndiceScadenza].Quantita += quantita;
			}else{

				//altrimenti devo aggiungere la scadenza e la quantita
				for(j=0;j<LUNGHEZZA_VET_SCADENZE;j++){
					if(alimenti[IndiceAlimento].Scadenze[j].Quantita == 0){
						alimenti[IndiceAlimento].Scadenze[j].Quantita = quantita;
						alimenti[IndiceAlimento].Scadenze[j].Data_Scadenza.Anno=data.Anno;
						alimenti[IndiceAlimento].Scadenze[j].Data_Scadenza.Mese=data.Mese;
						alimenti[IndiceAlimento].Scadenze[j].Data_Scadenza.Giorno=data.Giorno;
						break;
					}
				}
				if(j==LUNGHEZZA_VET_SCADENZE) printf("\nHai raggiunto il numero massimo di scadenze disponibili!\n"
						"Accedi alle Opzioni Alimenti per modificare le scadenze!\n");
			}

			//come NuovoIndirizzoImposto quello di se stesso
			(*NuovoIndirizzoAlimenti)=(int)alimenti;



			//memorizzo l'aggiunta anche nello storico spesa
			if(!Memorizza_In_Storico_Spesa(IndiceAlimento,quantita)) printf("\nErrore nell'aggiunta dell'alimento nello storico spesa!\n");


			//applico le modifica apportate al vettore anche su file
			if(Modifica_Alimento_Su_File(alimenti[IndiceAlimento])) printf("\nAggiunta dell'alimento nel frigo avvenuta con successo!\n");
			else printf("\nErrore nell'aggiunta dell'alimento su file!\n");



		}else{

			alimento alim;
			int j;
			quantita=0;


			//chiedo tutti i dati dell'alimento
			//chiedo il peso
			alim.Peso =FaiScelta("\nInserisci il peso dell'alimento: ");
			alim.Kcal_Pezzo =FaiSceltaDouble("\nInserisci le Kcal per pezzo dell'alimento: ");

			boolean flag=FaiSceltaBooleana("\nCi sono confezioni con date di scadenza diversa? ");
			int NumeroScadenze=1;
			if(flag==true){

				do{
					NumeroScadenze=FaiScelta("\nQuante sono le date di scadenza diverse?: ");
					if(NumeroScadenze>LUNGHEZZA_VET_SCADENZE) printf("\nErrore! Puoi inserire al massimo %d date di scadenza!\n",LUNGHEZZA_VET_SCADENZE);
				}while(NumeroScadenze>LUNGHEZZA_VET_SCADENZE || NumeroScadenze<1);

			}

			for(j=0;j<LUNGHEZZA_VET_SCADENZE;j++){

				if(j<NumeroScadenze){
					printf("\nScadenza %d\n",(j+1));
					alim.Scadenze[j].Quantita=FaiScelta("\nInserisci la quantita acquistata dell'alimento:");
					quantita+=alim.Scadenze[j].Quantita;
					getDataInput(&alim.Scadenze[j].Data_Scadenza.Giorno,&alim.Scadenze[j].Data_Scadenza.Mese,&alim.Scadenze[j].Data_Scadenza.Anno,"\nInserisci la data di scadenza dell'alimento:");
				}else{
					alim.Scadenze[j].Quantita=0;
					alim.Scadenze[j].Data_Scadenza.Giorno=0;
					alim.Scadenze[j].Data_Scadenza.Mese=0;
					alim.Scadenze[j].Data_Scadenza.Anno=0;
				}


			}

			alim.Visibilita=true;
			alim.Utilizzo=0;
			alim.ID_Alimento=Lunghezza_Vettore_Alimenti;
			strcpy(alim.Nome,scelta);



			//se l'alimento non è presente devo andare ad aggiungerlo al vettore
			//prova di allungamento del vettore
			Lunghezza_Vettore_Alimenti++;

			alimento *alimenti2= (alimento*) calloc(Lunghezza_Vettore_Alimenti,sizeof(alimento));

			for(j=0;j<Lunghezza_Vettore_Alimenti-1;j++) alimenti2[j]=alimenti[j];

			//Libero la memoria del vecchio vettore
			free(alimenti);

			alimenti2[Lunghezza_Vettore_Alimenti-1]=alim;

			(*NuovoIndirizzoAlimenti)=(int)alimenti2;



			//memorizzo l'aggiunta anche nello storico spesa
			if(!Memorizza_In_Storico_Spesa(Lunghezza_Vettore_Alimenti-1,quantita)) printf("\nErrore nell'aggiunta dell'alimento nello storico spesa!\n");



			//aggiungo l'alimento anche su file
			if(Aggiungi_Alimento_Su_File(alim)) printf("\nAlimento aggiunto nel frigo con successo!\n");
			else printf("\nErrore nell'aggiunta dell'alimento su file!\n");


		}


		FlagRipetizione=FaiSceltaBooleana("\nVuoi inserire un altro alimento?");
		i++;

	}while(FlagRipetizione==true);

	return Lunghezza_Vettore_Alimenti;
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
int Scelta_Opzioni_Spesa(alimento alimenti[],int Lunghezza_Vettore_Alimenti,int *NuovoIndirizzoAlimenti) {
	int NumScelta=1;

	//come NuovoIndirizzoImposto quello di se stesso nel caso non venisse mai richiamata
	//la funzionalita di Inserimento degli alimenti
	(*NuovoIndirizzoAlimenti)=(int)alimenti;

	do {
		printf("\nOpzioni Spesa\n");
		NumScelta = FaiScelta(MenuOpzioniSpesa);

		switch(NumScelta){
			case 1:
				//Inserimento della spesa
				Lunghezza_Vettore_Alimenti=Inserimento_Alimenti_Spesa(alimenti,Lunghezza_Vettore_Alimenti,NuovoIndirizzoAlimenti);

				//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di un nuovo alimento
				alimenti=(alimento *)(*NuovoIndirizzoAlimenti);

				break;

			case 2:
				//visualizzazione dello storico spese
				Visualizza_Storico_Spesa(alimenti,Lunghezza_Vettore_Alimenti);
				break;

			case 0:
				//case di uscita dal menu seguente
				break;

			default:
				printf("\nScelta errata!\n");
		}

	} while (NumScelta != 0);

	return Lunghezza_Vettore_Alimenti;
}

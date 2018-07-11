/**
 *  @file      Spesa_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Spesa_Tools.h
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include "Data_Tools.h"
#include <string.h>






/**
 * Funzione che visualizza in output all'utente, una tabella con la lista
 * di tutte le spese effettuate dalla prima accensione dello smart fridge.
 *
 * @pre il file Storico_Spesa.sf deve esistere e i dati all'interno devono
 * essere organizzati utilizzando la struct elemento_spesa.
 */
int visualizza_storico_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti){
	FILE *fileStoricoSpesa;

	elemento_spesa elemento;

	boolean flag=false;

	//pulisco lo schermo
	system("cls");

	if ((fileStoricoSpesa = fopen("Storico_Spesa.sf", "rb")) != NULL)
	{
		printf("\nSTORICO SPESA\n\n%s\n\n",STRINGASTERISCHI);
		printf("%20s | %20s | %20s","Alimento Acquistato","Quantita Acquistata","Data di Acquisto");
		printf("\n-----------------------------------------------------------------");

		do{
			if(fread(&elemento,sizeof(elemento_spesa),1,fileStoricoSpesa)>0){
				flag=true;
				printf("\n%20s | %20d | ",alimenti[elemento.ID_Alimento].Nome,elemento.Quantita);
				printf("%d/%d/%d %d:%d",elemento.Data_Ora.Giorno,elemento.Data_Ora.Mese,elemento.Data_Ora.Anno,elemento.Data_Ora.Ora,elemento.Data_Ora.Minuti);
			}
		}while(!feof(fileStoricoSpesa));

		if(!flag) return 0;
		else return 1;

		fclose(fileStoricoSpesa);
	}else return 0;
}






/**
 * Funzione che memorizza la spesa fatta all'interno del file Storico_Spesa.sf
 * che contiene lo storico di tutte le spese in ordine cronologico.
 *
 */
int memorizza_in_storico_spesa(int indiceAlimento,int quantita){
	FILE *fileStoricoSpesa;
	elemento_spesa elemento;

	elemento.ID_Alimento=indiceAlimento;

	get_data_pointer(&elemento.Data_Ora);

	//CANCELLARE DOPO AVER AGGIUNTO TUTTE LE SPESE
	//get_data_input(&elemento.Data_Ora.Giorno,&elemento.Data_Ora.Mese,&elemento.Data_Ora.Anno,"\n\nInserisci la data in cui inserisci la spesa");

	elemento.Quantita=quantita;

	if ((fileStoricoSpesa = fopen("Storico_Spesa.sf", "ab+")) == NULL) return 0;
	else {

		fwrite(&elemento,sizeof(elemento_spesa),1,fileStoricoSpesa);

		fclose(fileStoricoSpesa);
		return 1;
	}
}







/**
 * Funzione che si occupa di tutto quello che riguarda l'aggiunta dei
 * nuovi alimenti comprati,inserendoli sia all'inerno del vettore che del file Storico_Spesa.sf.
 * Essa chiede tutti i dati dell'acquisto all'utente e richiama le relative funzioni per salvare
 * i dati su file.
 *
 */
int inserimento_alimenti_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoAlimenti){

	char scelta[LUNGHEZZA_STRINGA];
	int i=0,j;
	int indiceAlimento;
	int indiceScadenza;
	int quantita;
	boolean flagRipetizione;

	//pulisco lo schermo
	system("cls");

	printf("\nINSERIMENTO SPESA\n%s\n\n",STRINGASTERISCHI);

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

					do{
						alim.Scadenze[j].Quantita=fai_scelta("\nInserisci la quantita acquistata dell'alimento:");
					}while(alim.Scadenze[j].Quantita < 1);

					quantita+=alim.Scadenze[j].Quantita;
					get_data_input(&alim.Scadenze[j].Data_Scadenza.Giorno,&alim.Scadenze[j].Data_Scadenza.Mese,&alim.Scadenze[j].Data_Scadenza.Anno,"\nInserisci la data di scadenza dell'alimento:");
				}else{
					alim.Scadenze[j].Quantita=0;
					alim.Scadenze[j].Data_Scadenza.Giorno=0;
					alim.Scadenze[j].Data_Scadenza.Mese=0;
					alim.Scadenze[j].Data_Scadenza.Anno=0;
					alim.Scadenze[j].Data_Scadenza.Minuti=0;
					alim.Scadenze[j].Data_Scadenza.Ora=0;
					alim.Scadenze[j].Data_Scadenza.Secondi=0;
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












/**
 * Funzione che gestisce il menu relativo alla spesa cioe' chiede in
 * input all'utente di fare una scelta, di controllare se sia valida,
 * e di eseguire le relative funzioni in base alla scelta fatta.
 *
 */
int scelta_opzioni_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoAlimenti) {
	int numScelta=1;

	//come NuovoIndirizzoImposto quello di se stesso nel caso non venisse mai richiamata
	//la funzionalita di Inserimento degli alimenti
	(*nuovoIndirizzoAlimenti)=(int)alimenti;

	do {

		//pulisco lo schermo
		system("cls");

		printf("\nOPZIONI SPESA\n");
		numScelta = fai_scelta(MENU_OPZIONI_SPESA);

		switch(numScelta){
			case 1:
				//Inserimento della spesa
				lunghezzaVettoreAlimenti=inserimento_alimenti_spesa(alimenti,lunghezzaVettoreAlimenti,nuovoIndirizzoAlimenti);

				//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di un nuovo alimento
				alimenti=(alimento *)(*nuovoIndirizzoAlimenti);

				break;

			case 2:
				//visualizzazione dello storico spese
				if(visualizza_storico_spesa(alimenti,lunghezzaVettoreAlimenti) == 0){
					printf("\n\nNon e' mai stata fatta la spesa!\n\n");
				}else printf("\n\n");
				break;

			case 0:
				//case di uscita dal menu seguente
				break;

			default:
				printf("\nScelta errata!\n");
		}

		if(numScelta != 0) {
			char c[LUNGHEZZA_STRINGA];
			printf("\nPremi per continuare....");
			fgets(c,LUNGHEZZA_STRINGA,stdin);
		}

	} while (numScelta != 0);

	return lunghezzaVettoreAlimenti;
}

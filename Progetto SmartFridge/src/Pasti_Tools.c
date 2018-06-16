/*
 * Pasti_Tools.c
 *
 *  Created on: 06 giu 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include "Messaggi_Menu.h"
#include "Ricette_Tools.h"
#include "Data_Tools.h"
#include "Gen_File.h"
#include "Alimenti_Tools.h"




int aggiungi_pasto_su_file(int numPorzioni,int idRicetta){

	FILE *file;
	pasto pp;

	pp.ID_Ricetta=idRicetta;
	pp.Porzioni=numPorzioni;
	pp.visibilita=true;

	get_data_pointer(&pp.Data_Ora);


	if ((file = fopen("src/Storico_Pasti.sf", "ab+")) == NULL) {
			printf("Errore nell'apertura del file!\n");
			return 0;
	} else {
		fwrite(&pp,sizeof(pasto),1,file);

		fclose(file);
		return 1;
	}

}





/* FUNZIONE TEMPORANEA PER LA VISUALIZZAZIONE DELLA SITUAZIONE SU FILE*/
int visualizza_file_pasti(ricetta ricette[]){
	FILE *fileStoricoPasti;

	pasto past;

	if ((fileStoricoPasti = fopen("src/Storico_Pasti.sf", "rb")) != NULL)
	{
		printf("\n\nStorico Pasti\n%s\n",STRINGASTERISCHI);
		printf("%20s | %20s | %20s | Visibilita","Alimento Acquistato","Quantita Acquistata","Data di Acquisto");
		printf("\n-----------------------------------------------------------------");

		do{
			int a=fread(&past,sizeof(past),1,fileStoricoPasti);
			if(a>0){
				printf("\n%20s | %20d | ",ricette[past.ID_Ricetta].Nome,past.Porzioni);
				printf("%d/%d/%d %d:%d | %s",past.Data_Ora.Giorno,past.Data_Ora.Mese,past.Data_Ora.Anno,past.Data_Ora.Ora,past.Data_Ora.Minuti,(past.visibilita)?"true":"false");
			}
		}while(!feof(fileStoricoPasti));

		fclose(fileStoricoPasti);
	}
	return 1;
}






int aggiungi_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){


	printf("\n\nAggiungi un pasto\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta che vuoi consumare:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice,numPorzioni;

	if ((indice=get_ricetta(ricette, lunghezzaVettoreRicette,scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nRicetta Trovata\n\n");

		do{
			numPorzioni=fai_scelta("Inserisci il numero di porzioni che si intende consumare: ");
			if(numPorzioni==0) printf("\nScelta non valida! Riprova!\n");
		}while(numPorzioni==0);

		int porzioniPossibili=get_numero_porzioni_possibili_ricetta(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,indice);

		if(numPorzioni<=porzioniPossibili){
			//incremento la frequenza del pasto
			ricette[indice].Frequenza+=numPorzioni;
			modifica_ricetta_su_file(ricette[indice]);

			//decremento le quantita di alimenti utilizzate nel vettore alimenti
			consuma_ricetta_su_alimenti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,indice,numPorzioni);


			if(aggiungi_pasto_su_file(numPorzioni,indice)) printf("\nPasto registrato con successo! %s\n",get_tipo_pasto());
			else printf("\nErrore nella memorizzazione del pasto su file!\n");
		}else printf("\nNon hai abbastanza ingredienti per preparare quella ricetta!\n");



	}else printf("\nLa ricetta inserita non esiste!\n");

	return 1;

}





/* FUNZIONE CHE STAMPA ALL'UTENTE TUTTI I PASTI CONSUMATI DURANTE UNA SETTIMANA *
 * PASSATA COME	PARAMETRO														*
 * 																				*
 * IL PARAMETRO NumeroSettimana REPPRESENTA QUANTE SETTIMANE A RITROSO BISOGNA	*
 * ANDARE PER STAMPARE LA SETTIMANA RICHIESTA 									*
 * 																				*
 * IL PARAMETRO giornoSettimana INDICA QUANTI GIORNI DELLA SETTIMANA LA 		*
 * FUNZIONE DEVE STAMPARE IN QUANTO SE LA SETTIMANA ATTUALE NON E' ANCORA 		*
 * FINITA LA FUNZIONE SI DEVE FERMARE AL GIORNO ATTUALE INVECE DI CONTINUARE 	*
 * PER I GIORNI FUTURI															*/
int stampa_iesimo_menu_settimanale(ricetta ricette[],int lunghezzaVettoreRicette,int NumeroSettimana,int giornoSettimana){

	int i;

	FILE *file;
	pasto pp;
	data_ora d;
	get_data_pointer(&d);
	boolean flag;
	int delay=0;

	//vuol dire che la funzione viene chiamata per visualizzare settimane precedenti a quella corrente
	//devo aggiungere un delay in quanto la data inserita dall'utente puo essere una data
	//mediana della settimana e quindi per far visualizzare tutta la settimana bisogna aggiungere
	//i giorni mancanti infatti delay andra' poi sommato alla distanza tra le 2 date
	if(NumeroSettimana!=0){
		delay=get_data('W');
		delay=NUMERO_MASSIMO_GIORNI-delay;
	}

	if ((file = fopen("src/Storico_Pasti.sf", "rb")) == NULL) {
				printf("Errore nell'apertura del file!\n");
				return 0;
	} else {
		printf("\n\n%15s | %20s | %15s\n","Giorno","Pasto","Porzioni");
		printf("---------------------------------------------------------");
		//scorro i giorni da lunedi fino al giorno della settimana corrente
		for(i=giornoSettimana;i>=0;i--){
			flag=false;
			//if(i!=giornoSettimana) printf("\n------------------------------------------------------");
			//leggo tutto il file
			while(!feof(file)){
				int a=fread(&pp,sizeof(pasto),1,file);

				//controllo che la distanza tra la data attuale e la data del pasto letta da file
				//sia uguale alla distanza tra il giorno della settimana che si vuole visualizzare
				//e la data attuale
				if(get_distanza_in_giorni(pp.Data_Ora,d,delay) == (i+(NumeroSettimana*NUMERO_GIORNI)) && a > 0 && pp.visibilita==true){

					//controllo se e' il primo ad essere trovato o no
					if(flag==false){
						printf("\n%15s | %20s | %15d",indice_to_giorni_settimana(giornoSettimana-i),ricette[pp.ID_Ricetta].Nome,pp.Porzioni);
						//printf("\n%20s | %15s\n","Ricetta","Porzioni");
						flag=true;
					}else printf("\n%15s | %20s | %15d","-" ,ricette[pp.ID_Ricetta].Nome,pp.Porzioni);
				}
			}
			if(flag==false) printf("\n%15s | %20s | %15s",indice_to_giorni_settimana(giornoSettimana-i),"-","-");
			rewind(file);
		}

		printf("\n\n");

		fclose(file);
	}

	return 1;

}





/* FUNZIONE CHE GESTISCE LA CHIAMATA DELLA FUNZIONE		*
 * PER LA VISUALIZZAZIONE DEL MENU SETTIMANALE DELLA 	*
 * SETTIMANA CORRENTE									*/
int visualizza_menu_settimana_in_corso(ricetta ricette[],int lunghezzaVettoreRicette){

	//Richiamo la funzione di stampa del menu della iesima settimana
	//in maniera che stampi la settimana corrente
	stampa_iesimo_menu_settimanale(ricette,lunghezzaVettoreRicette,0,get_data('W'));

	return 1;

}






/* FUNZIONE CHE CALCOLA IL NUMERO DI SETTIMANE 	*
 * DI DISTANZA IN BASE AI GIORNI DI DISTANZA	*
 * PASSATI COME PARAMETRO						*/
int get_numero_settimane(int distanza){
	int i,NumeroSettimane=0;
	for(i=0;distanza>=1;i++){
		NumeroSettimane++;
		distanza-=7;
	}
	return NumeroSettimane;
}






/* FUNZIONE CHE GESTISCE LA CHIAMATA DELLA FUNZIONE PER *
 * LA VISUALIZZAZIONE DEL MENU SETTIMANALE DI SETTIMANE *
 * PASSATE A QUELLA CORRENTE*/
int visualizza_menu_settimane_passate(ricetta ricette[],int lunghezzaVettoreRicette){

	data_ora dataInput;
	data_ora dataCorrente;
	boolean flag;
	int numeroSettimane;

	do{
		flag=false;
		get_data_pointer(&dataCorrente);
		get_data_input(&dataInput.Giorno,&dataInput.Mese,&dataInput.Anno,"\nInserisci la data di un giorno della settimana di cui si vuole vedere il menu settimanale: ");

		//calcolo la distanza tra la settimana corrente e la settimana inserita in input
		int distanza=get_distanza_in_giorni(dataInput,dataCorrente,0);

		if(distanza>=0){

			//calcolo quante settimane a ritroso devo andare
			//per visualizzare lo storico pasti della settimana presa in input
			distanza-=data_to_giorni_settimana(dataCorrente);
			numeroSettimane=get_numero_settimane(distanza);

			flag=true;

			//se il numero settimane e' diverso da 0 vuol dire che devo andare
			//a ritrono di NumeroSettimane SETTIMANE
			if(numeroSettimane!=0){
				stampa_iesimo_menu_settimanale(ricette,lunghezzaVettoreRicette,numeroSettimane,6);

			}else 	stampa_iesimo_menu_settimanale(ricette,lunghezzaVettoreRicette,0,get_data('W'));
		}else{
			//caso in cui la data inserita in input sia sucessiva alla data corrente
			printf("\nLa data non puo essere superiore alla data corrente! Reinseriscila!\n");
		}
	}while(flag==false);


	return 1;
}







int scelta_opzioni_visualizza_menu_settimanale(ricetta ricette[],int lunghezzaVettoreRicette){

	printf("\n\nVisualizzazione Menu Settimanale\n%s\n",STRINGASTERISCHI);

	int numScelta;

	do{

		numScelta=fai_scelta(MENU_OPZIONI_VISUALIZZAZIONE_MENU_SETTIMANALE);

		switch(numScelta){
			case 1:
				//visualizzazione menu settimana in corso
				visualizza_menu_settimana_in_corso(ricette,lunghezzaVettoreRicette);
				break;
			case 2:
				//visualizzazione menu settimane passate
				visualizza_menu_settimane_passate(ricette,lunghezzaVettoreRicette);
				break;
			case 0:

				break;
			default: printf("\nErrore!Riprova!\n");
		}

	}while(numScelta!=0);


	return 0;
}






int cancella_iesimo_pasto_da_file(int indicePasto,alimento alimenti[],ricetta ricette[]){
	FILE *fileStoricoPasti;
	pasto pp;

	if ((fileStoricoPasti = fopen("src/Storico_Pasti.sf", "rb+")) == NULL) {
		printf("Errore nell'apertura del file!\n");
		return 0;
	} else {
		fseek(fileStoricoPasti,indicePasto*sizeof(pasto),SEEK_SET);
		fread(&pp,sizeof(pasto),1,fileStoricoPasti);
		pp.visibilita=false;

		//bisogna aggiungere tutte le quantita cancellate
		int i;
		for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
			if(ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i] != -1) {
				alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]].Scadenze[0].Quantita += ricette[pp.ID_Ricetta].Alimenti_Quantita[1][i]*pp.Porzioni;
				if(alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]].Visibilita==false) alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[1][i]].Visibilita=true;
				modifica_alimento_su_file(alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]]);
			}
		}

		fseek(fileStoricoPasti,indicePasto*sizeof(pasto),SEEK_SET);
		fwrite(&pp,sizeof(pasto),1,fileStoricoPasti);

		fclose(fileStoricoPasti);
	}

	return 1;
}




int cancella_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[]){

	data_ora dataPasto,dataOdierna;
	FILE *file_Storico_Pasti;
	pasto past;
	int indice=0;
	int lunghezzaVettoreIndici=Get_Lunghezza_File_Storico_Pasti();
	int indiciSuFile[lunghezzaVettoreIndici];
	int indiceVetIndici=0;

	printf("\n\nCancellazione Pasto\n\%s\n",STRINGASTERISCHI);

	do{
		indice=0;
		get_data_pointer(&dataOdierna);
		get_data_input(&dataPasto.Giorno,&dataPasto.Mese,&dataPasto.Anno,"\nInserisci la data in cui e' stato consumato il pasto da cancellare:");

		//se la distanza tra le 2 date e' maggiore uguale a 0 vuol dire che la
		//data inserita e' uguale o meno recente del giorno odierno
		if(get_distanza_in_giorni(dataPasto,dataOdierna,0) < 0 ) printf("\nData non valida! Reinseriscila!\n");
		else{
			if ((file_Storico_Pasti = fopen("src/Storico_Pasti.sf", "rb")) == NULL) {
				printf("Errore nell'apertura del file!\n");
				return 0;
			} else {

				printf("\n%5s | %20s | %5s\n","N","Ricetta","Porzioni");
				printf("-----------------------------------------------------");
				while(!feof(file_Storico_Pasti)){
					if(fread(&past,sizeof(past),1,file_Storico_Pasti) > 0){
						//se le date sono le stesse avranno una distanza in giorni pari a 0
						if(get_distanza_in_giorni(past.Data_Ora,dataPasto,0) == 0 && past.visibilita==true){
							printf("\n%5d | %20s | %5d",indiceVetIndici,ricette[past.ID_Ricetta].Nome,past.Porzioni);
							indiciSuFile[indiceVetIndici]=indice;
							indiceVetIndici++;
						}

					}
					indice++;
				}
				printf("\n\n");
				int sceltaIndice;
				do{
					sceltaIndice=fai_scelta("\nInserisci il numero corrispondente al pasto che si vuole cancellare:");

					if(sceltaIndice>indiceVetIndici) printf("\nIndice non valido! Reinseriscilo!\n");

				}while(sceltaIndice>indiceVetIndici);

				if(cancella_iesimo_pasto_da_file(indiciSuFile[sceltaIndice],alimenti,ricette)) printf("\nCancellazione del pasto effettuata con successo!\n");
				else printf("\nErrore nella cancellazione del pasto su file!\n");

			}
		}
	}while(get_distanza_in_giorni(dataPasto,dataOdierna,0) < 0 );

	return 1;
}







int scelta_opzioni_pasti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	int NumScelta;

	do {
		NumScelta = fai_scelta(MENU_PASTI);

		switch (NumScelta) {
		case 1:

			//Visualizzazione del menu settimanale
			scelta_opzioni_visualizza_menu_settimanale(ricette,lunghezzaVettoreRicette);

			break;
		case 2:

			//aggiungi pasto
			aggiungi_pasto(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;
		case 3:

			//modifica pasto

			break;
		case 4:

			//cancella pasto
			cancella_pasto(ricette,lunghezzaVettoreRicette,alimenti);

			break;
		case 0:
			//case di uscita dal sottomenu
			break;
		default:
			printf("Scelta errata! Riprova!\n");
		}

	} while (NumScelta != 0);

	return 0;
}

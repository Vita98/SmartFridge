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





int Aggiungi_Pasto_Su_File(int numPorzioni,int Id_Ricetta){

	FILE *file;
	pasto pp;

	pp.ID_Ricetta=Id_Ricetta;
	pp.Porzioni=numPorzioni;

	getData2(&pp.Data_Ora);

	pp.Data_Ora.Giorno=4;
	pp.Data_Ora.Mese=6;

	if ((file = fopen("src/Storico_Pasti.sf", "ab+")) == NULL) {
			printf("Errore nell'apertura del file!\n");
			return 0;
	} else {
		fwrite(&pp,sizeof(pasto),1,file);

		fclose(file);
		return 1;
	}

}






int Aggiungi_Pasto(ricetta ricette[],int lunghezza_vettore_ricette){


	printf("\n\nAggiungi un pasto\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta che vuoi consumare:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice,numPorzioni;

	if ((indice=getRicetta(ricette, lunghezza_vettore_ricette,scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nRicetta Trovata\n\n");

		do{
			numPorzioni=FaiScelta("Inserisci il numero di porzioni che si intende consumare: ");
			if(numPorzioni==0) printf("\nScelta non valida! Riprova!\n");
		}while(numPorzioni==0);

		if(Aggiungi_Pasto_Su_File(numPorzioni,indice)) printf("\nPasto registrato con successo! %s\n",getTipoPasto());
		else printf("\nErrore nella memorizzazione del pasto su file!\n");

	}

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
int Stampa_Iesimo_Menu_Settimanale(ricetta ricette[],int lunghezza_vettore_ricette,int NumeroSettimana,int giornoSettimana){

	int i;

	FILE *file;
	pasto pp;
	data_ora d;
	getData2(&d);
	boolean flag;
	int delay=0;

	//vuol dire che la funzione viene chiamata per visualizzare settimane precedenti a quella corrente
	//devo aggiungere un delay in quanto la data inserita dall'utente puo essere una data
	//mediana della settimana e quindi per far visualizzare tutta la settimana bisogna aggiungere
	//i giorni mancanti infatti delay andra' poi sommato alla distanza tra le 2 date
	if(NumeroSettimana!=0){
		delay=getData('W');
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
				fread(&pp,sizeof(pasto),1,file);

				//controllo che la distanza tra la data attuale e la data del pasto letta da file
				//sia uguale alla distanza tra il giorno della settimana che si vuole visualizzare
				//e la data attuale
				if(getDistanzaInGiorni(pp.Data_Ora,d,delay) == (i+(NumeroSettimana*NUMERO_GIORNI))){

					//controllo se e' il primo ad essere trovato o no
					if(flag==false){
						printf("\n%15s | %20s | %15d",indiceToGiorniSettimana(giornoSettimana-i),ricette[pp.ID_Ricetta].Nome,pp.Porzioni);
						//printf("\n%20s | %15s\n","Ricetta","Porzioni");
						flag=true;
					}else printf("\n%15s | %20s | %15d","-" ,ricette[pp.ID_Ricetta].Nome,pp.Porzioni);
				}
			}
			if(flag==false) printf("\n%15s | %20s | %15s",indiceToGiorniSettimana(giornoSettimana-i),"-","-");
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
int Visualizza_Menu_Settimana_In_Corso(ricetta ricette[],int lunghezza_vettore_ricette){

	//Richiamo la funzione di stampa del menu della iesima settimana
	//in maniera che stampi la settimana corrente
	Stampa_Iesimo_Menu_Settimanale(ricette,lunghezza_vettore_ricette,0,getData('W'));

	return 1;

}






/* FUNZIONE CHE GESTISCE LA CHIAMATA DELLA FUNZIONE PER *
 * LA VISUALIZZAZIONE DEL MENU SETTIMANALE DI SETTIMANE *
 * PASSATE A QUELLA CORRENTE*/
int Visualizza_Menu_Settimane_Passate(ricetta ricette[],int lunghezza_vettore_ricette){

	data_ora dataInput;
	data_ora dataCorrente;
	boolean flag;


	do{
		flag=false;
		getData2(&dataCorrente);
		getDataInput(&dataInput.Giorno,&dataInput.Mese,&dataInput.Anno,"\nInserisci la data di un giorno della settimana di cui si vuole vedere il menu settimanale: ");

		//calcolo la distanza tra la settimana corrente e la settimana inserita in input
		int distanza=getDistanzaInGiorni(dataInput,dataCorrente,0);

		if(distanza>=0){
			//calcolo quante settimane a ritroso devo andare
			//per visualizzare lo storico pasti della settimana presa in input
			distanza-=dataToGiorniSettimana(dataCorrente);
			int i,NumeroSettimane=0;
			for(i=0;distanza>=1;i++){
				NumeroSettimane++;
				distanza-=7;
			}

			flag=true;

			//se il numero settimane e' diverso da 0 vuol dire che devo andare
			//a ritrono di NumeroSettimane SETTIMANE
			if(NumeroSettimane!=0){
				Stampa_Iesimo_Menu_Settimanale(ricette,lunghezza_vettore_ricette,NumeroSettimane,6);

			}else 	Stampa_Iesimo_Menu_Settimanale(ricette,lunghezza_vettore_ricette,0,getData('W'));
		}else{
			//caso in cui la data inserita in input sia sucessiva alla data corrente
			printf("\nLa data non puo essere superiore alla data corrente! Reinseriscila!\n");
		}
	}while(flag==false);


	return 1;
}







int Scelta_Opzioni_Visualizza_Menu_Settimanale(ricetta ricette[],int lunghezza_vettore_ricette){

	printf("\n\nVisualizzazione Menu Settimanale\n%s\n",STRINGASTERISCHI);

	int NumScelta;

	do{

		NumScelta=FaiScelta(MenuOpzioniVisualizzazioneMenuSettimanale);

		switch(NumScelta){
			case 1:
				//visualizzazione menu settimana in corso
				Visualizza_Menu_Settimana_In_Corso(ricette,lunghezza_vettore_ricette);
				break;
			case 2:
				//visualizzazione menu settimane passate
				Visualizza_Menu_Settimane_Passate(ricette,lunghezza_vettore_ricette);
				break;
			case 0:

				break;
			default: printf("\nErrore!Riprova!\n");
		}

	}while(NumScelta!=0);


	return 0;
}







int Scelta_Opzioni_Pasti(ricetta ricette[],int lunghezza_vettore_ricette,alimento alimenti[],int Lunghezza_vettore_alimenti){

	int NumScelta;

	do {
		NumScelta = FaiScelta(MenuPasti);

		switch (NumScelta) {
		case 1:

			//Visualizzazione del menu settimanale
			Scelta_Opzioni_Visualizza_Menu_Settimanale(ricette,lunghezza_vettore_ricette);

			break;
		case 2:

			//aggiungi pasto
			Aggiungi_Pasto(ricette,lunghezza_vettore_ricette);

			break;
		case 3:

			//modifica pasto

			break;
		case 4:

			//cancella pasto

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

/*
 * Alimenti_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */
#include "Tipi_Dato.h"
#include <String.h>
#include "Data_Tools.h"





/* FUNZIONE CHE RECUPERA DAL VETTORE DELLE SCADENZE			*
 * LA QUANTITA' DELL'ALIMENTO PASSATO TRAMITE IL PARAMETRO	*/
int getQuantita(alimento alim) {

	int quantita = 0, j;
	for (j = 0; j < LUNGHEZZA_VET_SCADENZE; j++) {
		quantita += alim.Scadenze[j].Quantita;
	}
	return quantita;
}





/* FUNZIONE CHE SERVE PER VERIFICARE SE ESISTE GIA LA DATA DI		*
 * SCADENZA PASSATA COME PARAMETRO ALL'INTERNO DEL VETTORE DI 	 	*
 * SCADENZE DELL'ALIMENTO alim ANCHESSO PASSATO COME PARAMETRO		*
 * 																	*
 * LA FUNZIONE RITORNA -1 SE NON VIENE TROVATA NESSUNA 				*
 * CORRISPONDENZA, ALTRIMENTI RITORNA LA POSIZIONE DELLA PRIMA 		*
 * OCCORRENZA														*/
int getDataScadenza(alimento alim,data_ora data){

	int i;
	for(i=0;i<LUNGHEZZA_VET_SCADENZE;i++){
		if(alim.Scadenze[i].Data_Scadenza.Anno == data.Anno)
		if(alim.Scadenze[i].Data_Scadenza.Mese == data.Mese)
		if(alim.Scadenze[i].Data_Scadenza.Giorno == data.Giorno){
			return i;
		}
	}

	return -1;

}





/* FUNZIONE CHE SERVE PER VERIFICARE SE ESISTE L'ALIMENTO PASSATO	*
 * COME PARAMETRO Parametri_Ricerca NEL VETTORE DI ALIMENTI			*
 * 																	*
 * SE IL PARAMETRO Visibilita E' true CONTROLLA TRA TUTTI GLI		*
 * ALIMENTI CON VISIBILITA true 									*
 * ALTRIMENTI CONTROLLA ANCHE TRA QUALLI 'CANCELLATI'				*
 * 																	*
 * LA FUNZIONE ELIMINA TUTTI GLI SPAZI FINALI E INIZIALI DELLE DUE	*
 * STRINGHE E INOLTRE NE CREA UNA COPIA IN MINUSCOLO				*
 * 																	*
 * LA FUNZIONE RITORNA -1 SE NON VIENE TROVATA NESSUNA 				*
 * CORRISPONDENZA, ALTRIMENTI RITORNA LA POSIZIONE DELLA PRIMA 		*
 * OCCORRENZA														*/
int getAlimento(alimento alimenti[], int Lunghezza_Alimenti,
		char Parametri_Ricerca[],boolean visibilita) {

	int i;
	char StringTempParametri[LUNGHEZZA_STRINGA];
	removeFirstLastSpace(Parametri_Ricerca, StringTempParametri,
			LUNGHEZZA_STRINGA);
	toLowerString(StringTempParametri, StringTempParametri);

	for (i = 0; i < Lunghezza_Alimenti; i++) {
		char StringTempVettore[LUNGHEZZA_STRINGA];
		removeFirstLastSpace(alimenti[i].Nome, StringTempVettore,
				LUNGHEZZA_STRINGA);
		toLowerString(StringTempVettore, StringTempVettore);

		//se le due stringhe sono uguali
		if (strcmp(StringTempParametri, StringTempVettore) == 0)
		if(alimenti[i].Visibilita || alimenti[i].Visibilita==visibilita)	return i;
	}

	return -1;
}








/* FUNZIONE CHE HA IL COMPITO DI VISUALIZZARE IN CONSOLE 	*
 * LE INFORMAZIONI DI GLI ALIMENTI PRESENTI NEL VETTORE		*
 * 															*
 * RITORNA 1 SE L'OPERAZIONE E' ANDATA A BUON FINE			*/
int Visualizza_Alimenti(alimento alimenti[], int Lunghezza_Vettore) {

	int i;

	printf("Alimenti presenti:\n");
	for (i = 0; i < Lunghezza_Vettore ; i++) {

		printf("%d - %s \t| Peso: %d \t| Id: %d   |   Quantita: %d   | Kcal: %.3f  | V:%s\n", i,
		alimenti[i].Nome, alimenti[i].Peso, alimenti[i].ID_Alimento,
		getQuantita(alimenti[i]),alimenti[i].Kcal_Pezzo,(alimenti[i].Visibilita)?"true":"false");
	}
	return 1;
}






/* FUNZIONE CHE APPLICA LE MODIFICHE EFFETTUATE		*
 * PRECEDENTEMENTE NELL'ALIMENTO ALL'INTERNO DEL 	*
 * FILE NELLA CORRETTA POSIZIONE					*
 * 													*
 * LA FUNZIONE RITORNA 1 SE LA PROCEDURA È ANDATA 	*
 * A BUON FINE ALTRIMENTI 0*/
int Modifica_Alimento_Su_File(alimento alim){
	FILE *file;

	if ((file = fopen("src/Alimenti.sf", "rb+")) == NULL) return 0;
	else {
		fseek(file,alim.ID_Alimento*sizeof(alimento),SEEK_SET);
		fwrite(&alim,sizeof(alimento),1,file);

		fclose(file);
		return 1;
	}

}





/* FUNZIONE CHE AGGIUNGE L'ALIMENTO PASSATO COME	*
 * PARAMETRO IN CODA AL FILE DI ALIMENTI			*
 * 													*
 * SE L'AGGIUNTA È ANDATA A BUON FINE LA FUNZIONE	*
 * RESTITUISCE 1, ALTRIMENTI 0						*/
int Aggiungi_Alimento_Su_File(alimento alim){
	FILE *file;

	if ((file = fopen("src/Alimenti.sf", "ab+")) == NULL) {
			printf("Errore nell'apertura del file!\n");
			return 0;
	} else {
		fwrite(&alim,sizeof(alimento),1,file);

		fclose(file);
		return 1;
	}

}





/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE IL NOME		*
 * DELL'ALIMENTO CON INDICE indice PASSATO COME PARAMETRO		*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT IL VALORE E LO AGGIORNA SIA SUL 	*
 * VETTORE DI ALIMENTI CHE SU FILE E INOLTRE VIENE CONTROLLATO	*
 * SE IL NOME INSERITO DALL'UTENTE È GIA ESISTENTE E QUINDI		*
 * UTILIZZABILE O NO			 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int Modifica_Nome_Alimento(alimento alimenti[],int Lunghezza_Vettore,int indice){

	char scelta[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		printf("\nInserisci il nuovo nome dell'Alimento:\n");
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);


		if(getAlimento(alimenti,Lunghezza_Vettore,scelta,false) > -1){
			 printf("\nQuesto nome gia esiste!\n");
		}else flag=true;

	}while(strlen(scelta) == 0 || flag==false);

	//Effettuo la modifica sul vettore presente in memoria
	strcpy(alimenti[indice].Nome,scelta);


	//Effettuo la modifica su file
	if(Modifica_Alimento_Su_File(alimenti[indice]) == 1) printf("\nModifica del nome avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica del nome su file!\n");
	}

	return 1;

}





/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE LE KCAL		*
 * DELL'ALIMENTO CON INDICE indice PASSATO COME PARAMETRO		*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT IL VALORE E LO AGGIORNA SIA SUL 	*
 * VETTORE DI ALIMENTI CHE SU FILE 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int Modifica_kcal_Alimento(alimento alimenti[],int indice){
	double Kcal=0.0;

	Kcal=FaiSceltaDouble("\nInserisci le nuove kcal dell'Alimento:\n");

	//effettuo la modifica nel vettore
	alimenti[indice].Kcal_Pezzo=Kcal;

	//effettuo la modifica su file
	if(Modifica_Alimento_Su_File(alimenti[indice]) == 1) printf("\nModifica delle Kcal avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica delle Kcal su file!\n");
	}

	return 1;
}






/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE IL PESO		*
 * DELL'ALIMENTO CON INDICE indice PASSATO COME PARAMETRO		*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT IL VALORE E LO AGGIORNA SIA SUL 	*
 * VETTORE DI ALIMENTI CHE SU FILE 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int Modifica_Peso_Alimento(alimento alimenti[],int indice){
	int peso=0;
	char stringa[LUNGHEZZA_STRINGA];

	do{
		printf("\nInserisci il nuovo peso dell'Alimento:\n");

		fgets(stringa,LUNGHEZZA_STRINGA,stdin);

		if(isNumber(stringa)) peso=toNumber(stringa);

	}while(!isNumber(stringa));

	//effettuo la modifica nel vettore
	alimenti[indice].Peso=peso;

	//effettuo la modifica su file
	if(Modifica_Alimento_Su_File(alimenti[indice]) == 1) printf("\nModifica del peso avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica del peso su file!\n");
	}

	return 1;
}






/* FUNZIONE CHE HA IL COMPITO DI VISUALIZZARE IN CONSOLE	*
 * ALL'UTENTE TUTTE LE QUANTITA E LE DATE DI SCADENZA 		*
 * PRESENTI NEL VETTORE SCADENZE DELL'ALIMENTO CON INDICE	*
 * indice PASSATO COME PARAMETRO							*
 * 															*
 * RITORNA 1 SE TUTTO È ANDATO BENE							*/
int Visualizza_Quantita_Scadenze(alimento alimenti[],int indice){
	printf("\n N | %s    |     %s\n","Quantita","Scadenza");
	printf("------------------------------------\n");
	int i;
	for(i=0;i<LUNGHEZZA_VET_SCADENZE;i++){
		if(alimenti[indice].Scadenze[i].Quantita != 0){
			printf("%2d | %5d       |    %d/%d/%d\n",i,alimenti[indice].Scadenze[i].Quantita,alimenti[indice].Scadenze[i].Data_Scadenza.Giorno,alimenti[indice].Scadenze[i].Data_Scadenza.Mese,alimenti[indice].Scadenze[i].Data_Scadenza.Anno);
		}
	}
	return 1;
}





/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE LA QUANTITA	*
 * DELL'ALIMENTO CON INDICE indice PASSATO COME PARAMETRO		*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT IL VALORE E LO AGGIORNA SIA SUL 	*
 * VETTORE DI ALIMENTI CHE SU FILE 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int Modifica_Quantita_Alimento(alimento alimenti[],int indice){
	printf("\n\nModifica Quantita alimento\n");

	Visualizza_Quantita_Scadenze(alimenti,indice);

	int NumeroScelta;
	boolean flag;

	do{
		flag=false;
		NumeroScelta=FaiScelta("\nInserisci il numero N corrispondente alla quantita\nche si vuole modificare riportata nella tabella in alto:\n");
		if(NumeroScelta>LUNGHEZZA_VET_SCADENZE) {
			printf("\nScelta non valida!\n");
			flag=true;
		}else if(alimenti[indice].Scadenze[NumeroScelta].Quantita==0){
			printf("\nScelta non valida!\n");
			flag=true;
		}
	}while(flag);

	int Nuova_Quantita=FaiScelta("\nInserisci la nuova quantita:");

	//modifica del vettore
	alimenti[indice].Scadenze[NumeroScelta].Quantita=Nuova_Quantita;

	//modifica del file
	if(Modifica_Alimento_Su_File(alimenti[indice]) == 1) printf("\nModifica della quantita avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica della quantita su file!\n");
	}

	return 1;
}






/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE IL VETTORE	*
 * SCADENZE DELL'ALIMENTO CON INDICE indice PASSATO COME 		*
 * PARAMETRO													*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT I VALORI E LI AGGIORNA SIA SUL 	*
 * VETTORE DI ALIMENTI CHE SU FILE 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int Modifica_Scadenze_Alimento(alimento alimenti[],int indice){
	printf("\n\nModifica Scadenza alimento\n");

	Visualizza_Quantita_Scadenze(alimenti,indice);


	int NumeroScelta;
	boolean flag;

	do{
		flag=false;
		NumeroScelta=FaiScelta("\nInserisci il numero N corrispondente alla scadenza\nche si vuole modificare riportata nella tabella in alto:\n");
		if(NumeroScelta>LUNGHEZZA_VET_SCADENZE) {
			printf("\nScelta non valida!\n");
			flag=true;
		}else if(alimenti[indice].Scadenze[NumeroScelta].Quantita==0){
			printf("\nScelta non valida!\n");
			flag=true;
		}
	}while(flag);

	char data[LUNGHEZZA_STRINGA];
	int giorno,mese,anno;

	do{
		flag=false;
		printf("\nInserisci la nuova data di scadenza:");
		fgets(data,LUNGHEZZA_STRINGA,stdin);

		if(ControlloData(data,&giorno,&mese,&anno)){
			 printf("\nData errata! Reinseriscila!\n");
			 flag=true;
		}

	}while(flag);

	//modifica nel vettore
	alimenti[indice].Scadenze[NumeroScelta].Data_Scadenza.Anno=anno;
	alimenti[indice].Scadenze[NumeroScelta].Data_Scadenza.Mese=mese;
	alimenti[indice].Scadenze[NumeroScelta].Data_Scadenza.Giorno=giorno;

	//modifica nel file
	if(Modifica_Alimento_Su_File(alimenti[indice]) == 1) printf("\nModifica della quantita avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica della quantita su file!\n");
	}

	return 1;
}







/* FUNZIONE CHE EFFETTUA LA MODIFICA DI UN DETERMINATO		*
 * ALIMENTO CHIESTO IN INPUT NELLA STESSA FUNZIONE			*/
int Modifica_Alimento(alimento alimenti[], int Lunghezza_Vettore) {

	printf("\n\n             Modifica Alimento\n");
	printf("\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice;

	if ((indice=getAlimento(alimenti, Lunghezza_Vettore, scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nAlimento Trovato\n\n");



		//devo fare la modifica effettiva
		int NumScelta=1;
		do{
			NumScelta=FaiScelta(MenuModificaAlimenti);

			switch(NumScelta){
				case 1:
					//modifica nome

					Modifica_Nome_Alimento(alimenti,Lunghezza_Vettore,indice);

					break;
				case 2:
					//modifica kcal

					Modifica_kcal_Alimento(alimenti,indice);

					break;
				case 3:
					//modifica peso

					Modifica_Peso_Alimento(alimenti,indice);

					break;
				case 4:
					//modifica quantita

					Modifica_Quantita_Alimento(alimenti,indice);

					break;
				case 5:
					//modifica scadenze

					Modifica_Scadenze_Alimento(alimenti,indice);

					break;
				case 0:
					//case di uscita dal sottomenu
					break;
				default:
					printf("Scelta errata! Riprova!\n");
			}

		} while (NumScelta != 0);


	} else
		printf("\n\nNon esiste nessun alimento che si chiama in quel modo!\n\n");

	return 1;
}






/* FUNZIONE CHE GESTISCE IL MENU RELATIVO AGLI ALIMENTI		*
 * CHIEDE ALL'UNTETE DI FARE UNA SCELTA E CONTROLLA CHE		*
 * LA SCELTA SIA VALIDA; 									*
 * SE LO E' RICHIAMA LE OPPORTUNE FUNZIONI CHE ESEGUONO		*
 * IL PARTOCOLARE COMPITO									*/
int Scelta_Opzioni_Alimenti(alimento alimenti[], int Lunghezza_Alimenti) {
	int NumScelta=1;

	do {
		NumScelta = FaiScelta(MenuAlimenti);

		switch (NumScelta) {
		case 1:

			//visualizza alimenti
			Visualizza_Alimenti(alimenti, Lunghezza_Alimenti);

			break;
		case 2:

			//modifica dell'alimento
			Modifica_Alimento(alimenti, Lunghezza_Alimenti);

			break;
		case 0:
			//case di uscita dal sottomenu
			break;
		default:
			printf("Scelta errata! Riprova!\n");
		}

	} while (NumScelta != 0);

	/*AGGIUNTA DELL'ALIMENTO CON LA SPESA*/


	return 1;
}

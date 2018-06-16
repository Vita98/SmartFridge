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
int get_quantita(alimento alim) {

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
int get_data_scadenza(alimento alim,data_ora data){

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
int get_alimento(alimento alimenti[], int lunghezzaVettoreAlimenti,
		char parametriRicerca[],boolean visibilita) {

	int i;
	char stringTempParametri[LUNGHEZZA_STRINGA];
	remove_first_last_space(parametriRicerca, stringTempParametri,
			LUNGHEZZA_STRINGA);
	to_lower_string(stringTempParametri, stringTempParametri);

	for (i = 0; i < lunghezzaVettoreAlimenti; i++) {
		char StringTempVettore[LUNGHEZZA_STRINGA];
		remove_first_last_space(alimenti[i].Nome, StringTempVettore,
				LUNGHEZZA_STRINGA);
		to_lower_string(StringTempVettore, StringTempVettore);

		//se le due stringhe sono uguali
		if (strcmp(stringTempParametri, StringTempVettore) == 0)
		if(alimenti[i].Visibilita || alimenti[i].Visibilita==visibilita)	return i;
	}

	return -1;
}








/* FUNZIONE CHE HA IL COMPITO DI VISUALIZZARE IN CONSOLE 	*
 * LE INFORMAZIONI DI GLI ALIMENTI PRESENTI NEL VETTORE		*
 * 															*
 * RITORNA 1 SE L'OPERAZIONE E' ANDATA A BUON FINE			*/
int visualizza_alimenti(alimento alimenti[], int lunghezzaVettoreAlimenti) {

	int i;

	printf("Alimenti presenti:\n");
	for (i = 0; i < lunghezzaVettoreAlimenti ; i++) {

		printf("%d - %30s \t| Peso: %5d \t| Id: %3d   |   Quantita: %5d   | Kcal: %5.3f  | V:%s\n", i,
		alimenti[i].Nome, alimenti[i].Peso, alimenti[i].ID_Alimento,
		get_quantita(alimenti[i]),alimenti[i].Kcal_Pezzo,(alimenti[i].Visibilita)?"true":"false");
	}
	return 1;
}






/* FUNZIONE CHE APPLICA LE MODIFICHE EFFETTUATE		*
 * PRECEDENTEMENTE NELL'ALIMENTO ALL'INTERNO DEL 	*
 * FILE NELLA CORRETTA POSIZIONE					*
 * 													*
 * LA FUNZIONE RITORNA 1 SE LA PROCEDURA È ANDATA 	*
 * A BUON FINE ALTRIMENTI 0*/
int modifica_alimento_su_file(alimento alim){
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
int aggiungi_alimento_su_file(alimento alim){
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
int modifica_nome_alimento(alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceAlimento){

	char scelta[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		printf("\nInserisci il nuovo nome dell'Alimento:\n");
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);


		if(get_alimento(alimenti,lunghezzaVettoreAlimenti,scelta,false) > -1){
			 printf("\nQuesto nome gia esiste!\n");
		}else flag=true;

	}while(strlen(scelta) == 0 || flag==false);

	//Effettuo la modifica sul vettore presente in memoria
	strcpy(alimenti[indiceAlimento].Nome,scelta);


	//Effettuo la modifica su file
	if(modifica_alimento_su_file(alimenti[indiceAlimento]) == 1) printf("\nModifica del nome avvenuta con successo!\n");
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
int modifica_kcal_alimento(alimento alimenti[],int indiceAlimento){
	double Kcal=0.0;

	Kcal=fai_scelta_double("\nInserisci le nuove kcal dell'Alimento:\n");

	//effettuo la modifica nel vettore
	alimenti[indiceAlimento].Kcal_Pezzo=Kcal;

	//effettuo la modifica su file
	if(modifica_alimento_su_file(alimenti[indiceAlimento]) == 1) printf("\nModifica delle Kcal avvenuta con successo!\n");
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
int modifica_peso_alimento(alimento alimenti[],int indiceAlimento){
	int peso=0;
	char stringa[LUNGHEZZA_STRINGA];

	do{
		printf("\nInserisci il nuovo peso dell'Alimento:\n");

		fgets(stringa,LUNGHEZZA_STRINGA,stdin);

		if(is_number(stringa)) peso=to_number(stringa);

	}while(!is_number(stringa));

	//effettuo la modifica nel vettore
	alimenti[indiceAlimento].Peso=peso;

	//effettuo la modifica su file
	if(modifica_alimento_su_file(alimenti[indiceAlimento]) == 1) printf("\nModifica del peso avvenuta con successo!\n");
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
int visualizza_quantita_scadenze(alimento alimenti[],int indiceAlimento){
	printf("\n N | %s    |     %s\n","Quantita","Scadenza");
	printf("------------------------------------\n");
	int i;
	for(i=0;i<LUNGHEZZA_VET_SCADENZE;i++){
		if(alimenti[indiceAlimento].Scadenze[i].Quantita != 0){
			printf("%2d | %5d       |    %d/%d/%d\n",i,alimenti[indiceAlimento].Scadenze[i].Quantita,alimenti[indiceAlimento].Scadenze[i].Data_Scadenza.Giorno,alimenti[indiceAlimento].Scadenze[i].Data_Scadenza.Mese,alimenti[indiceAlimento].Scadenze[i].Data_Scadenza.Anno);
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
int modifica_quantita_alimento(alimento alimenti[],int indiceAlimento){
	printf("\n\nModifica Quantita alimento\n");

	visualizza_quantita_scadenze(alimenti,indiceAlimento);

	int numeroScelta;
	boolean flag;

	do{
		flag=false;
		numeroScelta=fai_scelta("\nInserisci il numero N corrispondente alla quantita\nche si vuole modificare riportata nella tabella in alto:\n");
		if(numeroScelta>LUNGHEZZA_VET_SCADENZE) {
			printf("\nScelta non valida!\n");
			flag=true;
		}else if(alimenti[indiceAlimento].Scadenze[numeroScelta].Quantita==0){
			printf("\nScelta non valida!\n");
			flag=true;
		}
	}while(flag);

	int nuovaQuantita=fai_scelta("\nInserisci la nuova quantita:");

	//modifica del vettore
	alimenti[indiceAlimento].Scadenze[numeroScelta].Quantita=nuovaQuantita;

	//modifica del file
	if(modifica_alimento_su_file(alimenti[indiceAlimento]) == 1) printf("\nModifica della quantita avvenuta con successo!\n");
	else printf("\nErrore nella modifica della quantita su file!\n");

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
int modifica_scadenze_alimento(alimento alimenti[],int indiceAlimento){
	printf("\n\nModifica Scadenza alimento\n");

	visualizza_quantita_scadenze(alimenti,indiceAlimento);


	int NumeroScelta;
	boolean flag;

	do{
		flag=false;
		NumeroScelta=fai_scelta("\nInserisci il numero N corrispondente alla scadenza\nche si vuole modificare riportata nella tabella in alto:\n");
		if(NumeroScelta>LUNGHEZZA_VET_SCADENZE) {
			printf("\nScelta non valida!\n");
			flag=true;
		}else if(alimenti[indiceAlimento].Scadenze[NumeroScelta].Quantita==0){
			printf("\nScelta non valida!\n");
			flag=true;
		}
	}while(flag);

	data_ora data;

	get_data_input(&data.Giorno,&data.Mese,&data.Anno,"\nInserisci la nuovo data di scadenza: ");

	//modifica nel vettore
	alimenti[indiceAlimento].Scadenze[NumeroScelta].Data_Scadenza.Anno=data.Anno;
	alimenti[indiceAlimento].Scadenze[NumeroScelta].Data_Scadenza.Mese=data.Mese;
	alimenti[indiceAlimento].Scadenze[NumeroScelta].Data_Scadenza.Giorno=data.Giorno;

	//modifica nel file
	if(modifica_alimento_su_file(alimenti[indiceAlimento]) == 1) printf("\nModifica della data di scadenza avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica della quantita su file!\n");
	}

	return 1;
}







/* FUNZIONE CHE HA IL COMPITO DI SOTTRARRE AL VETTORE DI	*
 * SCADENZE E QUANTITA DELL'ELEMENTO UNA QUANTITA PASSATA	*
 * COME PARAMETRO. 											*
 * 															*
 * VIENE USATA QUANDO PER ESEMPIO VIENE CONSUMATO UN PASTO	*
 * E BISOGNA SOTTRARRE LE QUANTITA CONSUMATE A QUELLE 		*
 * DISPONIBILI												*/
int decrementa_quantita_alimento(alimento* alim, int quantita){
	int  j;
	for (j = LUNGHEZZA_VET_SCADENZE-1; j >= 0; j--) {
		if((*alim).Scadenze[j].Quantita>=quantita){
			(*alim).Scadenze[j].Quantita-=quantita;
			 quantita=0;
			 if(j==0){
				 (*alim).Visibilita=false;
				 modifica_alimento_su_file((*alim));
			 }
			 break;
		}
		else{
			quantita=quantita-(*alim).Scadenze[j].Quantita;
			(*alim).Scadenze[j].Quantita=0;
		}
	}
	return 1;
}







/* FUNZIONE CHE EFFETTUA LA MODIFICA DI UN DETERMINATO		*
 * ALIMENTO CHIESTO IN INPUT NELLA STESSA FUNZIONE			*/
int modifica_alimento(alimento alimenti[], int lunghezzaVettoreAlimenti) {

	printf("\n\n             Modifica Alimento\n");
	printf("\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice;

	if ((indice=get_alimento(alimenti, lunghezzaVettoreAlimenti, scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nAlimento Trovato\n\n");



		//devo fare la modifica effettiva
		int NumScelta=1;
		do{
			NumScelta=fai_scelta(MENU_MODIFICA_ALIMENTI);

			switch(NumScelta){
				case 1:
					//modifica nome

					modifica_nome_alimento(alimenti,lunghezzaVettoreAlimenti,indice);

					break;
				case 2:
					//modifica kcal

					modifica_kcal_alimento(alimenti,indice);

					break;
				case 3:
					//modifica peso

					modifica_peso_alimento(alimenti,indice);

					break;
				case 4:
					//modifica quantita

					modifica_quantita_alimento(alimenti,indice);

					break;
				case 5:
					//modifica scadenze

					modifica_scadenze_alimento(alimenti,indice);

					break;
				case 0:
					//case di uscita dal sottomenu
					break;
				default:
					printf("Scelta errata! Riprova!\n");
			}

		} while (NumScelta != 0);


	} else printf("\n\nNon esiste nessun alimento che si chiama in quel modo!\n\n");

	return 1;
}






/* FUNZIONE CHE GESTISCE IL MENU RELATIVO AGLI ALIMENTI		*
 * CHIEDE ALL'UNTETE DI FARE UNA SCELTA E CONTROLLA CHE		*
 * LA SCELTA SIA VALIDA; 									*
 * SE LO E' RICHIAMA LE OPPORTUNE FUNZIONI CHE ESEGUONO		*
 * IL PARTOCOLARE COMPITO									*/
int scelta_opzioni_alimenti(alimento alimenti[], int lunghezzaVettoreAlimenti) {
	int NumScelta=1;

	do {
		NumScelta = fai_scelta(MENU_ALIMENTI);

		switch (NumScelta) {
		case 1:

			//visualizza alimenti
			visualizza_alimenti(alimenti, lunghezzaVettoreAlimenti);

			break;
		case 2:

			//modifica dell'alimento
			modifica_alimento(alimenti, lunghezzaVettoreAlimenti);

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

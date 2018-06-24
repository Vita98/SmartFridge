/*
 * Ricette_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <String.h>
#include "Alimenti_Tools.h"
#include "Preferiti_Tools.h"
#include "Ordinamenti_Tools.h"














int visualizza_ricette_ordinate(ricetta ricette[], int lunghezzaVettoreRicette, int modalitaOrdinamento) {

	int i;
	int indici[lunghezzaVettoreRicette];

	printf("Ricette presenti ");
	printf ("(%d) :\n",lunghezzaVettoreRicette);


	sort_ricette(ricette, indici, lunghezzaVettoreRicette, modalitaOrdinamento);

	for (i = 0; i <lunghezzaVettoreRicette ; i++) {

		if (ricette[indici[i]].Visibilita==true){
			printf("%d - %30s \t| Kcal per porzione: %5.2f \t| Id: %3d  |  Freq: %5d  |  Visib: %s\n", i,
							ricette[indici[i]].Nome, ricette[indici[i]].Kcal_Porzione, ricette[indici[i]].ID_Ricetta, ricette[indici[i]].Frequenza,(ricette[indici[i]].Visibilita)?"true":"false");
		}


	}


	return 1;
}






int visualizza_ricette(ricetta ricette[], int lunghezzaVettoreRicette) {

	int i;

	printf("Ricette presenti ");
	printf ("(%d) :\n",lunghezzaVettoreRicette);


	for (i = 0; i <lunghezzaVettoreRicette ; i++) {

			if (ricette[i].Visibilita==true ){
				printf("%d - %30s \t| Kcal per porzione: %5.2f \t| Id: %3d  |  Freq: %5d  |  Visib: %s\n", i,
								ricette[i].Nome, ricette[i].Kcal_Porzione, ricette[i].ID_Ricetta, ricette[i].Frequenza,(ricette[i].Visibilita)?"true":"false");
			}
	}



	return 1;
}









int scelta_visualizzazione_ricette(ricetta ricette[],int lunghezzaVettoreRicette){
	int numScelta=0;

		do {
			numScelta = fai_scelta(MENU_ORDINAMENTO_RICETTE);

			switch (numScelta) {

			case 1:
				//ordinamento Normale
				visualizza_ricette(ricette,lunghezzaVettoreRicette);
				break;

			case MODALITA_ORDINAMENTO_KCAL_PORZIONE:
				//ordina per kcal
				visualizza_ricette_ordinate(ricette,lunghezzaVettoreRicette,numScelta);
				break;

			case MODALITA_ORDINAMENTO_FREQUENZA:
				//ordina per frequenza
				visualizza_ricette_ordinate(ricette,lunghezzaVettoreRicette,numScelta);
				break;

			case 0:
				//case di uscita dal sottomenu
				break;

			default:
				printf("Scelta errata! Riprova!\n");

			}
		}while(numScelta != 0);

		return 0;
}








/* FUNZIONE CHE APPLICA LE MODIFICHE EFFETTUATE		*
 * PRECEDENTEMENTE ALLA RICETTA ALL'INTERNO DEL 	*
 * FILE NELLA CORRETTA POSIZIONE					*
 * 													*
 * LA FUNZIONE RITORNA 1 SE LA PROCEDURA È ANDATA 	*
 * A BUON FINE ALTRIMENTI 0*/
int modifica_ricetta_su_file(ricetta rice){
	FILE *file;

	if ((file = fopen("src/Ricette.sf", "rb+")) == NULL) return 0;
	else {
		fseek(file,rice.ID_Ricetta*sizeof(ricetta),SEEK_SET);
		fwrite(&rice,sizeof(ricetta),1,file);

		fclose(file);
		return 1;
	}

}






/* FUNZIONE CHE SERVE PER VERIFICARE SE ESISTE LA RICETTA PASSATA	*
 * COME PARAMETRO Parametri_Ricerca NEL VETTORE DI RICETTE			*
 * 																	*
 * SE IL PARAMETRO Visibilita E' true CONTROLLA TRA TUTTE LE 		*
 * RICETTE CON VISIBILITA true 			   							*
 * ALTRIMENTI CONTROLLA ANCHE TRA QUALLI 'CANCELLATI'				*
 * 																	*
 * LA FUNZIONE ELIMINA TUTTI GLI SPAZI FINALI E INIZIALI DELLE DUE	*
 * STRINGHE E INOLTRE NE CREA UNA COPIA IN MINUSCOLO				*
 * 																	*
 * LA FUNZIONE RITORNA -1 SE NON VIENE TROVATA NESSUNA 				*
 * CORRISPONDENZA, ALTRIMENTI RITORNA LA POSIZIONE DELLA PRIMA 		*
 * OCCORRENZA														*/
int get_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,char parametriRicerca[],boolean visibilita){

	int i;
	char stringTempParametri[LUNGHEZZA_STRINGA];
	remove_first_last_space(parametriRicerca, stringTempParametri,
			LUNGHEZZA_STRINGA);
	to_lower_string(stringTempParametri, stringTempParametri);

	for (i = 0; i < lunghezzaVettoreRicette; i++) {
		char StringTempVettore[LUNGHEZZA_STRINGA];
		remove_first_last_space(ricette[i].Nome, StringTempVettore,
				LUNGHEZZA_STRINGA);
		to_lower_string(StringTempVettore, StringTempVettore);

		//se le due stringhe sono uguali
		if (strcmp(stringTempParametri, StringTempVettore) == 0)
		if(ricette[i].Visibilita || ricette[i].Visibilita==visibilita)	return i;
	}

	return -1;
}






int cancella_ricetta(ricetta ricette[],int lunghezzaVettoreRicette){

	char scelta[LUNGHEZZA_STRINGA];
	int indiceRicetta;

	printf("\n\n\n%s\n",STRINGASTERISCHI);
	printf("         CANCELLAZIONE RICETTA\n");
	printf("%s\n",STRINGASTERISCHI);

	printf("Inserisci il nome della ricetta che si vuole cancellare: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	if((indiceRicetta=get_ricetta(ricette,lunghezzaVettoreRicette,scelta,true)) == -1) printf("\nLa ricetta \"%s\" non esistente!\n",scelta);
	else{

		char StringaElab[LUNGHEZZA_STRINGA];
		strcpy(StringaElab,"\nSei sicuro di voler cancellare la ricetta \"");
		strcat(StringaElab,scelta);
		strcat(StringaElab,"\" ? ");

		boolean flag;

		if((flag=fai_scelta_booleana(StringaElab)) == false) printf("\nLa cancellazione della ricetta e' stata annullata!\n");
		else{

			//effettuo la cancellazione quindi setto il flag visibilita a false all'interno del vettore
			ricette[indiceRicetta].Visibilita=false;

			//applico le modifiche della ricetta su file
			modifica_ricetta_su_file(ricette[indiceRicetta]);

			printf("\nCancellazione della ricetta effettuata con successo!\n");
		}
	}

	return 1;
}







/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE LE KCAL PER 	*
 * PORZIONE DELLA RICETTA CON INDICE indice PASSATO COME 		*
 * PARAMETRO													*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT IL VALORE E LO AGGIORNA SIA SUL 	*
 * VETTORE DI RICETTE CHE SU FILE 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int modifica_kcalporzione_ricetta(ricetta ricette[],int indiceRicetta){
	double kcal=0.0;

	kcal=fai_scelta_double("\nInserisci le nuove kcal per porzione della Ricetta:\n");

	//effettuo la modifica nel vettore
	ricette[indiceRicetta].Kcal_Porzione=kcal;

	//effettuo la modifica su file
	if(modifica_ricetta_su_file(ricette[indiceRicetta]) == 1) printf("\nModifica delle Kcal per porzione della Ricetta avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica delle Kcal per porzione della Ricetta su file!\n");
	}

	return 1;
}








/* FUNZIONE SPECIFICA CHE SI OCCUPA DI MODIFICARE IL NOME		*
 * DELLA RICETTA CON INDICE indice PASSATO COME PARAMETRO		*
 * 																*
 * LA FUNZIONE CHIDE IN INPUT IL VALORE E LO AGGIORNA SIA SUL 	*
 * VETTORE DI RICETTE CHE SU FILE E INOLTRE VIENE CONTROLLATO	*
 * SE IL NOME INSERITO DALL'UTENTE È GIA ESISTENTE E QUINDI		*
 * UTILIZZABILE O NO			 								*
 * 																*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE, 0 ALTRIMENTI	*/
int modifica_nome_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,int indiceRicetta){

	char scelta[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		printf("\nInserisci il nuovo nome della Ricetta:\n");
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);


		if(get_ricetta(ricette,lunghezzaVettoreRicette,scelta,false) > -1){
			 printf("\nQuesto nome gia esiste!\n");
		}else flag=true;

	}while(strlen(scelta) == 0 || flag==false);

	//Effettuo la modifica sul vettore presente in memoria
	strcpy(ricette[indiceRicetta].Nome,scelta);


	//Effettuo la modifica su file
	if(modifica_ricetta_su_file(ricette[indiceRicetta]) == 1) printf("\nModifica del nome della Ricetta avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica del nome della Ricetta su file!\n");
	}

	return 1;

}







int visualizza_alimenti_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){
	printf("\n\nAlimenti che formano \"%s\" \n\n",ricette[indiceRicetta].Nome);
	printf("%s",STRINGASTERISCHI);

	printf("\n%15s   |%15s\n","Quantita","Alimento");
	int quantita=-1;
	int cont=0;
	int i;
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if((quantita=ricette[indiceRicetta].Alimenti_Quantita[1][i])!=0){
			cont++;
			printf("%15d   |%15s\n",quantita,alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]].Nome);
		}
	}
	return 1;
}







int get_alimento_ricetta(ricetta ricette[],int indiceRicetta,int idAlimento){

	int i;

	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if(ricette[indiceRicetta].Alimenti_Quantita[1][i]!=0 && ricette[indiceRicetta].Alimenti_Quantita[0][i]==idAlimento){
			return i;
		}
	}

	return -1;

}






int salva_alimento_in_ricetta(ricetta *rice,int indiceAlimento,int quantita){

	int i;
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if((*rice).Alimenti_Quantita[1][i]==0){
			(*rice).Alimenti_Quantita[1][i]=quantita;
			(*rice).Alimenti_Quantita[0][i]=indiceAlimento;
			return 1;
		}
	}
	return 0;
}







int inserimento_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento da aggiungere: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int IndiceAlimento;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((IndiceAlimento=get_alimento(alimenti,lunghezzaVettoreAlimenti,scelta,false)) > -1){

		//se esiste devo controllare se è stato gia inserito come alimento della ricetta
		if(get_alimento_ricetta(ricette,indiceRicetta,IndiceAlimento) > -1) printf("\nL'alimento che stai cercando di inserire nella ricetta e' gia presente!\n");
		else{

			//chiedo la quantita di alimento che necessita la ricetta
			int quantita;
			do{
				quantita=fai_scelta("\nInserisci la quantita di alimento di cui necessita la ricetta: ");
				if(quantita==0) printf("\nDevi inserire obbligatoriamente un valore maggiore di zero! Riprova!\n");
			}while(quantita==0);

			if(!salva_alimento_in_ricetta(&ricette[indiceRicetta],IndiceAlimento,quantita)) printf("\nNon puoi piu aggiungere alimenti alla ricetta perche hai raggiunto il numero massimo consentito!\n");
			else{
				if(modifica_ricetta_su_file(ricette[indiceRicetta])) printf("\nAggiunta dell'alimento alla ricetta \"%s\" avvenuta con successo!\n",ricette[indiceRicetta].Nome);
				else{
					printf("\nErrore nella scrittura della modifica dell'alimento della ricetta su file!\n");
					return 0;
				}
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste! Prima di utilizzarlo inserirlo tra gli alimenti!\n",scelta);
		return 0;
	}

	return 1;

}







int cancellazione_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento da cancellare: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int IndiceAlimento;
	int IndiceAlimentoInRIcetta;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((IndiceAlimento=get_alimento(alimenti,lunghezzaVettoreAlimenti,scelta,false)) > -1){

		//controllo se l'alimento inserito fa parte della ricetta
		if((IndiceAlimentoInRIcetta=get_alimento_ricetta(ricette,indiceRicetta,IndiceAlimento)) == -1){
			printf("\nL'alimento che stai cercando di cancellare non fa parte della ricetta \"%s\"\n",ricette[indiceRicetta].Nome);
			return 0;
		}
		else{
			int SceltaBool=fai_scelta_booleana("\nSei sicuro di volere cancellare l'alimento dalla ricetta? ");
			if(!SceltaBool){
				printf("\nCancellazione dell'alimento dalla ricetta annullata!\n");
				return 0;
			}else{

				//imposto i parametri prima presenti a zero
				ricette[indiceRicetta].Alimenti_Quantita[1][IndiceAlimentoInRIcetta]=0;
				ricette[indiceRicetta].Alimenti_Quantita[0][IndiceAlimentoInRIcetta]=-1;

				if(modifica_ricetta_su_file(ricette[indiceRicetta])){
					printf("\nCancellazione dell'alimento \"%s\" dalla ricetta \"%s\" avvenuta con successo!\n",alimenti[IndiceAlimento].Nome,ricette[indiceRicetta].Nome);
					return 1;
				}else{
					printf("\nErrore nella cancellazione dell'alimento \"%s\" dalla ricetta \"%s\" !\n",alimenti[IndiceAlimento].Nome,ricette[indiceRicetta].Nome);
					return 0;
				}
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste!\n",scelta);
		return 0;
	}


}







int modifica_quantita_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento di cui modificare la quantita: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int indiceAlimento;
	int indiceAlimentoInRicetta;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((indiceAlimento=get_alimento(alimenti,lunghezzaVettoreAlimenti,scelta,false)) > -1){

		//controllo se l'alimento inserito fa parte della ricetta
		if((indiceAlimentoInRicetta=get_alimento_ricetta(ricette,indiceRicetta,indiceAlimento)) == -1){
			printf("\nL'alimento che stai cercando di cancellare non fa parte della ricetta \"%s\"\n",ricette[indiceRicetta].Nome);
			return 0;
		}else{

			int quantita;
			do{
				quantita=fai_scelta("\nInserisci la nuova quantita: ");
				if(quantita==0) printf("\nQuantita non valida! Riprova!\n");
			}while(quantita==0);

			//applico le modifiche sul vettore di ricette
			ricette[indiceRicetta].Alimenti_Quantita[1][indiceAlimentoInRicetta]=quantita;

			//applico le modifiche anche sul file di ricette
			if(modifica_ricetta_su_file(ricette[indiceRicetta])){
				printf("\nModifica della quantita di \"%s\" nella ricetta \"%s\" avvenuta con successo!\n",alimenti[indiceAlimento].Nome,ricette[indiceRicetta].Nome);
				return 1;
			}else{
				printf("\nErrore nella modifica della quantita di \"%s\" della ricetta \"%s\" su file!\n",alimenti[indiceAlimento].Nome,ricette[indiceRicetta].Nome);
				return 0;
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste!\n",scelta);
		return 0;
	}

}







int modifica_alimenti_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	visualizza_alimenti_ricetta(ricette,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);

	int numScelta;

	do{
		numScelta=fai_scelta(MENU_MODIFICA_ALIMENTI_RICETTA);
		switch(numScelta){
			case 1:
				//Inserimento alimento nella ricetta
				inserimento_alimento_ricetta(ricette,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);
				break;

			case 2:
				//Calcellazione alimento nella ricetta
				cancellazione_alimento_ricetta(ricette,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);
				break;

			case 3:
				//Modifica quantita di un alimento della ricetta
				modifica_quantita_alimento_ricetta(ricette,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);
				break;

			case 0:
				break;

			default:printf("Scelta errata! Riprova!\n");
		}
	}while(numScelta!=0);



	return 1;
}









/* FUNZIONE CHE EFFETTUA LA MODIFICA DI UNA DETERMINATA		*
 * RICETTA CHIESTA IN INPUT NELLA STESSA FUNZIONE			*/
int modifica_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	printf("\n\n             Modifica Ricetta\n");
	printf("\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice;

	if ((indice=get_ricetta(ricette, lunghezzaVettoreRicette,scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nRicetta Trovata\n\n");



		//devo fare la modifica effettiva
		int NumScelta=1;
		do{
			NumScelta=fai_scelta(MENU_MODIFICA_RICETTE);

			switch(NumScelta){
				case 1:
					//modifica nome

					modifica_nome_ricetta(ricette,lunghezzaVettoreRicette,indice);

					break;
				case 2:
					//modifica kcal_Porzione

					modifica_kcalporzione_ricetta(ricette,indice);

					break;

				case 3:
					//Modifica la composizione di alimenti
					modifica_alimenti_ricetta(ricette,indice,alimenti,lunghezzaVettoreAlimenti);

					break;

				case 0:
					break;

				default:
					printf("Scelta errata! Riprova!\n");
			}

		} while (NumScelta != 0);


	} else
		printf("\n\nNon esiste nessuna ricetta che si chiama in quel modo!\n\n");

	return 1;
}







/* FUNZIONE CHE CALCOLA IL NUMERO DI POSSIBILI 	*
 * PORZIONI IN BASE ALLE QUANTITA DI ALIMENTI 	*
 * DISPONIBILI DI UNA RICETTA PASSATA COME 		*
 * PARAMETRO.									*
 * 												*
 * LA FUNZIONE RITORNA IL NUMERO DI PORZIONI	*
 * POSSIBILI SE CI SONO,ALTRIMENTI -1			*/
int get_numero_porzioni_possibili_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceRicetta){

	int i;
	int porzPoss[NUMERO_MAX_ALIMENTI];
	int min=-1;

	//for che scorre il vettore di alimenti della ricetta
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		alimento alim=alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]];
		if(get_quantita(alim) >= ricette[indiceRicetta].Alimenti_Quantita[1][i]){
			if(ricette[indiceRicetta].Alimenti_Quantita[1][i]!=0){
				porzPoss[i]= (int)(get_quantita(alim)/ricette[indiceRicetta].Alimenti_Quantita[1][i]);
				if(min==-1) min=porzPoss[i];
				if(min>porzPoss[i]) min=porzPoss[i];
			}
		}else return -1;
	}

	return min;
}











/* FUNZIONE CHE HA IL COMPITO DI SOTTRARRE LE QUANTITA	*
 * DEGLI ALIMENTI PER CONSUMARE UNA RICETTA PASSATA 	*
 * COME PARAMETRO										*
 * 														*
 * LA FUNZIONE ESEGUE LE MODIFICHE SIA SUL VETTORE DI 	*
 * ALIMENTI CHE SUL FILE								*/
int consuma_ricetta_su_alimenti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceRicetta,int porzioni){
	int i;
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if(ricette[indiceRicetta].Alimenti_Quantita[0][i] > -1){
			int quantita=ricette[indiceRicetta].Alimenti_Quantita[1][i];
			//incremento l'utilizzo dell'alimento
			alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]].Utilizzo+=(quantita*porzioni);

			decrementa_quantita_alimento(&alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]],(quantita*porzioni));


			//modifica_alimento_su_file(alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]]);
		}

	}
	return 1;

}






/* FUNZIONE CHE SI OCCUPA DI TUTTO QUELLO CHE RIGUARDA 	*
 * L'AGGIUNTA DELLE RICETTE ALL'INTERNO DEL VETTORE	    *
 * E ALL'INTERNO DEL FILE								*
 * 														*
 * LA FUNZIONE RICEVE COME PARAMETRI IL VETTORE DI 		*
 * RICETTE E DI ALIMENTI E LE LORO LUNGHEZZE E INOLTRE 	*
 * UN PUNTATORE 										*
 * AD INTERO PER LA MEMORIZZAZIONE DELL'INDIRIZZO 		*
 * DOVE RISIEDE IL NUONO VETTORE DI RICETTE IN CASO DI	*
 * AGGIUNTA DI UNA RICETTA IN CODA AL VETTORE			*/
int inserimento_ricetta(alimento alimenti[],int lunghezzaVettoreAlimenti,ricetta ricette[],int lunghezzaVettoreRicette,int *nuovoIndirizzoRicette){

	printf("\n\n            Inserimento Ricette\n%s\n\n",STRINGASTERISCHI);
	char scelta[LUNGHEZZA_STRINGA];
	int indiceRicetta=-1;


	printf("\nInserisci il nome della ricetta che vuoi aggiungere: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	if((indiceRicetta=get_ricetta(ricette,lunghezzaVettoreRicette,scelta,true)) == -1){
		//caso in cui la ricetta non è presente tra le ricette visibili

		//cerco la ricetta tra le ricette cancellate con visibilita false
		if((indiceRicetta=get_ricetta(ricette,lunghezzaVettoreRicette,scelta,false)) == -1){
			//caso in cui non esiste propio la ricetta,neanche tra le ricette gia cancellate




			//se la ricetta non è presente devo andare ad aggiungerlo al vettore
			//prova di allungamento del vettore
			lunghezzaVettoreRicette++;
			int j;
			ricetta *ricette2= (ricetta*) calloc(lunghezzaVettoreRicette,sizeof(ricetta));
			for(j=0;j<lunghezzaVettoreRicette-1;j++) ricette2[j]=ricette[j];
			//Libero la memoria del vecchio vettore
			free(ricette);
			//ricette[Lunghezza_Vettore_Ricette-1]=alim;
			(*nuovoIndirizzoRicette)=(int)ricette2;




			//chiedo tutte le caratteristiche della ricetta in input
			indiceRicetta=lunghezzaVettoreRicette-1;

			strcpy(ricette2[indiceRicetta].Nome,scelta);
			ricette2[indiceRicetta].Frequenza=0;
			ricette2[indiceRicetta].Visibilita=true;
			ricette2[indiceRicetta].ID_Ricetta=lunghezzaVettoreRicette-1;
			ricette2[indiceRicetta].Kcal_Porzione=fai_scelta_double("\nInserisci le Kcal per porzione della ricetta:");

			//inizializzo il vettore di alimenti della ricetta
			for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
				ricette2[indiceRicetta].Alimenti_Quantita[0][j]=-1;
				ricette2[indiceRicetta].Alimenti_Quantita[1][j]=0;
			}



			//aggiunta degli alimenti alla ricetta
			printf("\nInserimento alimenti della ricetta\n%s\n",STRINGASTERISCHI);
			boolean flag;
			int flag1=0;
			do{
				flag=false;

				if(flag1==0){
					flag1 = inserimento_alimento_ricetta(ricette2,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);
				}else inserimento_alimento_ricetta(ricette2,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);

				visualizza_alimenti_ricetta(ricette2,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);

				if(fai_scelta_booleana("\n\nVuoi aggiungere un altro alimento alla ricetta? ") == true) flag=true;
			}while(flag==true || flag1 == 0);


			printf("\nRicetta inserita con successo!\n");


		}else{

			ricette[indiceRicetta].Visibilita=true;
			modifica_ricetta_su_file(ricette[indiceRicetta]);

			//caso in cui la ricetta esiste gia nel tra le ricette eliminate
			printf("\nLa ricetta che stai cercando di inserire era nel nostro sistema in precedenza\n");
			printf("e non è stata rimossa del tutto! Da ora in poi la potrai vedere e modificare nel caso\n");
			printf("alcune particolarita non vadano bene! Per farlo vai in Opzioni Ricette > Modifica Ricetta\n\n");
		}

	}else{
		//caso in cui il nome della ricetta inserita dell'utente esiste gia quindi la ricetta esiste gia
		printf("\nLa ricetta che stai cercando di inserire esiste gia!\n");
	}

	return lunghezzaVettoreRicette;
}









int scelta_opzioni_ricette(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoRicette){

	int NumScelta;

	(*nuovoIndirizzoRicette)=(int)ricette;

	do {
		NumScelta = fai_scelta(MENU_RICETTE);

		switch (NumScelta) {
		case 1:

			//viualizza lista ricette
			scelta_visualizzazione_ricette(ricette, lunghezzaVettoreRicette);
			break;

		case 2:

			//aggiungi ricetta
			lunghezzaVettoreRicette=inserimento_ricetta(alimenti,lunghezzaVettoreAlimenti,ricette,lunghezzaVettoreRicette,nuovoIndirizzoRicette);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di una nuovo ricetta
			ricette=(ricetta*)(*nuovoIndirizzoRicette);

			break;
		case 3:

			//modifica ricetta
			modifica_ricetta(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;
		case 4:

			//cancella ricetta
			cancella_ricetta(ricette,lunghezzaVettoreRicette);

			break;

		case 5:

			//Gestione dei preferiti
			scelta_opzioni_preferiti(ricette, lunghezzaVettoreRicette);

			break;

		case 0:
			//case di uscita dal sottomenu
			break;
		default:
			printf("Scelta errata! Riprova!\n");
		}

	} while (NumScelta != 0);

	return lunghezzaVettoreRicette;
}


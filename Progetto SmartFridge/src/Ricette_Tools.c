/*
 * Ricette_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <String.h>
#include "Alimenti_Tools.h"


int Merging_Kcal(int inizio, int medio, int fine, ricetta a[], double b[]) {
   int l1, l2, i;

   for(l1 = inizio, l2 = medio + 1, i = inizio; l1 <= medio && l2 <= fine; i++) {
      if(a[l1].Kcal_Porzione <= a[l2].Kcal_Porzione)
         b[i] = a[l1++].Kcal_Porzione;
      else
         b[i] = a[l2++].Kcal_Porzione;
   }

   while(l1 <= medio)
      b[i++] = a[l1++].Kcal_Porzione;

   while(l2 <= fine)
      b[i++] = a[l2++].Kcal_Porzione;

   for(i = inizio; i <= fine; i++){
	    a[i].Kcal_Porzione = b[i];
   printf ("a: %.2f b: %.2f  |",a[i].Kcal_Porzione , b[i]);
   }

   printf("\n");

   return 1;
}



int Sort_Merge_Kcal(int inizio, int fine, ricetta a[], double b[]) {
   int medio;

   if(inizio < fine) {
      medio = (inizio + fine) / 2;
      Sort_Merge_Kcal(inizio, medio,a,b);
      Sort_Merge_Kcal(medio+1, fine,a,b);

      Merging_Kcal(inizio, medio, fine, a, b);
      return 0;
   } else {
      return 1;
   }
}




int Visualizza_Ricette(ricetta ricette[], int Lunghezza_Vettore) {

	int i;


	double vett_appoggio[Lunghezza_Vettore];

	printf("Ricette presenti:\n");
	for (i = 0; i < Lunghezza_Vettore; i++) {



	printf("Ricette presenti");
	printf ("%d :\n",Lunghezza_Vettore);

	Sort_Merge_Kcal(0,Lunghezza_Vettore-1,ricette,vett_appoggio);

	for (i = 0; i <Lunghezza_Vettore -1 ; i++) {


		if (ricette[i].Visibilita==true || ricette[i].Visibilita==false){
			printf("%d - %s \t| Kcal per porzione: %.2f \t| Id: %d  |  Freq: %d  |  Visib: %s\n", i,
							ricette[i].Nome, ricette[i].Kcal_Porzione, ricette[i].ID_Ricetta, ricette[i].Frequenza,(ricette[i].Visibilita)?"true":"false");
		}


	}
	return 1;
}





int Scelta_Visualizzazione(ricetta ricette[],int lunghezza_vettore_ricette){


	int NumScelta;

		do {
			NumScelta = FaiScelta(MENU_VISUALIZZA_ALIMENTI);

			switch (NumScelta) {

			case 1:
				//ordina per kcal
				Visualizza_Ricette(ricette,lunghezza_vettore_ricette);
				break;

			case 2:
				//ordina per frequenza
				break;

			default:
				printf("Scelta errata! Riprova!\n");

			}
		}while(NumScelta != 0);

		return 0;


}









/* FUNZIONE CHE APPLICA LE MODIFICHE EFFETTUATE		*
 * PRECEDENTEMENTE ALLA RICETTA ALL'INTERNO DEL 	*
 * FILE NELLA CORRETTA POSIZIONE					*
 * 													*
 * LA FUNZIONE RITORNA 1 SE LA PROCEDURA È ANDATA 	*
 * A BUON FINE ALTRIMENTI 0*/
int Modifica_Ricetta_Su_File(ricetta rice){
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
int getRicetta(ricetta ricette[],int Lunghezza_vettore_ricette,char Parametri_Ricerca[],boolean visibilita){

	int i;
	char StringTempParametri[LUNGHEZZA_STRINGA];
	removeFirstLastSpace(Parametri_Ricerca, StringTempParametri,
			LUNGHEZZA_STRINGA);
	toLowerString(StringTempParametri, StringTempParametri);

	for (i = 0; i < Lunghezza_vettore_ricette; i++) {
		char StringTempVettore[LUNGHEZZA_STRINGA];
		removeFirstLastSpace(ricette[i].Nome, StringTempVettore,
				LUNGHEZZA_STRINGA);
		toLowerString(StringTempVettore, StringTempVettore);

		//se le due stringhe sono uguali
		if (strcmp(StringTempParametri, StringTempVettore) == 0)
		if(ricette[i].Visibilita || ricette[i].Visibilita==visibilita)	return i;
	}

	return -1;
}






int Cancella_Ricetta(ricetta ricette[],int Lunghezza_vettore_ricette){

	char scelta[LUNGHEZZA_STRINGA];
	int IndiceRicetta;

	printf("\n\n\n%s\n",STRINGASTERISCHI);
	printf("         CANCELLAZIONE RICETTA\n");
	printf("%s\n",STRINGASTERISCHI);

	printf("Inserisci il nome della ricetta che si vuole cancellare: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	if((IndiceRicetta=getRicetta(ricette,Lunghezza_vettore_ricette,scelta,true)) == -1) printf("\nLa ricetta \"%s\" non esistente!\n",scelta);
	else{

		char StringaElab[LUNGHEZZA_STRINGA];
		strcpy(StringaElab,"\nSei sicuro di voler cancellare la ricetta \"");
		strcat(StringaElab,scelta);
		strcat(StringaElab,"\" ? ");

		boolean flag;

		if((flag=FaiSceltaBooleana(StringaElab)) == false) printf("\nLa cancellazione della ricetta e' stata annullata!\n");
		else{

			//effettuo la cancellazione quindi setto il flag visibilita a false all'interno del vettore
			ricette[IndiceRicetta].Visibilita=false;

			//applico le modifiche della ricetta su file
			Modifica_Ricetta_Su_File(ricette[IndiceRicetta]);

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
int Modifica_kcalPorzione_Ricetta(ricetta ricette[],int indice){
	double Kcal=0.0;

	Kcal=FaiSceltaDouble("\nInserisci le nuove kcal per porzione della Ricetta:\n");

	//effettuo la modifica nel vettore
	ricette[indice].Kcal_Porzione=Kcal;

	//effettuo la modifica su file
	if(Modifica_Ricetta_Su_File(ricette[indice]) == 1) printf("\nModifica delle Kcal per porzione della Ricetta avvenuta con successo!\n");
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
int Modifica_Nome_Ricetta(ricetta ricette[],int Lunghezza_vettore_ricette,int indice){

	char scelta[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		printf("\nInserisci il nuovo nome della Ricetta:\n");
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);


		if(getRicetta(ricette,Lunghezza_vettore_ricette,scelta,false) > -1){
			 printf("\nQuesto nome gia esiste!\n");
		}else flag=true;

	}while(strlen(scelta) == 0 || flag==false);

	//Effettuo la modifica sul vettore presente in memoria
	strcpy(ricette[indice].Nome,scelta);


	//Effettuo la modifica su file
	if(Modifica_Ricetta_Su_File(ricette[indice]) == 1) printf("\nModifica del nome della Ricetta avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica del nome della Ricetta su file!\n");
	}

	return 1;

}







int Visualizza_Alimenti_Ricetta(ricetta ricette[],int indice,alimento alimenti[],int Lunghezza_vettore_alimenti){
	printf("\n\nAlimenti che formano \"%s\" \n\n",ricette[indice].Nome);
	printf("%s",STRINGASTERISCHI);

	printf("\n%15s   |%15s\n","Quantita","Alimento");
	int quantita=-1;
	int cont=0;
	while((quantita=ricette[indice].Alimenti_Quantita[1][cont])!=0 && cont!=NUMERO_MAX_ALIMENTI){
		printf("%15d   |%15s\n",quantita,alimenti[ricette[indice].Alimenti_Quantita[0][cont]].Nome);
		cont++;
	}
	return 1;
}







int getAlimentoRicetta(ricetta ricette[],int indice,int Id_Alimento){

	int i;

	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if(ricette[indice].Alimenti_Quantita[1][i]!=0 && ricette[indice].Alimenti_Quantita[0][i]==Id_Alimento){
			return i;
		}
	}

	return -1;

}






int Salva_Alimento_In_Ricetta(ricetta *rice,int IndiceAlimento,int Quantita){

	int i;
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if((*rice).Alimenti_Quantita[1][i]==0){
			(*rice).Alimenti_Quantita[1][i]=Quantita;
			(*rice).Alimenti_Quantita[0][i]=IndiceAlimento;
			return 1;
		}
	}
	return 0;
}







int Inserimento_Alimento_Ricetta(ricetta ricette[],int indice,alimento alimenti[],int Lunghezza_vettore_alimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento da aggiungere: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int IndiceAlimento;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((IndiceAlimento=getAlimento(alimenti,Lunghezza_vettore_alimenti,scelta,false)) > -1){

		//se esiste devo controllare se è stato gia inserito come alimento della ricetta
		if(getAlimentoRicetta(ricette,indice,IndiceAlimento) > -1) printf("\nL'alimento che stai cercando di inserire nella ricetta e' gia presente!\n");
		else{

			//chiedo la quantita di alimento che necessita la ricetta
			int quantita;
			do{
				quantita=FaiScelta("\nInserisci la quantita di alimento di cui necessita la ricetta: ");
				if(quantita==0) printf("\nDevi inserire obbligatoriamente un valore maggiore di zero! Riprova!\n");
			}while(quantita==0);

			if(!Salva_Alimento_In_Ricetta(&ricette[indice],IndiceAlimento,quantita)) printf("\nNon puoi piu aggiungere alimenti alla ricetta perche hai raggiunto il numero massimo consentito!\n");
			else{
				if(Modifica_Ricetta_Su_File(ricette[indice])) printf("\nAggiunta dell'alimento alla ricetta \"%s\" avvenuta con successo!\n",ricette[indice].Nome);
				else{
					printf("\nErrore nella scrittura della modifica dell'alimento della ricetta su file!\n");
					return 0;
				}
			}
		}
	}else printf("\nL'alimento \"%s\" non esiste! Prima di utilizzarlo inserirlo tra gli alimenti!\n",alimenti[IndiceAlimento].Nome);

	return 1;

}







int Cancellazione_Alimento_Ricetta(ricetta ricette[],int indice,alimento alimenti[],int Lunghezza_vettore_alimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento da cancellare: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int IndiceAlimento;
	int IndiceAlimentoInRIcetta;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((IndiceAlimento=getAlimento(alimenti,Lunghezza_vettore_alimenti,scelta,false)) > -1){

		//controllo se l'alimento inserito fa parte della ricetta
		if((IndiceAlimentoInRIcetta=getAlimentoRicetta(ricette,indice,IndiceAlimento)) == -1){
			printf("\nL'alimento che stai cercando di cancellare non fa parte della ricetta \"%s\"\n",ricette[indice].Nome);
			return 0;
		}
		else{
			int SceltaBool=FaiSceltaBooleana("\nSei sicuro di volere cancellare l'alimento dalla ricetta? ");
			if(!SceltaBool){
				printf("\nCancellazione dell'alimento dalla ricetta annullata!\n");
				return 0;
			}else{

				//imposto i parametri prima presenti a zero
				ricette[indice].Alimenti_Quantita[1][IndiceAlimentoInRIcetta]=0;
				ricette[indice].Alimenti_Quantita[0][IndiceAlimentoInRIcetta]=-1;

				if(Modifica_Ricetta_Su_File(ricette[indice])){
					printf("\nCancellazione dell'alimento \"%s\" dalla ricetta \"%s\" avvenuta con successo!\n",alimenti[IndiceAlimento].Nome,ricette[indice].Nome);
					return 1;
				}else{
					printf("\nErrore nella cancellazione dell'alimento \"%s\" dalla ricetta \"%s\" !\n",alimenti[IndiceAlimento].Nome,ricette[indice].Nome);
					return 0;
				}
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste!\n",scelta);
		return 0;
	}


}







int Modifica_Quantita_Alimento_Ricetta(ricetta ricette[],int indice,alimento alimenti[],int Lunghezza_vettore_alimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento di cui modificare la quantita: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int IndiceAlimento;
	int IndiceAlimentoInRIcetta;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((IndiceAlimento=getAlimento(alimenti,Lunghezza_vettore_alimenti,scelta,false)) > -1){

		//controllo se l'alimento inserito fa parte della ricetta
		if((IndiceAlimentoInRIcetta=getAlimentoRicetta(ricette,indice,IndiceAlimento)) == -1){
			printf("\nL'alimento che stai cercando di cancellare non fa parte della ricetta \"%s\"\n",ricette[indice].Nome);
			return 0;
		}else{

			int quantita;
			do{
				quantita=FaiScelta("\nInserisci la nuova quantita: ");
				if(quantita==0) printf("\nQuantita non valida! Riprova!\n");
			}while(quantita==0);

			//applico le modifiche sul vettore di ricette
			ricette[indice].Alimenti_Quantita[1][IndiceAlimentoInRIcetta]=quantita;

			//applico le modifiche anche sul file di ricette
			if(Modifica_Ricetta_Su_File(ricette[indice])){
				printf("\nModifica della quantita di \"%s\" nella ricetta \"%s\" avvenuta con successo!\n",alimenti[IndiceAlimento].Nome,ricette[indice].Nome);
				return 1;
			}else{
				printf("\nErrore nella modifica della quantita di \"%s\" della ricetta \"%s\" su file!\n",alimenti[IndiceAlimento].Nome,ricette[indice].Nome);
				return 0;
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste!\n",scelta);
		return 0;
	}

}







int Modifica_Alimenti_Ricetta(ricetta ricette[],int indice,alimento alimenti[],int Lunghezza_vettore_alimenti){

	Visualizza_Alimenti_Ricetta(ricette,indice,alimenti,Lunghezza_vettore_alimenti);

	int NumScelta;

	do{
		NumScelta=FaiScelta(MenuModificaAlimentiRicetta);
		switch(NumScelta){
			case 1:
				//Inserimento alimento nella ricetta
				Inserimento_Alimento_Ricetta(ricette,indice,alimenti,Lunghezza_vettore_alimenti);
				break;

			case 2:
				//Calcellazione alimento nella ricetta
				Cancellazione_Alimento_Ricetta(ricette,indice,alimenti,Lunghezza_vettore_alimenti);
				break;

			case 3:
				//Modifica quantita di un alimento della ricetta
				Modifica_Quantita_Alimento_Ricetta(ricette,indice,alimenti,Lunghezza_vettore_alimenti);
				break;

			case 0:
				break;

			default:printf("Scelta errata! Riprova!\n");
		}
	}while(NumScelta!=0);



	return 1;
}









/* FUNZIONE CHE EFFETTUA LA MODIFICA DI UNA DETERMINATA		*
 * RICETTA CHIESTA IN INPUT NELLA STESSA FUNZIONE			*/
int Modifica_Ricetta(ricetta ricette[],int Lunghezza_vettore_ricette,alimento alimenti[],int Lunghezza_vettore_alimenti){

	printf("\n\n             Modifica Ricetta\n");
	printf("\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice;

	if ((indice=getRicetta(ricette, Lunghezza_vettore_ricette,scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nRicetta Trovata\n\n");



		//devo fare la modifica effettiva
		int NumScelta=1;
		do{
			NumScelta=FaiScelta(MenuModificaRicette);

			switch(NumScelta){
				case 1:
					//modifica nome

					Modifica_Nome_Ricetta(ricette,Lunghezza_vettore_ricette,indice);

					break;
				case 2:
					//modifica kcal_Porzione

					Modifica_kcalPorzione_Ricetta(ricette,indice);

					break;

				case 3:
					//Modifica la composizione di alimenti
					Modifica_Alimenti_Ricetta(ricette,indice,alimenti,Lunghezza_vettore_alimenti);

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











int Scelta_Opzioni_Ricette(ricetta ricette[],int lunghezza_vettore_ricette,alimento alimenti[],int Lunghezza_vettore_alimenti){

	int NumScelta;

	do {
		NumScelta = FaiScelta(MenuRicette);

		switch (NumScelta) {
		case 1:


			//viualizza lista ricette

				//viualizza lista ricette
				Visualizza_Ricette(ricette,lunghezza_vettore_ricette);


			Scelta_Visualizzazione(ricette, lunghezza_vettore_ricette);
			break;
		case 2:

			//aggiungi ricetta

			break;
		case 3:


			//modifica ricetta

				//modifica ricetta
				Modifica_Ricetta(ricette,lunghezza_vettore_ricette,alimenti,Lunghezza_vettore_alimenti);


			break;
		case 4:


			//cancella ricetta

				//cancella ricetta
				Cancella_Ricetta(ricette,lunghezza_vettore_ricette);


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

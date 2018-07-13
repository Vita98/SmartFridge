/**
 *  @file 	   Ricette_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Ricette_Tools.h
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#include "Tipi_Dato.h"
#include <String.h>
#include "Alimenti_Tools.h"
#include "Preferiti_Tools.h"
#include "Ordinamenti_Tools.h"






/**
 * Funzione utilizzata per visualizzare all'utente, sul terminale, le ricette in maniera ordinata
 * in base al parametro modalitaOrdinamento.
 *
 * @pre modalitaOrdinamento deve essere necessariamente una costante di ordinamento tra quelle
 * definite in Tipi_dato.h.
 *
 */
int visualizza_ricette_ordinate(ricetta ricette[], int lunghezzaVettoreRicette, int modalitaOrdinamento) {

	int i,cont=0;
	int indici[lunghezzaVettoreRicette];

	printf("Ricette presenti ");
	printf ("(%d) :\n",lunghezzaVettoreRicette);

	//richiamo la funzione di ordinamento delle ricette con la modalita desiderata
	sort_ricette(ricette, indici, lunghezzaVettoreRicette, modalitaOrdinamento);

	for (i = 0; i <lunghezzaVettoreRicette ; i++) {

		//faccio visualizzare tutte le ricette non cancellate
		if (ricette[indici[i]].Visibilita==true){
			printf("%d - %30s \t| Kcal per porzione: %5.2f \t| Id: %3d  |  Freq: %5d  |  Visib: %s\n", i,
							ricette[indici[i]].Nome, ricette[indici[i]].Kcal_Porzione, ricette[indici[i]].ID_Ricetta, ricette[indici[i]].Frequenza,(ricette[indici[i]].Visibilita)?"true":"false");
			cont++;
		}
	}

	if(cont == 0){
		printf("\nNon ci sono ricette!\n");
		return 0;
	}
	return 1;
}






/**
 * Funzione utilizzata per visualizzare all'utente, sul terminale, le ricette in ordine di lettura
 * dal file quindi senza uno specifico ordinamento.
 *
 */
int visualizza_ricette(ricetta ricette[], int lunghezzaVettoreRicette) {

	int i,cont=0;

	printf("Ricette presenti ");
	printf ("(%d) :\n",lunghezzaVettoreRicette);


	for (i = 0; i <lunghezzaVettoreRicette ; i++) {

		//faccio visualizzare tutte le ricette non cancellate
		if (ricette[i].Visibilita==true ){
			printf("%d - %30s \t| Kcal per porzione: %5.2f \t| Id: %3d  |  Freq: %5d  |  Visib: %s\n", i,
							ricette[i].Nome, ricette[i].Kcal_Porzione, ricette[i].ID_Ricetta, ricette[i].Frequenza,(ricette[i].Visibilita)?"true":"false");
			cont++;
		}
	}

	if(cont == 0){
		printf("\nNon ci sono ricette!\n");
		return 0;
	}

	return 1;
}









/**
 * Funzione che gestisce il menu relativo alle opzioni di visualizzazione
 * delle ricette cioe' permette all'utente di decidere in che modo
 * visualizzare ordinatamente le ricette o se visualizzarle senza
 * un ordine specifico.
 * In base alla scelta, la funzione richiama le specifiche funzioni.
 *
 */
int scelta_visualizzazione_ricette(ricetta ricette[],int lunghezzaVettoreRicette){
	int numScelta=0;

		do {
			//pulisco lo schermo
			system("cls");

			printf("\nVISUALIZZAZIONE DELLE RICETTE\n");

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

			if(numScelta != 0) {
				char c[LUNGHEZZA_STRINGA];
				printf("\nPremi per continuare....");
				fgets(c,LUNGHEZZA_STRINGA,stdin);
			}

		}while(numScelta != 0);

		return 1;
}








/**
 * Data la ricetta passata come parametro, la funzione la sovrascrive
 * alla sua vecchia versione all'interno del file Ricette.sf.
 * Viene utilizzato per far riflettere le modifiche dal vettore
 * al file.
 *
 * @pre il file Ricette.sf deve gia esistere.
 * @pre non deve essere stato modificato l'ID della ricetta
 * in quanto potrebbe andare a effettuare delle modifiche
 * inopportune all'interno del file.
 */
int modifica_ricetta_su_file(ricetta rice){
	FILE *file;

	if ((file = fopen("Ricette.sf", "rb+")) == NULL) return 0;
	else {

		//mi posiziono nella corretta posizione su file
		fseek(file,rice.ID_Ricetta*sizeof(ricetta),SEEK_SET);

		if(fwrite(&rice,sizeof(ricetta),1,file) > 0){
			fclose(file);
			return 1;
		}else return 0;
	}

}






/**
 * Data la stringa parametriRicerca come parametro, la funzione cerca se esiste
 * una ricetta chiamata in quella maniera all'interno del vettore di ricette.
 * Se il parametro visibilita e' TRUE allora la funzione cerchera la ricetta tra tutte
 * le ricette con attributo visibilita uguale a true altrimenti la ricerchera anche tra
 * le ricette 'cancellate'.
 * Il matching non tiene conto dei caratteri minuscoli e maiuscoli e degli
 * spazi iniziali e finali.
 *
 */
int get_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,char parametriRicerca[],boolean visibilita){

	int i;
	char stringTempParametri[LUNGHEZZA_STRINGA];

	//rimuovo gli spazi iniziali e finali alla stringa di ricerca
	remove_first_last_space(parametriRicerca, stringTempParametri,LUNGHEZZA_STRINGA);
	to_lower_string(stringTempParametri, stringTempParametri);

	for (i = 0; i < lunghezzaVettoreRicette; i++) {
		char StringTempVettore[LUNGHEZZA_STRINGA];

		//rimuovo gli spazi iniziali e finali al nome della ricetta
		remove_first_last_space(ricette[i].Nome, StringTempVettore,LUNGHEZZA_STRINGA);

		//la converto in caratteri minuscoli
		to_lower_string(StringTempVettore, StringTempVettore);

		//se le due stringhe sono uguali
		if (strcmp(stringTempParametri, StringTempVettore) == 0)
		if(ricette[i].Visibilita || ricette[i].Visibilita==visibilita)	return i;
	}
	return -1;
}





/**
 * Funzione che si occupa di tutto quello che riguarda la cancellazione di una ricetta
 * cioe' chiede in input la ricetta da cancellare, applica i controlli adeguati
 * e effettua la cancellazione sia sul vettore di ricette che sul file Ricette.sf.
 *
 */
int cancella_ricetta(ricetta ricette[],int lunghezzaVettoreRicette){

	char scelta[LUNGHEZZA_STRINGA];
	int indiceRicetta;

	//pulisco lo schermo
	system("cls");

	printf("\nCANCELLAZIONE RICETTA\n\n%s\n\n",STRINGASTERISCHI);

	printf("Inserisci il nome della ricetta che si vuole cancellare: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	//controllo se la ricetta inserita esiste
	if((indiceRicetta=get_ricetta(ricette,lunghezzaVettoreRicette,scelta,true)) == -1) printf("\nLa ricetta \"%s\" non esistente!\n",scelta);
	else{

		//creo una stringa da passare alla funzione fai_scelta_booleana()
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
			if(modifica_ricetta_su_file(ricette[indiceRicetta]) == 0){
				printf("\nErrore nella cancellazione della ricetta!\n");

				//annullo la cancellazione anche dal vettore
				ricette[indiceRicetta].Visibilita=true;

				return 0;
			}else printf("\nCancellazione della ricetta effettuata con successo!\n");
		}
	}

	char c[LUNGHEZZA_STRINGA];
	printf("\nPremi per continuare....");
	fgets(c,LUNGHEZZA_STRINGA,stdin);

	return 1;
}








/**
 * Funzione che si occupa di tutto quello che riguarda la modifica delle kcal
 * per porzione di una ricetta il cui ID viene passato come parametro.
 * La funzione chiede in input un nuovo valore e successivamente effettua la modifica
 * sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @pre indiceRicetta deve essere un indice di ricetta valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
int modifica_kcalporzione_ricetta(ricetta ricette[],int indiceRicetta){
	double kcal=0.0;
	double vecchieCalorie=ricette[indiceRicetta].Kcal_Porzione;

	kcal=fai_scelta_double("\nInserisci le nuove kcal per porzione della Ricetta:\n");

	//effettuo la modifica nel vettore
	ricette[indiceRicetta].Kcal_Porzione=kcal;

	//effettuo la modifica su file
	if(modifica_ricetta_su_file(ricette[indiceRicetta]) == 1) {
		printf("\nModifica delle Kcal per porzione della Ricetta avvenuta con successo!\n");
		return 1;
	}
	else{
		printf("\nErrore nella modifica delle Kcal per porzione della Ricetta su file!\n");
		ricette[indiceRicetta].Kcal_Porzione=vecchieCalorie;
		return 0;
	}
}








/**
 * Funzione che si occupa di tutto quello che riguarda la modifica del nome
 * di una ricetta il cui ID viene passato come parametro.
 * La funzione chiede in input un nuovo nome, controlla se e' un nome valido
 * e non ancora utilizzato e successivamente effettua la modifica sia sul vettore di ricette che
 * sul file.
 *
 * @pre indiceRicetta deve essere un indice di ricetta valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
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
		return 0;
	}

	return 1;

}






/**
 * Funzione che, data una ricetta come parametro, visualizza tutti gli alimenti
 * e le relative quantita che la ricetta necessita per essere preparata.
 *
 * @pre indiceRicetta deve essere un indice di ricetta valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
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

	//controllo se ho visualizzato almeno un alimento
	if(cont != 0) return 1;
	else return 0;
}






/**
 * Funzione che, data una ricetta e un alimento come parametro, controlla se
 * l'alimento serve per preparare la ricetta.
 *
 * @pre indiceRicetta deve essere un indice di ricetta valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 *
 * @pre indiceAlimento deve essere un indice di alimento valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
int get_alimento_ricetta(ricetta ricette[],int indiceRicetta,int indiceAlimento){

	int i;

	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if(ricette[indiceRicetta].Alimenti_Quantita[1][i]!=0 && ricette[indiceRicetta].Alimenti_Quantita[0][i]==indiceAlimento){
			return i;
		}
	}
	return -1;
}






/**
 * Funzione che, data una ricetta e un alimento con una quantita, aggiunge l'alimento
 * con la relativa quantita all'interno del vettore di alimenti che compongono
 * la ricetta.
 *
 * @pre indiceAlimento deve essere un indice di alimento valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 *
 * @pre quantita deve essere maggiore di 0.
 */
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






/**
 * Funzione che, data una ricetta come parametro, gestisce tutto quello che riguarda
 * l'aggiunta di un alimento che compone la ricetta.
 * La funzione chiede in input l'alimento da aggiungere alla ricetta, controlla se
 * e' gia usato e successivamente applica la modifica sia sul vettore di ricette che
 * sul file Ricette.sf.
 *
 * @pre indiceRicetta deve essere un indice di alimento valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
int inserimento_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento da aggiungere alla ricetta: ");
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
				if(quantita<=0) printf("\nDevi inserire obbligatoriamente un valore maggiore di zero! Riprova!\n");
			}while(quantita<=0);

			if(!salva_alimento_in_ricetta(&ricette[indiceRicetta],IndiceAlimento,quantita)) printf("\nNon puoi piu aggiungere alimenti alla ricetta perche hai raggiunto il numero massimo consentito!\n");
			else{
				if(modifica_ricetta_su_file(ricette[indiceRicetta])) printf("\nAggiunta dell'alimento alla ricetta \"%s\" avvenuta con successo!\n",ricette[indiceRicetta].Nome);
				else{
					printf("\nErrore nella scrittura della modifica dell'alimento della ricetta su file!\n");

					int indiceAl;
					//elimino l'aggiunta in quanto si e' verificato un errore nel salvataggio su file
					if((indiceAl = get_alimento_ricetta(ricette,indiceRicetta,IndiceAlimento)) > -1){
						ricette[indiceRicetta].Alimenti_Quantita[0][indiceAl]=0;
						ricette[indiceRicetta].Alimenti_Quantita[0][indiceAl]=-1;
					}

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






/**
 * Funzione che, data una ricetta come parametro, gestisce tutto quello che riguarda
 * la cancellazione di un alimento che compone la ricetta.
 * La funzione chiede in input l'alimento da cancellare alla ricetta, controlla se
 * fa parte della ricetta, effettua la cencellazione e successivamente applica la
 * modifica sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @pre indiceRicetta deve essere un indice di alimento valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
int cancellazione_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	char scelta[LUNGHEZZA_STRINGA];
	int vecchioIndiceAlimento=-1;
	int vecchiaQuantitaAlimento=0;

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

				vecchioIndiceAlimento=ricette[indiceRicetta].Alimenti_Quantita[1][IndiceAlimentoInRIcetta];
				vecchiaQuantitaAlimento=ricette[indiceRicetta].Alimenti_Quantita[0][IndiceAlimentoInRIcetta];

				//imposto i parametri prima presenti a zero
				ricette[indiceRicetta].Alimenti_Quantita[1][IndiceAlimentoInRIcetta]=0;
				ricette[indiceRicetta].Alimenti_Quantita[0][IndiceAlimentoInRIcetta]=-1;

				if(modifica_ricetta_su_file(ricette[indiceRicetta])){
					printf("\nCancellazione dell'alimento \"%s\" dalla ricetta \"%s\" avvenuta con successo!\n",alimenti[IndiceAlimento].Nome,ricette[indiceRicetta].Nome);
					return 1;
				}else{
					printf("\nErrore nella cancellazione dell'alimento \"%s\" dalla ricetta \"%s\" !\n",alimenti[IndiceAlimento].Nome,ricette[indiceRicetta].Nome);

					//ripristino i vecchi valori anche nel vettore dato che si e' verificato un errore nella modifica su file
					ricette[indiceRicetta].Alimenti_Quantita[1][IndiceAlimentoInRIcetta]=vecchiaQuantitaAlimento;
					ricette[indiceRicetta].Alimenti_Quantita[0][IndiceAlimentoInRIcetta]=vecchioIndiceAlimento;

					return 0;
				}
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste!\n",scelta);
		return 0;
	}


}






/**
 * Funzione che, data una ricetta come parametro, gestisce tutto quello che riguarda
 * la modifica della relativa quantita di un alimento che compone la ricetta.
 * La funzione chiede in input l'alimento di cui si vuole cancellare la quantita, controlla se
 * fa parte della ricetta, chiede la nuova quantita, effettua la modifica e successivamente applica la
 * modifica sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @pre indiceRicetta deve essere un indice di alimento valido. Se non lo dovesse essere potrebbe
 * causare una lettura illecita della memoria o una modifica su file incorretta.
 */
int modifica_quantita_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento di cui modificare la quantita: ");
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	int indiceAlimento;
	int indiceAlimentoInRicetta;

	int vecchiaQuantita;

	//controllo se l'alimento inserito in input esiste nel vettore di alimenti
	if((indiceAlimento=get_alimento(alimenti,lunghezzaVettoreAlimenti,scelta,false)) > -1){

		//controllo se l'alimento inserito fa parte della ricetta
		if((indiceAlimentoInRicetta=get_alimento_ricetta(ricette,indiceRicetta,indiceAlimento)) == -1){
			printf("\nL'alimento che stai cercando di cancellare non fa parte della ricetta \"%s\"\n",ricette[indiceRicetta].Nome);
			return 0;
		}else{

			vecchiaQuantita=ricette[indiceRicetta].Alimenti_Quantita[1][indiceAlimentoInRicetta];

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

				//annullo la modifica anche sul vettore in quanto si e' veirificato un errore nella modifica su file
				ricette[indiceRicetta].Alimenti_Quantita[1][indiceAlimentoInRicetta]=vecchiaQuantita;

				return 0;
			}
		}
	}else{
		printf("\nL'alimento \"%s\" non esiste!\n",scelta);
		return 0;
	}

}






/**
 * Funzione che gestisce il menu che riguarda le opzioni di modifica degli
 * alimenti che compongono una ricetta.
 * La funzione chiede di scelgliere che tipo di modifica fare e successivamente
 * richiama le opportune funzioni.
 *
 */
int modifica_alimenti_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti){

	int numScelta;

	do{

		//pulisco lo schermo
		system("cls");

		printf("\nMODIFICA ALIMENTI CHE FORMANO \"%s\"\n",ricette[indiceRicetta].Nome);

		visualizza_alimenti_ricetta(ricette,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);

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

		if(numScelta != 0) {
			char c[LUNGHEZZA_STRINGA];
			printf("\nPremi per continuare....");
			fgets(c,LUNGHEZZA_STRINGA,stdin);
		}

	}while(numScelta!=0);

	return 1;
}









/**
 * Funzione che gestisce il menu che riguarda la scelta del tipo di modifica da effettuare
 * sulla ricetta. La funzione chiede in input la ricetta da modificare, il tipo
 * di modifica da fare , effettua i controlli adeguati e infine richiama le
 * opportune funzioni in base al tipo di modifica.
 *
 */
int scelta_modifica_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	//pulisco lo schermo
	system("cls");

	printf("\nMODIFICA RICETTA\n");
	printf("\n%s\n",STRINGASTERISCHI);

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome della ricetta:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	int indice;

	if ((indice=get_ricetta(ricette, lunghezzaVettoreRicette,scelta,true)) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nRicetta Trovata\n\n");

		//devo fare la modifica effettiva
		int numScelta=1;
		do{

			//pulisco lo schermo
			system("cls");

			printf("\nMODIFICA DELLA RICETTA \"%s\" \n",ricette[indice].Nome);

			numScelta=fai_scelta(MENU_MODIFICA_RICETTE);

			switch(numScelta){
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

			if(numScelta != 0 && numScelta > 3) {
				char c[LUNGHEZZA_STRINGA];
				printf("\nPremi per continuare..23..");
				fgets(c,LUNGHEZZA_STRINGA,stdin);
			}

		} while (numScelta != 0);

	}else printf("\n\nNon esiste nessuna ricetta che si chiama in quel modo!\n\n");

	return 1;
}







/**
 * Data una ricetta passata come parametro, la funzione calcola il numero
 * di porzioni che e' possibile preparare per quella ricetta in base alle
 * quantita degli alimenti presenti nel frigo.
 *
 */
int get_numero_porzioni_possibili_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceRicetta){

	int i;
	int porzPoss[NUMERO_MAX_ALIMENTI];
	int min=-1;
	alimento alim;

	//for che scorre il vettore di alimenti della ricetta
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){

		if(ricette[indiceRicetta].Alimenti_Quantita[0][i] != -1){
			alim=alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]];

			//controllo se la quantita disponibile dell'alimento e' >= della quantita di alimento che necessita la ricetta
			if(get_quantita(alim) >= ricette[indiceRicetta].Alimenti_Quantita[1][i]){
				if(ricette[indiceRicetta].Alimenti_Quantita[1][i]!=0){

					//calcolo il numero di porzioni possibili per quel alimento
					porzPoss[i]= (int)(get_quantita(alim)/ricette[indiceRicetta].Alimenti_Quantita[1][i]);

					//il numero di porzioni possibili finale sara il minimo tra tutte le porzioni possibili
					//dei singoli alimenti
					if(min==-1) min=porzPoss[i];
					if(min>porzPoss[i]) min=porzPoss[i];
				}
			}else return 0;
		}

	}
	return min;
}











/**
 * Data la ricetta come parametro, la funzione ha il compito di decrementare tutte le quantita
 * disponibili degli alimenti che compongono una ricetta in maniera tale a rendere
 * effettiva la consumazione di una determinata ricetta.
 *
 * @pre controllare se e' effettivamente possibile consumare quella ricetta e quelle quantita
 * tramite la funzione get_numero_porzioni_possibili_ricetta() in quanto si potrebbero
 * verificare errori nelle quantita degli alimenti disponibili.
 */
int consuma_ricetta_su_alimenti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceRicetta,int porzioni){
	int i;
	for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
		if(ricette[indiceRicetta].Alimenti_Quantita[0][i] > -1){
			int quantita=ricette[indiceRicetta].Alimenti_Quantita[1][i];
			//incremento l'utilizzo dell'alimento
			alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]].Utilizzo+=(quantita*porzioni);

			decrementa_quantita_alimento(&alimenti[ricette[indiceRicetta].Alimenti_Quantita[0][i]],(quantita*porzioni));
		}
	}
	return 1;
}







/**
 * Funzione che si occupa di tutto quello che rigurda l'aggiunta di una ricetta.
 * La funzione chiede in input tutti gli attributi della ricetta, fa gli
 * opportuni controlli e la aggiunge sia sul vettore di alimenti
 * che sul file Ricette.sf.
 * L'aggiunta sul file viene fatta dichiarando un altro vettore di ricette
 * di lunghezza maggiore di 1. Il vecchio vettore viene deallocato e viene
 * passato come valore di ritorno l'indirizzo del nuovo vettore
 * all'interno del puntatore nuovoIndirizzoRicette passato come parametro.
 *
 */
int inserimento_ricetta(alimento alimenti[],int lunghezzaVettoreAlimenti,ricetta ricette[],int lunghezzaVettoreRicette,int *nuovoIndirizzoRicette){

	//pulisco lo schermo
	system("cls");

	printf("\nINSERIMENTO DI UNA RICETTA\n\n%s\n",STRINGASTERISCHI);
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
			printf("\n\nINSERIMENTO ALIMENTI DELLA RICETTA\n\n%s\n",STRINGASTERISCHI);
			boolean flag;
			int flag1=0;
			do{
				flag=false;

				if(flag1==0){
					flag1 = inserimento_alimento_ricetta(ricette2,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);
				}else inserimento_alimento_ricetta(ricette2,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);

				visualizza_alimenti_ricetta(ricette2,indiceRicetta,alimenti,lunghezzaVettoreAlimenti);

				if(fai_scelta_booleana("\n\nVuoi aggiungere un altro alimento alla ricetta? ") == true) flag=true;
				if(flag1 == 0) printf("\n\nDevi inserire almeno un alimento!\n\n");
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

	printf("Premi per continuare....");
	getchar();
	system("cls");


	return lunghezzaVettoreRicette;
}






/**
 * Funzione che cerca all'interno del vettore di ricette tutte le ricette che e' possibile
 * cucinare in base alle quantita e alle disponibilita degli alimenti.
 *
 */
int* get_ricette_che_si_possono_cucinare(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int* numeroRicettePossibili){
	int i;

	int* vettoreRicettePossibili = (int*) calloc(lunghezzaVettoreRicette,sizeof(int));

	int indiceVettoreRicettePossibili=0;

	for(i=0;i<lunghezzaVettoreRicette;i++){

		//verifico che e' possibile cucinare almeno una porzione della ricetta
		if(get_numero_porzioni_possibili_ricetta(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,i) > 0){

			//se la ricetta si puo cucinare la salvo nel vettore di indici
			vettoreRicettePossibili[indiceVettoreRicettePossibili]=i;
			indiceVettoreRicettePossibili++;
		}
	}

	//creo un vettore di lunghezza pari al numero di ricette trovate
	//in maniera da deallocare quello di grandezza massima e continuare a
	//lavorare con il numero giusto di locazioni di memoria
	int* vettore= (int*) calloc(indiceVettoreRicettePossibili,sizeof(int));

	for(i=0;i<indiceVettoreRicettePossibili;i++){
		vettore[i]=vettoreRicettePossibili[i];
	}

	(*numeroRicettePossibili) = indiceVettoreRicettePossibili;

	return vettore;
}






/**
 * Funzione che ha il compito di visualizzare in console all'utente tutte le ricette che
 * e' possibile cucinare in base alle disponibilita degli alimenti.
 * La visualizzaione delle ricette e' fatta in maniera ordinata facendo vedere prima
 * i preferiti e poi il resto in ordine di frequenza.
 *
 */
int visualizza_ricette_che_si_possono_cucinare(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	//pulisco lo schermo
	system("cls");

	printf("\nSUGGERIMENTO DELLE RICETTE CHE SI POSSONO PREPARARE\n\n%s\nLe ricette saranno ordinate prima\nper i preferiti e poi per frequenza\n\n",STRINGASTERISCHI);


	int numeroRicettePossibili=0;

	//richiamo la funzione che cerca le ricette che si possono cucinare
	int* vettoreRicettePossibili=get_ricette_che_si_possono_cucinare(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,&numeroRicettePossibili);

	int i;
	boolean flag=false;

	if(numeroRicettePossibili == 0) printf("\nNon puoi cucinare nessuna ricetta in quanto non hai abbastanza ingredienti per qualunque ricetta!\n\n\n");
	else{

		printf("\nLe ricette saranno ordinate per freferiti e per frequenza\n");

		//ordino per preferiti
		merge_sort_ricette(ricette,0,numeroRicettePossibili-1,vettoreRicettePossibili,MODALITA_ORDINAMENTO_PREFERITI);

		printf("\nLe ricette che e' possibile preparare sono:\n");
		for(i=0;i<numeroRicettePossibili;i++){

			//se e' la prima volta che trovo un elemento non preferito, ordino tutto il resto del vettore
			//in base alla frequenza quindi ordino tutti i non preferiti per frequenza
			if(exist_preferito(ricette,&vettoreRicettePossibili[i]) == false && flag==false){
				merge_sort_ricette(ricette,i,numeroRicettePossibili-1,vettoreRicettePossibili,MODALITA_ORDINAMENTO_FREQUENZA);
				flag=true;
			}
			printf("%d - %25s \t| Kcal per porzione: %5.2f \t| %s\n", i,
										ricette[vettoreRicettePossibili[i]].Nome, ricette[vettoreRicettePossibili[i]].Kcal_Porzione,(exist_preferito(ricette,&vettoreRicettePossibili[i]) == true)? "PREF":"");
		}
		printf("\n\n");
	}

	return 1;
}








/**
 * Funzione che gestisce il menu relativo alle opzioni delle ricette cioe'
 * chiede all'utente di fare una scelta di opzione, effettua i controlli
 * e richiama le specifiche funzioni.
 *
 */
int scelta_opzioni_ricette(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoRicette){

	int numScelta;

	//imposto come nuovo indirizzo del vettore di ricette, il suo stesso indirizzo
	(*nuovoIndirizzoRicette)=(int)ricette;

	do {

		//pulisco lo schermo
		system("cls");

		printf("\nOPZIONI DELLE RICETTE\n");

		numScelta = fai_scelta(MENU_RICETTE);

		switch (numScelta) {
		case 1:

			//viualizza lista ricette
			scelta_visualizzazione_ricette(ricette, lunghezzaVettoreRicette);
			numScelta=0;
			break;

		case 2:

			//aggiungi ricetta
			lunghezzaVettoreRicette=inserimento_ricetta(alimenti,lunghezzaVettoreAlimenti,ricette,lunghezzaVettoreRicette,nuovoIndirizzoRicette);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di una nuovo ricetta
			ricette=(ricetta*)(*nuovoIndirizzoRicette);

			break;
		case 3:

			//modifica ricetta
			scelta_modifica_ricetta(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

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

		if(numScelta != 0 && numScelta > 5) {
			char c[LUNGHEZZA_STRINGA];
			printf("\nPremi per continuare....");
			fgets(c,LUNGHEZZA_STRINGA,stdin);
		}

	} while (numScelta != 0);

	return lunghezzaVettoreRicette;
}


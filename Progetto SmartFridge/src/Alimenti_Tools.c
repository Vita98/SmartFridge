/**
 *  @file 	   Alimenti_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Alimenti_Tools.c
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include "Tipi_Dato.h"
#include <String.h>
#include "Data_Tools.h"
#include "Ordinamenti_Tools.h"







/**
 * Dato l'alimento come parametro, la funzione calcola la quantita
 * di alimento presente all'interno dello smart fridge.
 *
 * @pre il vettore di scadenze dell'alimento deve essere gia
 * inizializzato altrimenti la funzione potrebbe restituire risulatati
 * inattesi.
 */
int get_quantita(alimento alim) {

	int quantita = 0, j;
	for (j = 0; j < LUNGHEZZA_VET_SCADENZE; j++) {
		quantita += alim.Scadenze[j].Quantita;
	}
	return quantita;
}





/**
 * Dato l'alimento e la data , passati come parametro, la funzione verifica
 * se la data e' una data di scadenza dell'alimento presente nello
 * smart fridge.
 *
 * @pre il vettore di scadenze dell'alimento deve essere gia
 * inizializzato altrimenti la funzione potrebbe restituire risulatati
 * inattesi.
 *
 * @pre la funzione controlla se la data e' uguale confrontando
 * solamente il giorno, mese e anno.
 */
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





/**
 * Data il nome della ricetta come parametro, la funzione verifice
 * se esiste una ricetta con quel nome nel vettore di alimenti anche esso
 * passato come parametri.
 * Se il parametro visibilita e' true la funzione ricerchera la ricetta
 * tra tutti gli alimenti disponibili altrimenti se e' false, la ricerca
 * verra effettuata anche tra gli alimenti cancellati o non disponibili.
 *
 * @pre la stringa dei parametri di ricerca non deve essere elaborata
 * in nessun modo in quanto all'interno della funzione essa viene
 * elaborata in maniera tale da assicurare una corrispondenza,
 * nell'eventualita di matching con stringhe maiusole e minuscole
 * o di presenza di spazi all'inizio o alla fine.
 */
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








/**
 * Funzione che ha il compito di visualizzare in console, in una determinata formattazione,
 * le informazioni riguardanti gli alimenti presenti nello smart fridge.
 *
 * @pre il vettore di alimenti deve essere pieno o inizializzato.
 *
 * @warning la lunghezza del vettore deve essere la lunghezza effettiva
 * in quanto una discordanza potrebbe causare una lettura di porzioni
 * di memoria non allocate.
 */
int visualizza_alimenti(alimento alimenti[], int lunghezzaVettoreAlimenti) {

	int i;
	int cont=0;

	printf("Alimenti presenti:\n");
	for (i = 0; i < lunghezzaVettoreAlimenti ; i++) {

		if(alimenti[i].Visibilita == true || alimenti[i].Visibilita == false )
		printf("%d - %30s \t| Utilizzo: %5d \t| Id: %3d   |   Quantita: %5d   | Kcal: %5.3f  | V:%s\n", ++cont,
		alimenti[i].Nome, alimenti[i].Utilizzo, alimenti[i].ID_Alimento,
		get_quantita(alimenti[i]),alimenti[i].Kcal_Pezzo,(alimenti[i].Visibilita)?"true":"false");
	}

	//controllo se ha visualizzato almento un elemento
	if (cont == 0) printf("\nNon ci sono alimenti disponibili!\n");
	return 1;
}






/**
 * Dato l'alimento passato come parametro, la funzione lo sovrascrive
 * alla sua vecchia versione all'interno del file.
 * Viene utilizzato per far riflettere le modifiche dal vettore
 * al file.
 *
 * @pre il file Alimenti.sf deve gia esistere.
 * @pre non deve essere stato modificato l'ID dell'alimento
 * in quanto potrebbe andare a effettuare delle modifiche
 * inopportune all'interno del file.
 */
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





/**
 * Dato l'alimento passato come parametro, la funzione lo aggiunge in coda
 * al file di alimenti.
 *
 * @pre l'ID dell'alimento deve essere il numero sequenziale
 * dell'alimento su file.
 */
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





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica del nome di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 * @pre l'indice passato come parametro deve essere un indice valido
 * per il vettore di alimenti.
 */
int modifica_nome_alimento(alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceAlimento){

	if(indiceAlimento >= lunghezzaVettoreAlimenti || indiceAlimento < 0) return 0;

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
		return 0;
	}

	return 1;

}





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica delle kcal di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 */
int modifica_kcal_alimento(alimento alimenti[],int indiceAlimento){
	double Kcal=0.0;

	Kcal=fai_scelta_double("\nInserisci le nuove kcal dell'Alimento:\n");

	//effettuo la modifica nel vettore
	alimenti[indiceAlimento].Kcal_Pezzo=Kcal;

	//effettuo la modifica su file
	if(modifica_alimento_su_file(alimenti[indiceAlimento]) == 1) printf("\nModifica delle Kcal avvenuta con successo!\n");
	else{
		printf("\nErrore nella modifica delle Kcal su file!\n");
		return 0;
	}

	return 1;
}






/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica del peso di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 */
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
		return 0;
	}

	return 1;
}






/**
 * Dato l'indice di un alimento come parametro, la funzione visualizza in console
 * tutto il vettore di scadenze, con le relative quantita e date di scadenza.
 *
 */
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





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica della quantita di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 */
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
	else{
		printf("\nErrore nella modifica della quantita su file!\n");
		return 0;
	}

	return 1;
}






/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica delle scadenze di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 */
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
		return 0;
	}

	return 1;
}







/**
 * Funzione che ha il compito di sottrarre alle quantita del vettore
 * di scadenze di un alimento,passato come parametro, una quantita
 * anchessa passata come parametro.
 * Viene usata quando viene consumato un pasto e bisogna sottrarre
 * le quantita consumate a quelle disponibili.
 *
 * @pre la quantita da sottrarre deve essere minore o uguale
 * della quantita totale disponibile dell'alimento.
 */
int decrementa_quantita_alimento(alimento* alim, int quantita){
	int  j;
	for (j = LUNGHEZZA_VET_SCADENZE-1; j >= 0; j--) {
		if((*alim).Scadenze[j].Quantita>=quantita){
			(*alim).Scadenze[j].Quantita-=quantita;
			 quantita=0;
			 if(j==0 && (*alim).Scadenze[j].Quantita == 0){
				 (*alim).Visibilita=false;
			 }
			 break;
		}
		else{
			quantita=quantita-(*alim).Scadenze[j].Quantita;
			(*alim).Scadenze[j].Quantita=0;
		}
	}
	return modifica_alimento_su_file((*alim));
}







/**
 * Funzione che gestisce tutte le operazioni per la modifica di un alimento.
 * Chiede all'utente l'alimento da modificare e che tipo di modifica fare
 * per poi richiamare le funzioni rispettive per effettuare la modifica.
 *
 * @pre il vettore di alimenti deve essere inizializzato.
 * @pre la lunghezza del vettore di alimenti deve corrispondere con
 * la reale lunghezza del vettore.
 */
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






/**
 * Funzione che ha il compito di richiamare l'algoritmo di ordinamento
 * secondo la modalita di ordinamento passata come parametro
 * e, successivamente, di visualizzare tutti gli alimenti ordinati.
 *
 * @pre il numero di modalita di ordinamento deve essere una modalita
 * valida.
 */
int visualizza_alimenti_ordinati(alimento alimenti[],int lunghezzaVettoreAlimenti, int modalitaOrdinamento) {

	int i;
	int indici[lunghezzaVettoreAlimenti];

	printf("Ricette presenti \n");

	sort_alimenti(alimenti, indici, lunghezzaVettoreAlimenti, modalitaOrdinamento);
	int cont=0;

	for (i = 0; i <lunghezzaVettoreAlimenti ; i++) {
		if (alimenti[indici[i]].Visibilita==true){
			printf("%d - %30s \t| Kcal per porzione: %5.2f \t| Id: %3d  |  Freq: %5d  |  Visib: %s\n", ++cont,
							alimenti[indici[i]].Nome, alimenti[indici[i]].Kcal_Pezzo, alimenti[indici[i]].ID_Alimento, alimenti[indici[i]].Utilizzo,(alimenti[indici[i]].Visibilita)?"true":"false");
		}
	}
	return 1;
}







/**
 * Funzione che gestisce tutte le operazioni di ordinamento del vettore di alimenti.
 * La funzione chiede all'utente in che modalita di ordinamento si vuole
 * visualizzare il vettore e richiama le opportune funzioni.
 *
 */
int scelta_visualizzazione_alimenti(alimento alimenti[],int lunghezzaVettoreAlimenti){
	int numScelta=0;

		do {
			numScelta = fai_scelta(MENU_ORDINAMENTO_RICETTE);

			switch (numScelta) {

			case 1:
				//ordinamento Normale
				visualizza_alimenti(alimenti,lunghezzaVettoreAlimenti);
				break;

			case MODALITA_ORDINAMENTO_KCAL_PORZIONE:
				//ordina per kcal
				visualizza_alimenti_ordinati(alimenti,lunghezzaVettoreAlimenti,numScelta);
				break;

			case MODALITA_ORDINAMENTO_FREQUENZA:
				//ordina per frequenza
				visualizza_alimenti_ordinati(alimenti,lunghezzaVettoreAlimenti,numScelta);
				break;

			case 0:
				//case di uscita dal sottomenu
				break;

			default:
				printf("Scelta errata! Riprova!\n");

			}
		}while(numScelta != 0);

		return 1;
}





/**
 * Funzione che gestisce il menu riguardante tutte le opzioni
 * relative agli alimenti.
 * Chiede all'utente di fare una scelta e richiama le opportune funzioni
 * per svolgere quel determinato compito.
 *
 */
int scelta_opzioni_alimenti(alimento alimenti[], int lunghezzaVettoreAlimenti) {
	int NumScelta=1;

	do {
		NumScelta = fai_scelta(MENU_ALIMENTI);

		switch (NumScelta) {
		case 1:

			//visualizza alimenti
			scelta_visualizzazione_alimenti(alimenti, lunghezzaVettoreAlimenti);

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

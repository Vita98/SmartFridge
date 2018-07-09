/**
 *  @file Pasti_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Pasti_Tools.h.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include "Tipi_Dato.h"
#include "Messaggi_Menu.h"
#include "Ricette_Tools.h"
#include "Data_Tools.h"
#include "Alimenti_Tools.h"
#include "Caricamento_Vettori_Tools.h"




/**
 * Funzione che aggiunge un pasto, con gli attributi passati come
 * parametro, in coda sul file dei pasti.
 * Se il file Storico_Pasti.sf non esiste la funzione lo crea.
 *
 * @pre idRicetta deve essere un indice di ricetta esistente
 * in quanto nella lettura dello storico dei pasti si potrebbe
 * verificare un errore nella visualizzazione della ricetta inesistente.
 *
 */
int aggiungi_pasto_su_file(int numPorzioni,int idRicetta){

	FILE *file;
	pasto pp;

	pp.ID_Ricetta=idRicetta;
	pp.Porzioni=numPorzioni;
	pp.visibilita=true;

	get_data_pointer(&pp.Data_Ora);

	if ((file = fopen("Storico_Pasti.sf", "ab+")) == NULL) {
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

	if ((fileStoricoPasti = fopen("Storico_Pasti.sf", "rb")) != NULL)
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







/**
 * Funzione che gestisce tutte le operazioni per la consumazione di un pasto.
 *
 * @pre lunghezzaVettoreRicette deve essere la lunghezza effettiva del vettore
 * di ricette in quanto ,se non lo fosse, potrebbe causare una lettura di porzioni
 * di memoria non allocate al vettore oppure una lettura parziale del vettore di ricette.
 *
 * @pre lunghezzaVettoreAlimenti deve essere la lunghezza effettiva del vettore
 * di ricette in quanto ,se non lo fosse, potrebbe causare una lettura di porzioni
 * di memoria non allocate al vettore oppure una lettura parziale del vettore di alimenti.
 */
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







/**
 * Funzione che stampa all'utente tutti i pasti consumati durante una settimana
 * passata come parametro.
 *
 * @pre giornoSettimana deve essere un numero compreso tra 0 e 6.
 */
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

	if ((file = fopen("Storico_Pasti.sf", "rb")) == NULL || NumeroSettimana < 0) {
				return 0;
	} else {
		printf("\n\n%15s   %10s | %20s | %15s\n","Giorno","Data","Pasto","Porzioni");
		printf("-----------------------------------------------------------------------------");
		//scorro i giorni da lunedi fino al giorno della settimana corrente
		for(i=giornoSettimana;i>=0;i--){
			flag=false;
			//leggo tutto il file
			while(!feof(file)){
				int a=fread(&pp,sizeof(pasto),1,file);

				//controllo che la distanza tra la data attuale e la data del pasto letta da file
				//sia uguale alla distanza tra il giorno della settimana che si vuole visualizzare
				//e la data attuale
				if(get_distanza_in_giorni(pp.Data_Ora,d,delay) == (i+(NumeroSettimana*NUMERO_GIORNI)) && a > 0 && pp.visibilita==true){

					//controllo se e' il primo ad essere trovato o no
					if(flag==false){
						printf("\n%15s - %2d/%2d/%4d | %20s | %15d",indice_to_giorni_settimana(giornoSettimana-i),pp.Data_Ora.Giorno,pp.Data_Ora.Mese,pp.Data_Ora.Anno,ricette[pp.ID_Ricetta].Nome,pp.Porzioni);

						flag=true;
					}else printf("\n%15s   %10s | %20s | %15d","-","-",ricette[pp.ID_Ricetta].Nome,pp.Porzioni);
				}
			}
			if(flag==false) printf("\n%15s   %10s | %20s | %15s",indice_to_giorni_settimana(giornoSettimana-i)," ","-","-");
			rewind(file);
		}

		printf("\n\n");

		fclose(file);
	}

	return 1;

}





/**
 * Funzione che gestisce la chiamata della funzione per la visualizzazione
 * del menu setimanale della settimana corrente.
 */
int visualizza_menu_settimana_in_corso(ricetta ricette[],int lunghezzaVettoreRicette){

	//Richiamo la funzione di stampa del menu della iesima settimana
	//in maniera che stampi la settimana corrente
	if(stampa_iesimo_menu_settimanale(ricette,lunghezzaVettoreRicette,0,get_data('W')) == 0){
		printf("\n\nNon e' mai stato consumato niente!\n\n");
	}

	return 1;

}






/**
 * In base al numero di giorni passato come parametro
 * viene calcolato il numero di settimane a cui
 * corrispondono i giorni passati come parametro.
 *
 * @pre giorni deve essere positivo, se non lo e'
 * la funzione ristituira 0.
 */
int get_numero_settimane(int giorni){
	int NumeroSettimane=0;
	while(giorni >= 1){
		NumeroSettimane++;
		giorni-=7;
	}
	return NumeroSettimane;
}






/**
 * Funzione che gestisce la chiamata della funzione per la visualizzazione
 * del menu setimanale di settimane passate relativamente a quella corrente.
 */
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
			//a ritroso di NumeroSettimane SETTIMANE
			if(numeroSettimane!=0){
				if(stampa_iesimo_menu_settimanale(ricette,lunghezzaVettoreRicette,numeroSettimane,6) == 0){
					printf("\n\nNon e' mai stato consumato niente!\n\n");
				}

			}else if(stampa_iesimo_menu_settimanale(ricette,lunghezzaVettoreRicette,0,get_data('W')) == 0){
				printf("\n\nNon e' mai stato consumato niente!\n\n");
			}
		}else{
			//caso in cui la data inserita in input sia sucessiva alla data corrente
			printf("\nLa data non puo essere superiore alla data corrente! Reinseriscila!\n");
		}
	}while(flag==false);


	return 1;
}






/**
 * Funzione che visualizza all'utente un menu per fargli
 * scegliere il tipo di settimana di cui vedere
 * il menu settimanale.
 */
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

	return 1;
}





/**
 * Funzione che effettua la cancellazione di un pasto dal file.
 * Inoltre la funzione si occupa di gestire le modifiche della
 * frequenza delle ricette e della quantita e dell'utilizzo
 * degli alimenti.
 *
 * @pre indicePasto deve essere un indice valido
 *
 * @warning se indicePasto non e' valido, non e'garantito
 * il corretto funzionamento della funzione in quanto
 * andrebbe a modificare un pasto inesistente.
 */
int cancella_iesimo_pasto_da_file(int indicePasto,alimento alimenti[],ricetta ricette[]){
	FILE *fileStoricoPasti;
	pasto pp;

	if ((fileStoricoPasti = fopen("Storico_Pasti.sf", "rb+")) == NULL) {
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

				//decremento l'utilizzo dell'alimento
				alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]].Utilizzo-=ricette[pp.ID_Ricetta].Alimenti_Quantita[1][i]*pp.Porzioni;

				//incremento la quantita dell'alimentoc
				alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]].Scadenze[0].Quantita += ricette[pp.ID_Ricetta].Alimenti_Quantita[1][i]*pp.Porzioni;
				if(alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]].Visibilita==false) alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[1][i]].Visibilita=true;
				modifica_alimento_su_file(alimenti[ricette[pp.ID_Ricetta].Alimenti_Quantita[0][i]]);
			}
		}

		//devo aggiornare la frequenza della ricetta
		ricette[pp.ID_Ricetta].Frequenza-=pp.Porzioni;
		modifica_ricetta_su_file(ricette[pp.ID_Ricetta]);

		//aggiorno il file di storico pasti
		fseek(fileStoricoPasti,indicePasto*sizeof(pasto),SEEK_SET);
		fwrite(&pp,sizeof(pasto),1,fileStoricoPasti);

		fclose(fileStoricoPasti);
	}

	return 1;
}







/**
 * Funzione che gestisce tutte le operazioni per la cencellazione di un pasto.
 *
 * @pre il file Storico_Pasti.sf deve esistere gia in quanto
 * viene aperto in lettura.
 */
int cancella_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[]){

	data_ora dataPasto,dataOdierna;
	FILE *file_Storico_Pasti;
	pasto past;
	int indice=0;
	int lunghezzaVettoreIndici=get_lunghezza_file_storico_pasti();
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
			if ((file_Storico_Pasti = fopen("Storico_Pasti.sf", "rb")) == NULL) {
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

				if(indiceVetIndici != 0){
					printf("\n\n");
					int sceltaIndice;
					do{
						sceltaIndice=fai_scelta("\nInserisci il numero corrispondente al pasto che si vuole cancellare:");

						if(sceltaIndice>indiceVetIndici) printf("\nIndice non valido! Reinseriscilo!\n");

					}while(sceltaIndice>indiceVetIndici);

					if(cancella_iesimo_pasto_da_file(indiciSuFile[sceltaIndice],alimenti,ricette)) printf("\nCancellazione del pasto effettuata con successo!\n");
					else printf("\nErrore nella cancellazione del pasto su file!\n");
				}else printf("\n\nNella data inserita non sono stati consumati pasti!\n");
			}
		}
	}while(get_distanza_in_giorni(dataPasto,dataOdierna,0) < 0 );

	return 1;
}







/**
 * Passato il pasto come parametro e l'indice su file,
 * la funzione salva il pasto sul file Storico_Pasti.sf
 * nella posizione indicePasto partendo dall ínizio del file.
 *
 * @pre il file Storico_Pasti.sf deve gia esistere.
 * @pre indicePasto deve essere un indice valido per la
 * grandezza del file.
 *
 */
int modifica_iesimo_pasto_su_file(pasto iesimoPasto,int indicePasto){

	FILE *fileStoricoPasti;

	if ((fileStoricoPasti = fopen("Storico_Pasti.sf", "rb+")) == NULL) {
		return 0;
	} else {
		fseek(fileStoricoPasti,indicePasto*sizeof(pasto),SEEK_SET);
		fwrite(&iesimoPasto,sizeof(pasto),1,fileStoricoPasti);
		fclose(fileStoricoPasti);
		return 1;
	}

}






/**
 * Data la posizione del pasto su file come parametro,
 * la funzione restituisce il pasto letto in quella posizione.
 *
 * @pre il file Storico_Pasti.sf deve esistere gia.
 * @pre indicePasto deve essere una posizione valida e piena del file.
 */
pasto leggi_iesimo_pasto(int indicePasto){
	FILE *fileStoricoPasti;
	pasto pp;

	if ((fileStoricoPasti = fopen("Storico_Pasti.sf", "rb")) == NULL) {
		return pp;
	} else {
		fseek(fileStoricoPasti,indicePasto*sizeof(pasto),SEEK_SET);
		fread(&pp,sizeof(pasto),1,fileStoricoPasti);
		fclose(fileStoricoPasti);
		return pp;
	}
}








/**
 * In base alla ricetta e al numero di porzioni aggiuntive passate come parametro,
 * la funzione verifica se è possibile aggiungere porzioni ad un pasto
 * consumato nel passato.
 * Principalemente verifica se gli alimenti della ricetta non sono mai stati
 * indisponibili in quanto l'aggiunta del pasto genererebbe una quantita
 * negativa di alimenti.
 *
 * @pre indiceRicetta deve essere un indice di ricetta valido.
 *
 */
boolean is_possible_add_porzioni_pasto(int indiceRicetta,int porzioniAggiuntive,ricetta ricette[],alimento alimenti[],data_ora data_pasto){

	int i;
	int numeroPorzioniPossibili=0;
	boolean flag;


	//a questo punto tutti gli alimenti della ricetta di cui si vuole aggiungere la quantita sono disponibili nel presente;
	//bisogna controllare se erano disponibili in quel momento del passato o se
	//la modifica che si vuole fare e cronologicamente antecedente alla prima spesa
	//degli alimenti della ricetta.
	FILE *fileStoricoPasti,*fileStoricoSpesa;
	if ((fileStoricoPasti = fopen("Storico_Pasti.sf", "rb")) == NULL) {
		return false;
	} else if ((fileStoricoSpesa = fopen("Storico_Spesa.sf", "rb")) == NULL) {
		return false;
	} else {
		//tutti e 2 i file sono stati aperti con successo
		elemento_spesa elSpesa;
		pasto past;
		int quantitaAlimentiDisponibili[2][NUMERO_MAX_ALIMENTI]; //riga 1 : id alimento   riga 2: quantita disponibile alla data dataRiferimento
		int vettoreQuantitaMinime[NUMERO_MAX_ALIMENTI];

		//carico gli indici degli alimenti della ricetta all'interno del vettore di sopra
		for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
			quantitaAlimentiDisponibili[0][i] = ricette[indiceRicetta].Alimenti_Quantita[0][i];
			quantitaAlimentiDisponibili[1][i] = 0;
			vettoreQuantitaMinime[i]=-1;
		}
		flag=false;

		if(fread(&past,sizeof(pasto),1,fileStoricoPasti) > 0){

			if(fread(&elSpesa,sizeof(elemento_spesa),1,fileStoricoSpesa) > 0){

				//ripeto il while solo fino alla fine dello storico pasti perche mi interessa sapere le quantita minime fino
				//all'ultimo pasto prima dell'ultima spesa in quanto l'ultima spesa puo essere trascurata dato
				//che andrebbe solo ad aumentare le quantita o al massimo lasciarle invariate
				while(!feof(fileStoricoPasti)){

					//confronto le due date
					if(data_compare(past.Data_Ora,elSpesa.Data_Ora)  <= 0){
						//caso in cui il pasto e' successivo alla spesa

						if(!feof(fileStoricoSpesa)){
							//controllo che l'alimento della spesa si presente nella ricetta
							int indiceAlim;
							if((indiceAlim = get_alimento_ricetta(ricette,indiceRicetta,elSpesa.ID_Alimento)) > -1){
								quantitaAlimentiDisponibili[1][indiceAlim] += elSpesa.Quantita;
							}
							if(fread(&elSpesa,sizeof(elemento_spesa),1,fileStoricoSpesa) <= 0) break;
						}

					}else{

						//controllo se il pasto che sto leggendo e' lo stesso di quello che voglio cambiare
						if(past.ID_Ricetta == indiceRicetta){
							flag=true;
							for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
								if(quantitaAlimentiDisponibili[0][i] != -1){
									quantitaAlimentiDisponibili[1][i] -= (ricette[indiceRicetta].Alimenti_Quantita[1][i]*past.Porzioni);

									//mi memorizzo la quantita minima di tutta la cronologia di un pasto solo se la data di consumazione e' successiva alla data del pasto che
									//si vuole modificare
									if((vettoreQuantitaMinime[i] == -1 || quantitaAlimentiDisponibili[1][i] < vettoreQuantitaMinime[i]) && data_compare(past.Data_Ora,data_pasto) >= 0) vettoreQuantitaMinime[i] = quantitaAlimentiDisponibili[1][i];
								}
							}
						}else{
							//se non lo è devo controllare se questa ricetta consumata ha gli stessi alimenti della
							//ricetta che voglio modificare
							int j;
							for(i=0;i<NUMERO_MAX_ALIMENTI;i++)
							for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
								//se l'alimento della ricetta consumata e' anche un alimento della ricetta che volgio modificare
								if(ricette[past.ID_Ricetta].Alimenti_Quantita[0][i] == quantitaAlimentiDisponibili[0][j]){
									quantitaAlimentiDisponibili[1][j] -= (ricette[past.ID_Ricetta].Alimenti_Quantita[1][i]*past.Porzioni);
									break;
								}
							}
						}
						if(fread(&past,sizeof(pasto),1,fileStoricoPasti) <= 0) break;
					}
				}
			}
		}

		//caso in cui la ricetta non e' mai stata consumata e quindi non si trova mai un minimo
		if(flag==false){
			for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
				vettoreQuantitaMinime[i]=quantitaAlimentiDisponibili[1][i];
			}
		}

		//vedo quante porzioni posso preparare con le quantita minime calcolate
		int porzPoss[NUMERO_MAX_ALIMENTI];

		//for che scorre il vettore di alimenti della ricetta
		for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
			if(vettoreQuantitaMinime[i] != -1){
				if(vettoreQuantitaMinime[i] >= ricette[indiceRicetta].Alimenti_Quantita[1][i]){
					if(ricette[indiceRicetta].Alimenti_Quantita[1][i]!=0){
						porzPoss[i]= (int)(vettoreQuantitaMinime[i]/ricette[indiceRicetta].Alimenti_Quantita[1][i]);
						if(numeroPorzioniPossibili==0) numeroPorzioniPossibili=porzPoss[i];
						else if(numeroPorzioniPossibili>porzPoss[i]) numeroPorzioniPossibili=porzPoss[i];
					}
				}else numeroPorzioniPossibili = 0;
			}

		}
		if(porzioniAggiuntive <= numeroPorzioniPossibili) return true;
		else return false;
	}
}







/**
 * Funzione che effettua tutti i controlli e modifica un pasto
 * consumato nel passato nel caso in cui la modifica riguarda
 * solo le porzioni del pasto.
 *
 * @pre indicePasto deve essere un indice di pasto valido.
 * @pre nuovePorzioni deve essere un numero positivo.
 */
int modifica_porzioni_pasto(int indicePasto,alimento alimenti[],ricetta ricette[],int nuovePorzioni){

	pasto iesimoPasto;
	int vecchiePorzioni=0;

	//se le nuove porzioni sono meno di quelle di prima posso effettuare la modifica tranquillamente
	if(nuovePorzioni < (iesimoPasto = leggi_iesimo_pasto(indicePasto)).Porzioni  && nuovePorzioni > 0){
		vecchiePorzioni=iesimoPasto.Porzioni;
		iesimoPasto.Porzioni=nuovePorzioni;
		if(modifica_iesimo_pasto_su_file(iesimoPasto,indicePasto) == 1){

			//devo aggiungere alla frequanza della ricetta la differenza tra le vecchie porzioni e le nuove
			ricette[iesimoPasto.ID_Ricetta].Frequenza -= (vecchiePorzioni-nuovePorzioni);
			modifica_ricetta_su_file(ricette[iesimoPasto.ID_Ricetta]);

			//devo modificare l'utilizzo degli alimenti
			//bisogna aggiungere tutte le quantita cancellate
			int i;
			for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
				if(ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i] != -1) {

					//decremento l'utilizzo dell'alimento
					alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i]].Utilizzo-=ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[1][i]*(vecchiePorzioni-nuovePorzioni);

					//incremento la quantita dell'alimento
					alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i]].Scadenze[0].Quantita += ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[1][i]*(vecchiePorzioni-nuovePorzioni);
					if(alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i]].Visibilita==false) alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[1][i]].Visibilita=true;
					modifica_alimento_su_file(alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i]]);
				}
			}
			return 1;
		}else return 0;
	}else if(nuovePorzioni > iesimoPasto.Porzioni){
		vecchiePorzioni = iesimoPasto.Porzioni;

		//richiamo la funzione che verifica se in quella data avevo disponibile la quantita
		//di alimenti per consumare quelle porzioni in piu
		if(is_possible_add_porzioni_pasto(iesimoPasto.ID_Ricetta,nuovePorzioni-iesimoPasto.Porzioni,ricette,alimenti,iesimoPasto.Data_Ora) == true){
			iesimoPasto.Porzioni=nuovePorzioni;

			if(modifica_iesimo_pasto_su_file(iesimoPasto,indicePasto) == 1){

				//devo aggiungere alla frequanza della ricetta la differenza tra le vecchie porzioni e le nuove
				ricette[iesimoPasto.ID_Ricetta].Frequenza += (nuovePorzioni-vecchiePorzioni);
				modifica_ricetta_su_file(ricette[iesimoPasto.ID_Ricetta]);

				//devo modificare l'utilizzo degli alimenti
				//bisogna aggiungere tutte le quantita cancellate
				int i;
				for(i=0;i<NUMERO_MAX_ALIMENTI;i++){
					if(ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i] != -1) {

						//incremento l'utilizzo dell'alimento
						alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i]].Utilizzo+=ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[1][i]*(nuovePorzioni-vecchiePorzioni);

						//decremento la quantita dell'alimento, la funzione lo fa anche su file
						decrementa_quantita_alimento(&alimenti[ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[0][i]],ricette[iesimoPasto.ID_Ricetta].Alimenti_Quantita[1][i]*(nuovePorzioni-vecchiePorzioni));

					}
				}
				return 1;
			}
		}else return 2;
		return 0;
	}else if(nuovePorzioni > 0){
		//le nuove porzioni sono le stesse di prima quindi non devo fare niente
		return 1;
	}else {
		//le porzioni inserite sono negative
		return 0;
	}
}







/**
 * Funzione che effettua tutti i controlli e modifica un pasto
 * consumato nel passato nel caso in cui la modifica riguarda
 * il cambio totale del pasto.
 *
 * @pre indicePasto deve essere un indice di pasto valido.
 */
int cambio_pasto(int indicePasto,alimento alimenti[],ricetta ricette[],int lunghezzaVettoreRicette){

	pasto pastoDaModificare = leggi_iesimo_pasto(indicePasto);
	char scelta[LUNGHEZZA_STRINGA];
	int indiceNuovaRicetta=-1;

	printf("\nInserisci il nome della ricetta che si e' consumati al posto di \"%s\": ",ricette[pastoDaModificare.ID_Ricetta].Nome);
	fgets(scelta,LUNGHEZZA_STRINGA,stdin);

	if((indiceNuovaRicetta = get_ricetta(ricette,lunghezzaVettoreRicette,scelta,true)) == -1){
		printf("\nLa ricetta non esiste!\n");
		return 0;
	}else{
		int porzioniNuovaRicetta = fai_scelta("\nInserisci il numero di porzioni che hai consumato per quella ricetta:");

		//devo azzerare il pasto di prima sia nel file di pasti che nei vettori di alimenti
		//una volta reinserite le quantita del pasto negli alimenti devo azzerare il pasto su file
		//modifica_porzioni_pasto andra a buon fine perhche le nuove porzioni sono 0 cioe minori
		//delle vecchie porzioni che sono almeno 1.
		if(modifica_porzioni_pasto(indicePasto,alimenti,ricette,0) == 1){

			if(is_possible_add_porzioni_pasto(indiceNuovaRicetta,porzioniNuovaRicetta,ricette, alimenti,pastoDaModificare.Data_Ora) == true){
				//consumo il pasto al posto di quello di prima e con quella data
				pastoDaModificare.ID_Ricetta = indiceNuovaRicetta;
				pastoDaModificare.Porzioni = porzioniNuovaRicetta;

				//ho modificato il pasto sul file
				if(modifica_iesimo_pasto_su_file(pastoDaModificare,indicePasto) == 1){

					//ora devo modificare le quantita degli alimenti
					if(modifica_porzioni_pasto(indicePasto,alimenti,ricette,porzioniNuovaRicetta*2) == 1){
						if(modifica_iesimo_pasto_su_file(pastoDaModificare,indicePasto) == 1){
							return 1;
						}
					}
				}
			}else{
				//se non e' possibile mettere quel pasto al posto di quello vecchio devo ripristinare le vecchie quantita
				//sia su file dello storico pasti che su quello degli alimenti e delle ricette
				if(modifica_porzioni_pasto(indicePasto,alimenti,ricette,pastoDaModificare.Porzioni) == 1){
					return 0;
				}
			}
		}
	}
	return 0;
}







/**
 * Funzione che gestisce tutto quello che riguarda la modifica
 * di un pasto consumato nel passato quindi la richiesta delle informazioni
 * in input e i richiami delle adeguate funzioni per i controlli e per
 * l'effettiva modifica.
 *
 */
int modifica_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[]){

	data_ora dataPasto,dataOdierna;
	FILE *file_Storico_Pasti;
	pasto past;
	int indice=0;
	int lunghezzaVettoreIndici=get_lunghezza_file_storico_pasti();
	int indiciSuFile[lunghezzaVettoreIndici];
	int indiceVetIndici=0;

	printf("\nModifica Pasto\n\%s\n",STRINGASTERISCHI);

	do{
		indice=0;
		get_data_pointer(&dataOdierna);
		get_data_input(&dataPasto.Giorno,&dataPasto.Mese,&dataPasto.Anno,"\nInserisci la data in cui e' stato consumato il pasto da modificare:");

		//se la distanza tra le 2 date e' maggiore uguale a 0 vuol dire che la
		//data inserita e' uguale o meno recente del giorno odierno
		if(get_distanza_in_giorni(dataPasto,dataOdierna,0) < 0 ) printf("\nData non valida! Reinseriscila!\n");
		else{
			if ((file_Storico_Pasti = fopen("Storico_Pasti.sf", "rb")) == NULL) {
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

				if(indiceVetIndici != 0){
					printf("\n\n");
					int sceltaIndice;
					do{
						sceltaIndice=fai_scelta("\nInserisci il numero corrispondente al pasto che si vuole modificare:");

						if(sceltaIndice>indiceVetIndici) printf("\nIndice non valido! Reinseriscilo!\n");

					}while(sceltaIndice>indiceVetIndici);


					//chiedo che tipo di modifica al pasto vuole effettuare
					printf("\n%s\n",STRINGASTERISCHI);
					int numScelta;
					int returnValore;
					int nuovePorzioni;

					do{
						numScelta= fai_scelta(MENU_MODIFICA_PASTO);

						switch(numScelta){
							case 1:
								//modifica numero porzioni

								nuovePorzioni = fai_scelta("\nInserisci le nuove porzioni consumate per quel pasto: ");

								if((returnValore=modifica_porzioni_pasto(indiciSuFile[sceltaIndice],alimenti,ricette,nuovePorzioni)) == 1){
									printf("\nModifica delle porzioni avvenuta con successo\n");
								}else printf("\n%s\n",(returnValore == 0) ? "Impossibile completare l'operazione! Errore sui file!" : "La modifica che stai tentando di"
										" effettuare non e' consentita in quanto gli alimenti che stai tentando di consumare sono gia stati consumati o\nnella data inserita"
										" non c'era la disponibilita di alimenti per consumare la ricetta.");
								numScelta = 0;

								break;
							case 2:
								//cambio del pasto
								if(cambio_pasto(indiciSuFile[sceltaIndice], alimenti, ricette,lunghezzaVettoreRicette) == 1){
									printf("\nCambio del pasto avvenuto con successo!\n");
								}else printf("\nSi e' verificato un errore nel cambio del pasto!\n");
								numScelta = 0;
								break;
							case 0:
								//annullamento
								break;
							default:
								printf("\nScelta errata!\n");
						}

					}while(numScelta != 0);

					/*if(cancella_iesimo_pasto_da_file(indiciSuFile[sceltaIndice],alimenti,ricette)) printf("\nCancellazione del pasto effettuata con successo!\n");
					else printf("\nErrore nella cancellazione del pasto su file!\n");*/
				}else printf("\n\nNella data inserita non sono stati consumati pasti!\n");
			}
		}
	}while(get_distanza_in_giorni(dataPasto,dataOdierna,0) < 0 );

	return 1;
}






/**
 * Funzione che visualizza all'utente un menu per fargli
 * scegliere il tipo di operazione vuole effettuare
 * per quanto riguarda i pasti.
 */
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
			modifica_pasto(ricette,lunghezzaVettoreRicette,alimenti);

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

	return 1;
}

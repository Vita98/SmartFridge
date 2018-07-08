/**
 *  @file 	   Ricerca_Ricette_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Ricerca_Ricette_Tools.h.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include "Tipi_Dato.h"
#include "Alimenti_Tools.h"
#include <string.h>
#include "Data_Tools.h"
#include "Ricette_Tools.h"
#include "Preferiti_Tools.h"
#include "Ordinamenti_Tools.h"





/**
 * Funzione che, dato il vettore di interi e un valore intero come parametro,
 * controlla se il valore intero è presente all'interno del vettore.
 *
 */
boolean is_parametro_ricerca(int vettore[],int lunghezzaVettore,int valore){

	int i;
	for(i=0;i<lunghezzaVettore;i++){
		if(valore == vettore[i]) return true;
	}
	return false;

}





/**
 * Funzione che cerca, tra le ricette, le ricette con tutti gli alimenti
 * passati come parametro nel vettore di ID di alimenti (vettoreIndiciAlimenti).
 * Il matching degli alimenti viene effettuato anche utilizzando le sottostringhe.
 * Gli ID delle ricette trovate vengono memorizzati in un vettore che verra restituito dalla funzione.
 *
 */
int* get_ricette_per_alimenti(alimento alimenti[],int lunghezzaVettoreAlimenti,int vettoreIndiciAlimenti[],int lunghezzaVettoreIndici,ricetta ricette[],int lunghezzaVettoreRicette,int *numeroRicetteTrovate){

	int i,j,k;
	int contatore;
	int IndiciRicetteOK[lunghezzaVettoreRicette];
	int IndiceVettoreRicetteOK=0;

	//for che scorre il vettore di ricette
	for(i=0;i<lunghezzaVettoreRicette;i++){
		contatore=0;
		//for che scorre gli alimenti della ricetta
		for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
			//for che scorre gli alimenti da cercare nella ricetta
			for(k=0;k<lunghezzaVettoreIndici;k++){
				//controllo se l'alimento da cercare e' presente nella ricetta

				//creo i vettori che conterranno le sringhe derivanti l'esplosione dei nomi degli alimenti
				char StringheEsploseAlimentoRicetta[LUNGHEZZA_STRINGA/2][LUNGHEZZA_STRINGA];
				char StringheEsploseAlimento[LUNGHEZZA_STRINGA/2][LUNGHEZZA_STRINGA];

				//esplodo i nomi delle ricette per avere un matching piu accurato
				int quantitaStringaEsplosaAlimentoRicetta=explode_string(alimenti[ricette[i].Alimenti_Quantita[0][j]].Nome,StringheEsploseAlimentoRicetta);
				int quantitaStringaEsplosaAlimento=explode_string(alimenti[vettoreIndiciAlimenti[k]].Nome,StringheEsploseAlimento);


				int f,g;
				boolean flag=false;

				//cicli for che confrontano tutte le stringhe derivanti l'esplosione dei due nomi di alimenti tra di loro
				for(f=0;f<quantitaStringaEsplosaAlimento;f++){

					remove_first_last_space(StringheEsploseAlimento[f],StringheEsploseAlimento[f],LUNGHEZZA_STRINGA);
					to_lower_string(StringheEsploseAlimento[f],StringheEsploseAlimento[f]);

					for(g=0;g<quantitaStringaEsplosaAlimentoRicetta;g++){

						remove_first_last_space(StringheEsploseAlimentoRicetta[g],StringheEsploseAlimentoRicetta[g],LUNGHEZZA_STRINGA);

						to_lower_string(StringheEsploseAlimentoRicetta[g],StringheEsploseAlimentoRicetta[g]);

						if(strcmp(StringheEsploseAlimento[f],StringheEsploseAlimentoRicetta[g]) == 0){
							flag=true;
							contatore++;
							break;
						}

					}
					if(flag==true) break;
				}
			}

			//se il numero di matching effettuati e' uguale al numero di alimenti inseriti dall'utente
			//vuol dire che la ricetta puo essere preparata con quelli ingredienti
			if(contatore==lunghezzaVettoreIndici){
				//salvo l'indice della ricetta nel vettore IndiceRicetteOK
				IndiciRicetteOK[IndiceVettoreRicetteOK]=i;
				IndiceVettoreRicetteOK++;
				break;
			}
		}
	}


	//salvo le ricette trovate nel vettore e passo il suo indirizzo nel punatore
	//passato come parametro che ha la funzionalita anche di valore di ritorno
	int *c=(int*) calloc(IndiceVettoreRicetteOK-1,sizeof(int));
	for(i=0;i<IndiceVettoreRicetteOK;i++){
		c[i]=IndiciRicetteOK[i];
	}
	(*numeroRicetteTrovate)=IndiceVettoreRicetteOK;
	return c;

}






/**
 * Funzione che gestisce tutto quello che riguarda la ricerca delle ricette in base agli
 * alimenti.
 * La funzione chiede in input all'utente gli alimenti con cui fare la ricerca,
 * richiama le opportune funzioni per l'effettiva ricerca e mostra
 * all'utente in console i risultati della ricerca in maniera ordinata per preferiti e frequenza.
 *
 */
int ricerca_ricette_per_alimenti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	boolean flag;

	//creo un vettore che conterra gli indici degli alimenti chiesti all'utente
	int vettoreIndici[lunghezzaVettoreAlimenti];
	int indiceVettoreIndici=0;

	int indice=0,i;
	char alimentoInput[LUNGHEZZA_STRINGA];

	printf("\n\nRicerca delle ricette in base agli alimenti\n%s\n",STRINGASTERISCHI);

	do{
		flag=false;

		printf("Inserisci il nome dell'alimento numero %d:",(indice+1));
		fgets(alimentoInput,LUNGHEZZA_STRINGA,stdin);

		//controllo se l'alimento inserito esiste nel vettore alimenti
		if((vettoreIndici[indiceVettoreIndici++]=get_alimento(alimenti,lunghezzaVettoreAlimenti,alimentoInput,true)) > -1){

			//se esiste nel vettore alimenti controllo se e' gia stato inserito come parametro di ricerca della ricetta
			if(is_parametro_ricerca(vettoreIndici,indiceVettoreIndici-1,vettoreIndici[indiceVettoreIndici-1]) == true){
				printf("\nL'alimento che stai tentando di inserire e' stato gia inserito!\n");
				indiceVettoreIndici--;
			}else indice++;

		}else{
			printf("\nL'alimento che stai tentando di inserire non esiste!\n");
			indiceVettoreIndici--;
		}

		if(fai_scelta_booleana("\nVuoi cercare le ricette con altri alimenti oltre a quelli gia inseriti? ") == true) flag=true;
		else if(indiceVettoreIndici==0) printf("\nDevi inserire almeno un alimento per cercare le ricette!\n");


	}while((flag==true || indiceVettoreIndici==0 ) && indiceVettoreIndici < NUMERO_MAX_ALIMENTI );


	//richiamo la funzione che ricerca tutte le ricette con quei alimenti
	int numeroRicetteTrovate=0;
	int *indiciRicette=get_ricette_per_alimenti(alimenti,lunghezzaVettoreAlimenti,vettoreIndici,indiceVettoreIndici,ricette,lunghezzaVettoreRicette,&numeroRicetteTrovate);

	if(numeroRicetteTrovate == 0) printf("\n\nNon e' possibile preparare nessuna ricetta con gli alimenti inseriti!\n\n");
	else{

		//faccio salire le ricette preferite
		merge_sort_ricette(ricette,0,numeroRicetteTrovate-1,indiciRicette,MODALITA_ORDINAMENTO_PREFERITI);

		printf("\n\nRicette che e' possibile preparare con gli alimenti inseriti:\n");
		printf("%20s | %20s\n","Nome","Kcal per porzione");
		printf("-----------------------------------------------------\n");

		flag=false;

		for(i=0;i<numeroRicetteTrovate;i++){

			//se e' la prima volta che trovo un elemento non preferito, ordino tutto il resto del vettore
			//in base alla frequenza quindi ordino tutti i non preferiti per frequenza
			if(exist_preferito(ricette,&indiciRicette[i]) == false && flag==false){
				merge_sort_ricette(ricette,i,numeroRicetteTrovate-1,indiciRicette,MODALITA_ORDINAMENTO_FREQUENZA);
				flag=true;
			}
			printf("%20s | %18.2f | freq:%d\n",ricette[indiciRicette[i]].Nome,ricette[indiciRicette[i]].Kcal_Porzione,ricette[indiciRicette[i]].Frequenza);
		}
	}


	return 1;
}






/**
 * Funzione che cerca, tra le ricette, quelle che hanno degli alimenti con una scadenza
 * nei prossimi DISTANZA_GIORNI_SCADENZA giorni.
 * Di quelle trovate viene memorizzato il suo ID in un vettore che verra' restituito dalla funzione.
 *
 */
int* get_ricette_in_scadenza(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int *numeroRicetteTrovate){

	//Alloco la memoria per un vettore di interi che conterra gli indici
	//delle eventuali ricette con alimenti in scadenza.
	//Sono costretto ad allocare le stesse posizioni del vettore di ricette in quanto,
	//non sapendo ancora quante ricette in scadenza ci sono, suppongo che siano
	//tutte in scadenza.
	int *vettoreRicetteScadenza = (int*) calloc(lunghezzaVettoreRicette,sizeof(int));


	int indiceVetRicetteScadenza=-1;

	int i,j,k;
	data_ora dataAttuale;
	get_data_pointer(&dataAttuale);
	boolean flag;

	//ciclo che scorre tutte le ricette
	for(i=0;i<lunghezzaVettoreRicette;i++){
		if(ricette[i].Visibilita == true)

		//controllo se la iesima ricetta ha la possibilita di essere preparata
		if(get_numero_porzioni_possibili_ricetta(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,i) > 0){
			flag=false;

			//vettore che scorre gli alimenti della ricetta
			//per ferificare se qualcuno e' in scadenza
			for(j=0;j<NUMERO_MAX_ALIMENTI;j++){
				if(ricette[i].Alimenti_Quantita[1][j] != 0)
				for(k=0;k<LUNGHEZZA_VET_SCADENZE;k++){ //vettore che scorre le date di scadenza dell'alimento
					if(alimenti[ricette[i].Alimenti_Quantita[0][j]].Scadenze[k].Quantita != 0){

						//calcolo la distanza in giorni tra la data di scadenza e la data attuale
						int distanza=get_distanza_in_giorni(dataAttuale,alimenti[ricette[i].Alimenti_Quantita[0][j]].Scadenze[k].Data_Scadenza,0);

						//sa la distanza e' in un range tra 0 e la costante DISTANZA_GIORNI_SCADENZA allora
						//la ricetta e' sicuramente in scadenza
						if(distanza >= 0 && distanza <= DISTANZA_GIORNI_SCADENZA ){
							indiceVetRicetteScadenza++;
							vettoreRicetteScadenza[indiceVetRicetteScadenza]=i;
							flag=true;
							break;
						}
					}
				}

				//se so gia che 1 elemento della ricetta e' in scadenza, non serve continuare a scorrere
				//tutti gli altri alimenti del vettore
				if(flag==true) break;
			}
		}
	}


	//creo un altro vettore, che conterra le ricette in scadenza, del
	//numero esatto di ricette in scadenza in maniera tale da lavorare con un vettore
	//della lunghezza giusta e non con un vettore piu' grande del dovuto
	int *c=(int*) calloc(indiceVetRicetteScadenza+1,sizeof(int));
	for(i=0;i<indiceVetRicetteScadenza+1;i++){
		c[i]=vettoreRicetteScadenza[i];
	}

	//salvo il numero di ricette trovate nel puntatore passato come parametro
	//sommo 1 ad indiceVetRicetteScadenza perche parte da -1
	(*numeroRicetteTrovate)=indiceVetRicetteScadenza+1;

	//ritorno il vettore di ricette con alimenti in scadenza
	return c;

}





/**
 * Funzione che gestisce tutto quello che riguarda il suggerimento delle ricette con alimenti in scadenza
 * e quindi richiama le funzioni per la ricerca effettiva delle ricette e li visualizza
 * all'utente in un determinato ordine.
 * L'ordine di visualizzazione delle ricette e' per preferiti e successivamente per frequenza.
 * In oltre i preferiti vengono gia ordinati anche per frequenza dall'algoritmo di ordinamento.
 *
 */
int suggerimento_ricette_in_scadenza(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti){

	printf("\n\nSuggerimento delle ricette in scadenza\n%s\nLe ricette saranno ordinate prima\nper i preferiti e poi per frequenza\n\n",STRINGASTERISCHI);

	int numeroRicetteInScadenza=0;

	//richiamo la funzione che ricerca le ricette con alimenti in scadenza
	//essa ritorna un vettore di interi con all'interno gli indici delle ricette con alimenti in scadenza
	int *vettoreRicetteScadenza=get_ricette_in_scadenza(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,&numeroRicetteInScadenza);

	//ordino il vettore per preferiti in maniera tala da portare in alto tutti i preferiti
	if(numeroRicetteInScadenza != 0) merge_sort_ricette(ricette,0,numeroRicetteInScadenza-1,vettoreRicetteScadenza,MODALITA_ORDINAMENTO_PREFERITI);

	int i;
	boolean flag=false;

	if(numeroRicetteInScadenza == 0) printf("\nNon ci sono ricette con alimenti in scadenza\n");
	else{
		printf("\nLe ricette che hanno degli alimenti in scadenza sono:\n");
		for(i=0;i<numeroRicetteInScadenza;i++){

			//se e' la prima volta che trovo un elemento non preferito, ordino tutto il resto del vettore
			//in base alla frequenza quindi ordino tutti i non preferiti per frequenza
			if(exist_preferito(ricette,&vettoreRicetteScadenza[i]) == false && flag==false){
				merge_sort_ricette(ricette,i,numeroRicetteInScadenza-1,vettoreRicetteScadenza,MODALITA_ORDINAMENTO_FREQUENZA);
				flag=true;
			}
			printf("%d - %25s \t| Kcal per porzione: %5.2f \t| %s\n", i,
										ricette[vettoreRicetteScadenza[i]].Nome, ricette[vettoreRicetteScadenza[i]].Kcal_Porzione,(exist_preferito(ricette,&vettoreRicetteScadenza[i]) == true)? "PREF":"");
		}
	}

	return 1;
}




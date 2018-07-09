/**
 *  @file 	   Ordinamenti_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Ordinamenti_Tools.h.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#include "Tipi_Dato.h"
#include "Preferiti_Tools.h"






/**
 * Funzione che effettua i confronti e gli scambi per l'ordinamento del vettore di ricette.
 * Questa funzione e' il secondo passo del merge sort delle ricette e viene richiamata
 * dalla funzione merge_sort_ricette().
 *
 */
int merging_ricette(ricetta ricette[], int inizio, int medio, int fine, int index[], int modalitaOrdinamento){

    int i, j, k;

    //calcolo la lunghezza dei due vettori temporanei
    int n1 = medio - inizio + 1;
    int n2 =  fine - medio;

    //creo i due vettori temporanei di destra e di sinistra
    int L[n1];
    int R[n2];

    //copio tutti gli indici del vettore di indici all'interno dei vettori temporanei
    for (i = 0; i < n1; i++) L[i] = index[inizio + i];
    for (j = 0; j < n2; j++) R[j] = index[medio + 1+ j];




    //Applico l'algoritmo principale del merge sort

    i = 0; //Indice iniziale del primo vettore temporaneo
    j = 0; //Indice iniziale del secondo vettore temporaneo
    k = inizio; //Indice di inizio del vettore da ordinare

    if (modalitaOrdinamento == MODALITA_ORDINAMENTO_KCAL_PORZIONE){

    	//ordinamento per kcal
    	while (i < n1 && j < n2){
			if (ricette[L[i]].Kcal_Porzione < ricette[R[j]].Kcal_Porzione){
				index[k] = L[i];
				i++;
			}else{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }else if(modalitaOrdinamento == MODALITA_ORDINAMENTO_FREQUENZA){

    	//ordinamento per frequenza
    	while (i < n1 && j < n2){
			if (ricette[L[i]].Frequenza > ricette[R[j]].Frequenza){
				index[k] = L[i];
				i++;
			}else{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }else if(modalitaOrdinamento == MODALITA_ORDINAMENTO_PREFERITI){

    	//ordinamento per preferiti
    	while (i < n1 && j < n2){

    		//porto in alto i preferiti
			if ((exist_preferito(ricette,&L[i]) == true) && (exist_preferito(ricette,&R[j]) == false)){
				index[k] = L[i];
				i++;
			}else if((exist_preferito(ricette,&L[i]) == true) && (exist_preferito(ricette,&R[j]) == true)){ //tra i preferiti porto in alto quello piu consumato
				if(ricette[L[i]].Frequenza > ricette[R[j]].Frequenza){
					index[k] = L[i];
					i++;
				}else{
					index[k] = R[j];
					j++;
				}
			}else{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }


    //copio gli eventuali elementi rimanenti del vettore temporaneo di sinistra
    while (i < n1){
        index[k] = L[i];
        i++;
        k++;
    }


    //copio gli eventuali elementi rimanenti del vettore temporaneo di destra
    while (j < n2){
        index[k] = R[j];
        j++;
        k++;
    }

    return 1;
}








/**
 * Funzione che effettua il primo passo del merge sort delle ricette cioe' divide il vettore
 * in due parti e su ogni parte prima richiama se stessa e poi applica l'algoritmo di ordinamento
 * cioe' richiama la funzione merging_ricette().
 * I parametri inizio e fine stanno ad indicare gli estremi della partizione del vettore che si sta
 * analizzando all'interno della funzione.
 *
 * @pre inizio deve essere un numero maggiore o uguale a 0.
 * @pre fine deve essere minore o uguale della lunghezza del vettore di alimenti.
 */
int merge_sort_ricette(ricetta ricette[], int inizio, int fine,int index[], int modalitaOrdinamento){

    if (inizio < fine)
    {
        //trovo la posizione media del vettore
        int m = inizio+(fine-inizio)/2;

        //richiama se stessa per la ulteriore suddivisione delle 2 meta
        //in ulteriori partizioni.
        merge_sort_ricette(ricette, inizio, m,index,modalitaOrdinamento);
        merge_sort_ricette(ricette, m+1, fine,index,modalitaOrdinamento);

        //eseguo l'ordinamento sulla partizione presa in considerazione
        //in basi agli attuali valori di inizio e fine.
        merging_ricette(ricette, inizio, m, fine,index,modalitaOrdinamento);
    }
    return 1;
}




/**
 * Funzione di facciata per poter applicare il merge sort sulle ricette.
 * Questa funzione riempie il vettore di indici con gli ID delle ricette e
 * richiama le funzioni di ordinamento delle ricette in maniera
 * tale da ordinare il vettore di ricette ordinando gli indici
 * all'interno del vettore index[].
 * Il tipo di ordinamento (per kcal,frequenza,preferiti) viene determinato
 * dal valore del parametro modalitaOrdinamento che deve essere una costante
 * tra quelle dichiarate (MODALITA_ORDINAMENTO_KCAL_PORZIONE,MODALITA_ORDINAMENTO_FREQUENZA
 * MODALITA_ORDINAMENTO_PREFERITI).
 *
 * MODALITA_ORDINAMENTO_KCAL_PORZIONE = Ordinamento per kcal (dal meno calorico al piu' calorico).
 * MODALITA_ORDINAMENTO_FREQUENZA = Ordinamento per frequenza (dal piu' usato al meno usato).
 * MODALITA_ORDINAMENTO_PREFERITI = Ordinamento per preferiti cioe' vengono portati in alto
 * i preferiti e nello stesso tempo i preferiti vengono ordinati per frequenza d'uso.
 *
 * @warning assicurarsi che il parametro modalitaOrdinamento sia una tra le costanti elencate
 * altrimenti non verra applicato nessun ordinamento.
 */
int sort_ricette (ricetta ricette[],int index[], int lunghezzaVettoreRicette, int modalitaOrdinamento){

	int i;
	for (i=0;i<lunghezzaVettoreRicette;i++){
		index[i] = ricette[i].ID_Ricetta;
	}

	merge_sort_ricette(ricette,0,lunghezzaVettoreRicette-1,index,modalitaOrdinamento);
	return 1;
}











/**
 * Funzione che effettua i confronti e gli scambi per l'ordinamento del vettore di alimenti.
 * Questa funzione e' il secondo passo del merge sort degli alimenti e viene richiamata
 * dalla funzione merge_sort_ricette().
 *
 */
int merging_alimenti(alimento alimenti[], int inizio, int medio, int fine, int index[], int modalitaOrdinamento){

    int i, j, k;

    //calcolo la lunghezza dei due vettori temporanei
    int n1 = medio - inizio + 1;
    int n2 =  fine - medio;

    //creo i due vettori temporanei di destra e di sinistra
    int L[n1], R[n2];

    //copio tutti gli indici del vettore di indici all'interno dei vettori temporanei
    for (i = 0; i < n1; i++) L[i] = index[inizio + i];
    for (j = 0; j < n2; j++) R[j] = index[medio + 1+ j];




    //Applico l'algoritmo principale del merge sort

    i = 0; //Indice iniziale del primo vettore temporaneo
    j = 0; //Indice iniziale del secondo vettore temporaneo
    k = inizio; //Indice di inizio del vettore da ordinare

    if (modalitaOrdinamento == MODALITA_ORDINAMENTO_KCAL_PORZIONE){

    	//ordinamento per kcal
    	while (i < n1 && j < n2){
			if (alimenti[L[i]].Kcal_Pezzo < alimenti[R[j]].Kcal_Pezzo){
				index[k] = L[i];
				i++;
			}else{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }else if(modalitaOrdinamento == MODALITA_ORDINAMENTO_FREQUENZA){

    	//ordinamento per frequenza
    	while (i < n1 && j < n2){
			if (alimenti[L[i]].Utilizzo > alimenti[R[j]].Utilizzo){
				index[k] = L[i];
				i++;
			}else{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }


    //copio gli eventuali elementi rimanenti del vettore temporaneo di sinistra
    while (i < n1){
        index[k] = L[i];
        i++;
        k++;
    }


    //copio gli eventuali elementi rimanenti del vettore temporaneo di destra
    while (j < n2){
        index[k] = R[j];
        j++;
        k++;
    }

    return 1;
}






/**
 * Funzione che effettua il primo passo del merge sort degli alimenti cioe' divide il vettore
 * in due parti e su ogni parte prima richiama se stessa e poi applica l'algoritmo di ordinamento
 * cioe' richiama la funzione merging_alimenti().
 * I parametri inizio e fine stanno ad indicare gli estremi della partizione del vettore che si sta
 * analizzando all'interno della funzione.
 *
 * @pre inizio deve essere un numero maggiore o uguale a 0.
 * @pre fine deve essere minore o uguale della lunghezza del vettore di alimenti.
 */
int merge_sort_alimenti(alimento alimenti[], int inizio, int fine,int index[], int modalitaOrdinamento){

    if (inizio < fine){

    	//trovo la posizione media del vettore
        int m = inizio+(fine-inizio)/2;

        //richiama se stessa per la ulteriore suddivisione delle 2 meta
        //in ulteriori partizioni.
        merge_sort_alimenti(alimenti, inizio, m,index,modalitaOrdinamento);
        merge_sort_alimenti(alimenti, m+1, fine,index,modalitaOrdinamento);

        //eseguo l'ordinamento sulla partizione presa in considerazione
        //in basi agli attuali valori di inizio e fine.
        merging_alimenti(alimenti, inizio, m, fine,index,modalitaOrdinamento);
    }
    return 1;
}






/**
 * Funzione di facciata per poter applicare il merge sort sugli alimenti.
 * Questa funzione riempie il vettore di indici con gli ID degli alimenti e
 * richiama le funzioni di ordinamento degli alimenti in maniera
 * tale da ordinarene il vettore ordinando gli indici
 * all'interno del vettore index[].
 * Il tipo di ordinamento (per kcal o frequenza) viene determinato
 * dal valore del parametro modalitaOrdinamento che deve essere una costante
 * tra quelle dichiarate (MODALITA_ORDINAMENTO_KCAL_PORZIONE,MODALITA_ORDINAMENTO_FREQUENZA
 * MODALITA_ORDINAMENTO_PREFERITI).
 *
 * MODALITA_ORDINAMENTO_KCAL_PORZIONE = Ordinamento per kcal (dal meno calorico al piu' calorico).
 * MODALITA_ORDINAMENTO_FREQUENZA = Ordinamento per frequenza (dal piu' usato al meno usato).
 *
 * @warning assicurarsi che il parametro modalitaOrdinamento sia una tra le costanti elencate
 * altrimenti non verra applicato nessun ordinamento.
 */
int sort_alimenti (alimento alimenti[],int index[], int lunghezzaVettoreAlimenti, int modalitaOrdinamento){

	int i;
	for (i=0;i<lunghezzaVettoreAlimenti;i++){
		index[i] = alimenti[i].ID_Alimento;
	}

	merge_sort_alimenti(alimenti,0,lunghezzaVettoreAlimenti-1,index,modalitaOrdinamento);
	return 1;
}

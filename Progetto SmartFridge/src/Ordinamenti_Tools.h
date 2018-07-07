/**
 *  @file 	   Ordinamenti_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per l'ordinamento delle ricette e degli alimenti.
 *
 *  @details   Le funzioni implementate in questo file effettuano l'ordinamento
 *  		   delle ricette per kcal, frequenza e preferiti mentre gli alimenti
 *  		   per kcal e frequenza.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#ifndef ORDINAMENTI_TOOLS_H_
#define ORDINAMENTI_TOOLS_H_




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
 *
 * @param[in] ricette vettore di ricette che si vuole ordinare.
 * @param[in,out] index vettore di indice che verra effettivamente ordinato.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal,frequenza o preferiti).
 * @return 1 se l'operazione e' andata a buon fine e inoltre il vettore di indici ordinato.
 */
int sort_ricette (ricetta ricette[],int index[], int lunghezzaVettoreRicette, int modalitaOrdinamento);





/**
 * Funzione che effettua il primo passo del merge sort delle ricette cioe' divide il vettore
 * in due parti e su ogni parte prima richiama se stessa e poi applica l'algoritmo di ordinamento
 * cioe' richiama la funzione merging_ricette().
 * I parametri inizio e fine stanno ad indicare gli estremi della partizione del vettore che si sta
 * analizzando all'interno della funzione.
 *
 * @param[in] ricette vettore di ricette che si vuole ordinare.
 * @param[in] inizio posizione di inizio della partizione che si vuole ordinare.
 * @param[in] fine posizione di fine della partizione che si vuole ordinare.
 * @param[in,out] index vettore di indici che verra effettivamente ordinato.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal,frequenza o preferiti).
 * Questo valore viene ereditato dalla funzione sort_ricette().
 * @return 1 se l'operazione e' andata a buon fine.
 */
int merge_sort_ricette(ricetta ricette[], int inizio, int fine,int index[], int modalitaOrdinamento);





/**
 * Funzione che effettua i confronti e gli scambi per l'ordinamento del vettore di ricette.
 * Questa funzione e' il secondo passo del merge sort delle ricette e viene richiamata
 * dalla funzione merge_sort_ricette().
 *
 * @param[in] ricette vettore di ricette che si vuole ordinare.
 * @param[in] inizio posizione di inizio della partizione che si vuole ordinare.
 * @param[in] medio posizione media del vettore di riferimento.
 * @param[in] fine posizione di fine della partizione che si vuole ordinare.
 * @param[in,out] index vettore di indici che verra effettivamente ordinato.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal,frequenza o preferiti).
 * Questo valore viene ereditato dalla funzione merge_sort_ricette().
 * @return 1 se l'operazione e' andata a buon fine.
 */
int merging_ricette(ricetta ricette[], int inizio, int medio, int fine, int index[], int modalitaOrdinamento);








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
 *
 * @param[in] alimenti vettore di alimenti che si vuole ordinare.
 * @param[in,out] index vettore di indice che verra effettivamente ordinato.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal o frequenza).
 * @return 1 se l'operazione e' andata a buon fine e inoltre il vettore di indici ordinato.
 */
int sort_alimenti (alimento alimenti[],int index[], int lunghezzaVettoreAlimenti, int modalita);





/**
 * Funzione che effettua il primo passo del merge sort degli alimenti cioe' divide il vettore
 * in due parti e su ogni parte prima richiama se stessa e poi applica l'algoritmo di ordinamento
 * cioe' richiama la funzione merging_alimenti().
 * I parametri inizio e fine stanno ad indicare gli estremi della partizione del vettore che si sta
 * analizzando all'interno della funzione.
 *
 * @param[in] alimenti vettore di alimenti che si vuole ordinare.
 * @param[in] inizio posizione di inizio della partizione che si vuole ordinare.
 * @param[in] fine posizione di fine della partizione che si vuole ordinare.
 * @param[in,out] index vettore di indici che verra effettivamente ordinato.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal o frequenza).
 * Questo valore viene ereditato dalla funzione sort_alimenti().
 * @return 1 se l'operazione e' andata a buon fine.
 */
int merge_sort_alimenti(alimento alimenti[], int inizio, int fine,int index[], int modalitaOrdinamento);





/**
 * Funzione che effettua i confronti e gli scambi per l'ordinamento del vettore di alimenti.
 * Questa funzione e' il secondo passo del merge sort degli alimenti e viene richiamata
 * dalla funzione merge_sort_ricette().
 *
 * @param[in] alimenti vettore di alimenti che si vuole ordinare.
 * @param[in] inizio posizione di inizio della partizione che si vuole ordinare.
 * @param[in] medio posizione media del vettore di riferimento.
 * @param[in] fine posizione di fine della partizione che si vuole ordinare.
 * @param[in,out] index vettore di indici che verra effettivamente ordinato.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal o frequenza).
 * Questo valore viene ereditato dalla funzione merge_sort_alimenti().
 * @return 1 se l'operazione e' andata a buon fine.
 */
int merging_alimenti(alimento alimenti[], int inizio, int medio, int fine, int index[], int modalitaOrdinamento);


#endif /* ORDINAMENTI_TOOLS_H_ */

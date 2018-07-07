/**
 *  @file 	   Ricerca_Ricette_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la ricerca delle ricette in scadenza e in base agli alimenti.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#ifndef RICERCA_RICETTE_TOOLS_H_
#define RICERCA_RICETTE_TOOLS_H_







/**
 * Funzione che gestisce tutto quello che riguarda la ricerca delle ricette in base agli
 * alimenti.
 * La funzione chiede in input all'utente gli alimenti con cui fare la ricerca,
 * richiama le opportune funzioni per l'effettiva ricerca e mostra
 * all'utente in console i risultati della ricerca in maniera ordinata per preferiti e frequenza.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la funzione e' andata a buon fine.
 */
int ricerca_ricette_per_alimenti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che, dato il vettore di interi e un valore intero come parametro,
 * controlla se il valore intero è presente all'interno del vettore.
 *
 * @param[in] vettore vettore di interi in cui si vuole cercare il valore intero.
 * @param[in] lunghezzaVettore lunghezza del vettore di interi.
 * @param[in] valore valore che si vuole cercare all'interno del vettore.
 * @return true se la ricerca ha trovato una carrispondenza, false altrimenti.
 */
boolean is_parametro_ricerca(int vettore[],int lunghezzaVettore,int valore);





/**
 * Funzione che cerca, tra le ricette, le ricette con tutti gli alimenti
 * passati come parametro nel vettore di ID di alimenti (vettoreIndiciAlimenti).
 * Il matching degli alimenti viene effettuato anche utilizzando le sottostringhe.
 * Gli ID delle ricette trovate vengono memorizzati in un vettore che verra restituito dalla funzione.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param[in] vettoreIndiciAlimenti vettore che contiene gli ID degli alimenti con cui cercare le ricette.
 * @param[in] lunghezzaVettoreIndici lunghezza del vettore degli ID degli alimenti con cui cercare le ricette.
 * @param[in,out] numeroRicetteTrovate puntatore ad una locazione di memoria in cui viene
 * memorizzato il numero di ricette risultanti la ricerca.
 *
 * @return puntatore ad un vettore di interi con all'interno gli indici delle ricette ricsultanti la ricerca
 * per alimenti.
 */
int* get_ricette_per_alimenti(alimento alimenti[],int lunghezzaVettoreAlimenti,int vettoreIndiciAlimenti[],int lunghezzaVettoreIndici,ricetta ricette[],int lunghezzaVettoreRicette,int *numeroRicetteTrovate);





/**
 * Funzione che gestisce tutto quello che riguarda il suggerimento delle ricette con alimenti in scadenza
 * e quindi richiama le funzioni per la ricerca effettiva delle ricette e li visualizza
 * all'utente in un determinato ordine.
 * L'ordine di visualizzazione delle ricette e' per preferiti e successivamente per frequenza.
 * In oltre i preferiti vengono gia ordinati anche per frequenza dall'algoritmo di ordinamento.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la funzione e' andata a buon fine.
 */
int suggerimento_ricette_in_scadenza(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che cerca, tra le ricette, quelle che hanno degli alimenti con una scadenza
 * nei prossimi DISTANZA_GIORNI_SCADENZA giorni.
 * Di quelle trovate viene memorizzato il suo ID in un vettore che verra' restituito dalla funzione.
 *
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param[in,out] numeroRicetteTrovate numero trovato di ricette con alimenti in scadenza.
 * @return puntatore ad un vettore di interi con all'interno gli indici delle ricette con alimenti in scadenza.
 */
int* get_ricette_in_scadenza(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int *numeroRicetteTrovate);

#endif /* RICERCA_RICETTE_TOOLS_H_ */

/**
 *  @file 	   Lista_Spesa_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per gestione della lista della spesa.
 *
 *  @details   File contenente tutti i prototipi delle funzioni
 *  		   per la generazione della lista della spesa, per la visualizzazione della precedente
 *  		   e della modifica della quantità minima degli alimenti.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */

#ifndef LISTA_SPESA_TOOLS_H_
#define LISTA_SPESA_TOOLS_H_




/**
 * Dato il vettore di alimenti, la funzione leggera tutti gli alimenti
 * presenti in frigo e scrivera' sul file (Lista_Spesa.sf)
 * le informazioni relative a quelli aventi una quantita'
 * inferiore alla soglia minima stabilta.
 *
 * @param[in] alimenti vettore dove sono memorizzati gli alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 *
 * @return 1 se la lista e' stata generata correttamente.
 */
int genera_lista_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti);








/**
 * Funzione che legge il file (Lista_Spesa.sf) e visualizza l'ultima lista generata, se presente.
 *
 * @param[in] alimenti vettore dove sono memorizzati gli alimenti.
 *
 * @return 1 se la visualizzazione e' andata a buon fine.
 */
int visualizza_lista_spesa(alimento alimenti[]);







/**
 * Funzione che permette di modificare la quantità minima degli alimenti
 * in base alla quale viene generata la lista, e salvarla sul file di configurazione (Config.txt).
 *
 *
 * @return 1 se la modifica è andata a buon fine.
 */
int modifica_soglia_spesa();








/**
 * Funzione che gestisce il menu riguardante tutte le opzioni
 * relative alla lsta della spesa.
 * Chiede all'utente di fare una scelta e richiama le opportune funzioni
 * per svolgere quel determinato compito.
 *
 * @param[in] alimenti vettore dove dove sono memorizzati gli alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 *
 * @return 1 se l'operazione e' andata a buon fine.
 */
int scelte_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti);





#endif /* LISTA_SPESA_TOOLS_H_ */

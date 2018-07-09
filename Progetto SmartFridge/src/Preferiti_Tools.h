/**
 *  @file 	   Preferiti_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per gestione delle ricette preferite.
 *
 *  @details   File contenente tutti i prototipi delle funzioni
 *  		   per l'aggiunta, la visualizzazione, la cancellazione di un preferito
 *  		   e controlli sulla loro pre-esistenza.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */

#ifndef PREFERITI_TOOLS_H_
#define PREFERITI_TOOLS_H_




/**
 * Dato il vettore di ricette, la funzione apre il file di ricette preferite(Preferiti.sf)
 * e controlla se la ricetta inserita sia presente al suo interno.
 *
 * @param[in] ricette vettore dove sono memorizzate le ricette.
 * @param[in,out] indiceRicetta puntatore a una locazione di memoria che contiene l'indice della ricetta da cercare
 *
 * @return true se la ricetta e' presente, false se non esiste il file (o
 * se e' vuoto) o se la ricetta non e' presente.
 */
boolean exist_preferito(ricetta ricette[], int* indiceRicetta);







/**
 * Dato il vettore di ricette, la funzione controlla se la ricetta inserita sia esistenze
 * e presente all'interno dei preferiti.
 *
 * @param[in] ricette vettore dove dove sono memorizzate le ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] scelta stringa contenente il nome di una ricetta.
 * @param[in,out] indiceRicetta puntatore a una locazione di memoria che conterra' l'indice della ricetta inserita.
 *
 *
 * @return true se la ricetta inserita esiste ed e' presente tra i preferiti, false altrimenti
 */
boolean controllo_preferiti(ricetta ricette[], int lunghezzaVettoreRicette, char scelta[], int* indiceRicetta);








/**
 * Data la ricetta inserita da tastier, la funzione lo aggiunge in coda
 * al file dei preferiti una volta controllato se non e' gia' presente.
 *
 * @param[in] ricette vettore dove dove sono memorizzate le ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 *
 * @return 1 se l'aggiunta e' andata a buon fine, 0 altrimenti.
 */
int aggiungi_preferito(ricetta ricette[], int lunghezzaVettoreRicette);





/**
 * Data la ricetta passata come parametro, la funzione lo cancella dal
 * file dei preferiti una volta controllato se e' presente.
 *
 * @param[in] ricette vettore dove dove sono memorizzate le ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 *
 * @return 1 se la cancellazione e' andata a buon fine, 0 altrimenti.
 */
int cancella_preferito(ricetta ricette[], int lunghezzaVettoreRicette);








/**
 * Funzione che permette di visualizzare tutte le ricette preferite
 * nell'ordine in cui sono state inserite.
 *
 * @param[in] ricette vettore dove dove sono memorizzate le ricette.
 *
 * @return 1 se la visualizzazione e' andata a buon fine.
 */
int visualizza_preferiti(ricetta ricette[]);




/**
 * Funzione che gestisce il menu riguardante tutte le opzioni
 * relative alle ricette preferite.
 * Chiede all'utente di fare una scelta e richiama le opportune funzioni
 * per svolgere quel determinato compito.
 *
 * @param[in] ricette vettore dove dove sono memorizzate le ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 *
 * @return 1 se l'operazione e' andata a buon fine.
 */
int scelta_opzioni_preferiti(ricetta ricette[], int lunghezzaVettoreRicette);



#endif /* PREFERITI_TOOLS_H_ */

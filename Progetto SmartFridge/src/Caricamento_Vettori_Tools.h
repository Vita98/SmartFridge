/**
 *  @file 	   Caricamento_Vettori_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per il caricamento in memoria dei file.
 *
 *  @details   File contenente tutti i prototipi delle funzioni
 *  		   per il caricamento in memoria delle ricette, alimenti e del file
 *  		   di configurazione e per la lettura del numero di alimenti,ricette e pasti.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#ifndef CARICAMENTO_VETTORI_TOOLS_H_
#define CARICAMENTO_VETTORI_TOOLS_H_




/**
 * Funzione che gestisce il file di configurazione(Config.txt): lo apre,se esiste, e carica
 * le impostazioni.
 * Se non esiste lo crea e imposta la configurazione predefinita.
 *
 * @return 1 se tutto e' andato a buon fine.
 */
int carica_configurazione();





/**
 * Dato il vettore di alimenti, la funzione apre il file di alimenti(Alimenti.sf)
 * e carica tutti gli alimenti dal file al vettore.
 *
 * @param[in,out] alimenti vettore dove vengono messi gli alimenti letti dal file.
 * @return 1 se il caricamento e' andato a buon fine, 0 se non esiste il file o
 * se e' vuoto.
 */
int carica_alimenti(alimento alimenti[]);





/**
 * La funzione apre il file di alimenti(Alimenti.sf) per calcolare
 * il numero di alimenti che ne sono stati memorizzati all'interno.
 *
 * @return il numero di alimenti memorizzati all'interno del file Alimenti.sf.
 */
int get_lunghezza_file_alimenti();





/**
 * Dato il vettore di ricette come parametro, la funzione apre il file di ricette(Ricette.sf)
 * e carica tutte le ricette dal file al vettore.
 *
 * @param[in,out] ricette vettore dove vengono messe le ricette lette dal file.
 * @return 1 se il caricamento e' andato a buon fine, 0 se non esiste il file o
* se e' vuoto.
 */
int carica_ricette(ricetta ricette[]);





/**
 * La funzione apre il file di ricette(Ricette.sf) per calcolare
 * il numero di ricette che ne sono stati memorizzati all'interno.
 *
 * @return il numero di ricette memorizzati all'interno del file Ricette.sf.
 */
int get_lunghezza_file_ricette();





/**
 * La funzione apre il file di pasti(Storico_Pasti.sf) per calcolare
 * il numero di pasti che ne sono stati memorizzati all'interno.
 *
 * @return il numero di pasti memorizzati all'interno del file Storico_Pasti.sf.
 */
int get_lunghezza_file_storico_pasti();



#endif /* CARICAMENTO_VETTORI_TOOLS_H_ */

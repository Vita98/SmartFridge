/**
 *  @file      Spesa_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la visualizzazione e l'aggiunta della spesa.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#ifndef SPESA_TOOLS_H_
#define SPESA_TOOLS_H_





/**
 * Funzione che gestisce il menu relativo alla spesa cioe' chiede in
 * input all'utente di fare una scelta, di controllare se sia valida,
 * e di eseguire le relative funzioni in base alla scelta fatta.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore alimenti.
 * @param[in,out] nuovoIndirizzoAlimenti nuovo indirizzo del vettore di alimenti
 * nel caso in cui viene comprato un alimento non conosciuto.
 * @return la nuova lunghezza del vettore di alimenti.
 */
int scelta_opzioni_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoAlimenti) ;





/**
 * Funzione che si occupa di tutto quello che riguarda l'aggiunta dei
 * nuovi alimenti comprati,inserendoli sia all'inerno del vettore che del file Storico_Spesa.sf.
 * Essa chiede tutti i dati dell'acquisto all'utente e richiama le relative funzioni per salvare
 * i dati su file.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore alimenti.
 * @param[in,out] nuovoIndirizzoAlimenti nuovo indirizzo del vettore di alimenti
 * nel caso in cui viene comprato un alimento non conosciuto.
 * @return la nuova lunghezza del vettore di alimenti.
 */
int inserimento_alimenti_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoAlimenti);





/**
 * Funzione che memorizza la spesa fatta all'interno del file Storico_Spesa.sf
 * che contiene lo storico di tutte le spese in ordine cronologico.
 *
 * @param[in] indiceAlimento Identificativo dell'alimento che e' stato acquistato nella spesa.
 * @param[in] quantita Quantita' di alimento acquistato per questa spesa.
 * @return 1 se la memorizzazione e' andata a buon fine, 0 altrimenti.
 */
int memorizza_in_storico_spesa(int indiceAlimento,int quantita);





/**
 * Funzione che visualizza in output all'utente, una tabella con la lista
 * di tutte le spese effettuate dalla prima accensione dello smart fridge.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la visualizzazione e' andata a buon fine, 0 altrimenti.
 */
int visualizza_storico_spesa(alimento alimenti[],int lunghezzaVettoreAlimenti);


#endif /* SPESA_TOOLS_H_ */

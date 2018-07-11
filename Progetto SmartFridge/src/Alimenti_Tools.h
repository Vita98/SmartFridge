/**
 *  @file Alimenti_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la gestione di tutto quello che riguarda gli alimenti.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */



#ifndef ALIMENTI_TOOLS_H_
#define ALIMENTI_TOOLS_H_



/**
 * Data il nome della ricetta come parametro, la funzione verifice
 * se esiste una ricetta con quel nome nel vettore di alimenti anche esso
 * passato come parametri.
 * Se il parametro visibilita e' true la funzione ricerchera la ricetta
 * tra tutti gli alimenti disponibili altrimenti se e' false, la ricerca
 * verra effettuata anche tra gli alimenti cancellati o non disponibili.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param parametriRicerca nome della ricetta che si vuole cercare.
 * @param visibilita modalita di ricerca.
 * @return -1 se non viene trovata nessuna occorrenza, altrimenti la
 * posizione della prima occorrenza.
 */
int get_alimento(alimento alimenti[], int lunghezzaVettoreAlimenti,char parametriRicerca[],boolean visibilita);





/**
 * Funzione che gestisce il menu riguardante tutte le opzioni
 * relative agli alimenti.
 * Chiede all'utente di fare una scelta e richiama le opportune funzioni
 * per svolgere quel determinato compito.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se l'operazione e' andata a buon fine.
 */
int scelta_opzioni_alimenti(alimento alimenti[], int lunghezzaVettoreAlimenti);





/**
 * Funzione che ha il compito di visualizzare in console, in una determinata formattazione,
 * le informazioni riguardanti gli alimenti presenti nello smart fridge.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se e' stato visualizzato almeno 1 alimento, 0 altrimenti.
 */
int visualizza_alimenti(alimento alimenti[], int lunghezzaVettoreAlimenti);





/**
 * Funzione che gestisce tutte le operazioni per la modifica di un alimento.
 * Chiede all'utente l'alimento da modificare e che tipo di modifica fare
 * per poi richiamare le funzioni rispettive per effettuare la modifica.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se e' andato tutto bene.
 */
int modifica_alimento(alimento alimenti[], int lunghezzaVettoreAlimenti) ;





/**
 * Dato l'alimento come parametro, la funzione calcola la quantita
 * di alimento presente all'interno dello smart fridge.
 *
 * @param[in] alim alimento di cui si vuole calcolare la quantita.
 * @return la quantita totale di alimento disponibile indipendentemente
 * dalle varie scadenze dell'alimento.
 */
int get_quantita (alimento alim);





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica del nome di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param indiceAlimento indice dell'alimento di cui si vuole modificare il nome.
 * @return 1 se e' andato tutto bene, 0 altrimenti.
 */
int modifica_nome_alimento(alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceAlimento);





/**
 * Dato l'alimento passato come parametro, la funzione lo sovrascrive
 * alla sua vecchia versione all'interno del file.
 * Viene utilizzato per far riflettere le modifiche dal vettore
 * al file.
 *
 * @param[in] alim alimento che si vuole sovrascrivere su file.
 * @return 1 se la modifica e' andata a buon fine, 0 altrimenti.
 */
int modifica_alimento_su_file(alimento alim);






/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica delle kcal di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] indiceAlimento indice dell'alimento di cui si vogliono modificare le kcal.
 * @return 1 se e' andato tutto bene, 0 altrimenti.
 */
int modifica_kcal_alimento(alimento alimenti[],int indiceAlimento);





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica del peso di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] indiceAlimento indice dell'alimento di cui si vuole modificare il peso.
 * @return 1 se e' andato tutto bene, 0 altrimenti.
 */
int modifica_peso_alimento(alimento alimenti[],int indiceAlimento);





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica della quantita di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] indiceAlimento indice dell'alimento di cui si vuole modificare la quantita.
 * @return 1 se e' andato tutto bene, 0 altrimenti.
 */
int modifica_quantita_alimento(alimento alimenti[],int indiceAlimento);





/**
 * Funzione specifica che si occupa di tutto quello che riguarda
 * la modifica delle scadenze di un alimento di cui viene passato l'indice
 * all'interno del vettore di alimenti.
 * Si accupa della richiesta delle nuove informazioni all'utente
 * e degli opportuni controlli.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] indiceAlimento indice dell'alimento di cui si vuole modificare le scadenze.
 * @return 1 se e' andato tutto bene, 0 altrimenti.
 */
int modifica_scadenze_alimento(alimento alimenti[],int indiceAlimento);





/**
 * Dato l'indice di un alimento come parametro, la funzione visualizza in console
 * tutto il vettore di scadenze, con le relative quantita e date di scadenza.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] indiceAlimento indice dell'alimento di cui si vuole visualizzare il vettore di scadenze.
 * @return 1 se la visualizzazione e' andata a buon fine.
 */
int visualizza_quantita_scadenze(alimento alimenti[],int indiceAlimento);





/**
 * Dato l'alimento e la data , passati come parametro, la funzione verifica
 * se la data e' una data di scadenza dell'alimento presente nello
 * smart fridge.
 *
 * @param[in] alim alimento di cui si vuole controllare se esiste la data di scadenza.
 * @param[in] data data di cui si vuole verificarne l'esistenza.
 * @return -1 se non viene trovata nessuna corrispondenza, altrimenti ritorna
 * la posizione della prima occorrenza.
 */
int get_data_scadenza(alimento alim,data_ora data);





/**
 * Dato l'alimento passato come parametro, la funzione lo aggiunge in coda
 * al file di alimenti.
 *
 * @param[in] alim alimento che si vuole aggiungere su file.
 * @return 1 se l'aggiunta e' andata a buon fine, 0 altrimenti.
 */
int aggiungi_alimento_su_file(alimento alim);





/**
 * Funzione che ha il compito di sottrarre alle quantita del vettore
 * di scadenze di un alimento,passato come parametro, una quantita
 * anchessa passata come parametro.
 * Viene usata quando viene consumato un pasto e bisogna sottrarre
 * le quantita consumate a quelle disponibili.
 *
 * @param[in,out] alim alimento da cui si vuole diminuire la quantita.
 * @param[in] quantita quantita che si vuole andare a sottrarre all'alimento.
 * @return 1 se la modifica e' stata effettuata, 0 altrimenti;
 */
int decrementa_quantita_alimento(alimento* alim, int quantita);





/**
 * Funzione che gestisce tutte le operazioni di ordinamento del vettore di alimenti.
 * La funzione chiede all'utente in che modalita di ordinamento si vuole
 * visualizzare il vettore e richiama le opportune funzioni.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se l'operazione e' andata a buon fine.
 */
int scelta_visualizzazione_alimenti(alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che ha il compito di richiamare l'algoritmo di ordinamento
 * secondo la modalita di ordinamento passata come parametro
 * e, successivamente, di visualizzare tutti gli alimenti ordinati.
 *
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param modalitaOrdinamento numero che identifica la modalita di ordinamento.
 * @return 1 se e' stato visualizzato almeno 1 alimento, 0 altrimenti.
 */
int visualizza_alimenti_ordinati(alimento alimenti[],int lunghezzaVettoreAlimenti, int modalitaOrdinamento);


#endif /* ALIMENTI_TOOLS_H_ */

/**
 *  @file Pasti_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la gestione dei pasti.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */



#ifndef PASTI_TOOLS_H_
#define PASTI_TOOLS_H_





/**
 * Funzione che visualizza all'utente un menu per fargli
 * scegliere il tipo di operazione vuole effettuare
 * per quanto riguarda i pasti.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezze del vettore di alimenti.
 * @return 1 se tutto e' andato a buon fine, 0 altrimenti.
 */
int scelta_opzioni_pasti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti);




/**
 * Funzione che gestisce tutte le operazioni per la consumazione di un pasto.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return ritorna 1 se la funzione e' andata a buon fine.
 */
int aggiungi_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che aggiunge un pasto, con gli attributi passati come
 * parametro, in coda sul file dei pasti.
 * Se il file Storico_Pasti.sf non esiste la funzione lo crea.
 *
 * @param[in] numPorzioni Numero di porzioni del pasto consumato.
 * @param[in] idRicetta   Id della ricetta che e' stata consumata.
 * @return 1 se la funzione e'riuscita ad aprire il file e ad effettuare
 * l'aggiunta, 0 altrimenti.
 */
int aggiungi_pasto_su_file(int numPorzioni,int idRicetta);





/**
 * Funzione che visualizza all'utente un menu per fargli
 * scegliere il tipo di settimana di cui vedere
 * il menu settimanale.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se la funzione e' andata a buon fine.
 */
int scelta_opzioni_visualizza_menu_settimanale(ricetta ricette[],int lunghezzaVettoreRicette);





/**
 * Funzione che gestisce la chiamata della funzione per la visualizzazione
 * del menu setimanale della settimana corrente.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se la funzione e' andata a buon fine.
 */
int visualizza_menu_settimana_in_corso(ricetta ricette[],int lunghezzaVettoreRicette);





/**
 * Funzione che gestisce la chiamata della funzione per la visualizzazione
 * del menu setimanale di settimane passate relativamente a quella corrente.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se la funzione e' andata a buon fine.
 */
int visualizza_menu_settimane_passate(ricetta ricette[],int lunghezzaVettoreRicette);





/**
 * Funzione che stampa all'utente tutti i pasti consumati durante una settimana
 * passata come parametro.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] NumeroSettimana rappresenta quante settimane a ritroso bisogna andare
 * per stampare la settimana richiesta.
 *
 * @param[in] giornoSettimana indica quanti giorni della settimana la funzione deve stampare
 * in quanto se la settimana attuale non e' ancora finita la funzione si deve fermare al
 * giorno attuale invece di continuare per giorni futuri.
 *
 * @return ritorna 1 se la funzione e' andata a buon fine.
 */
int stampa_iesimo_menu_settimanale(ricetta ricette[],int lunghezzaVettoreRicette,int NumeroSettimana,int giornoSettimana);










/**
 * Funzione che gestisce tutte le operazioni per la cencellazione di un pasto.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @return 1 se la funzione e' andata a buon fine,0 altrimenti.
 */
int cancella_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[]);






/**
 * Funzione che effettua la cancellazione di un pasto dal file.
 * Inoltre la funzione si occupa di gestire le modifiche della
 * frequenza delle ricette e della quantita e dell'utilizzo
 * degli alimenti.
 *
 * @param[in] indicePasto indice su file del pasto che si vuole cancellare.
 * @param[in,out] alimenti vettore di alimenti in cui verranno effettuate le
 * modifiche derivanti la cancellazione del pasto.
 *
 * @param[in,out] ricette vettore di ricette in cui verranno effettuate le
 * modifiche derivanti la cancellazione del pasto.
 * @return 1 se la cencellazione su file e le modifiche sono andate a buon fine
 * 0 altrimenti.
 */
int cancella_iesimo_pasto_da_file(int indicePasto,alimento alimenti[],ricetta ricette[]);





/**
 * In base al numero di giorni passato come parametro
 * viene calcolato il numero di settimane a cui
 * corrispondono i giorni passati come parametro.
 *
 * @param[in] giorni numero di giorni.
 * @return il numero di settimane corrispondenti ai giorni
 */
int get_numero_settimane(int giorni);





/**
 * Funzione che gestisce tutto quello che riguarda la modifica
 * di un pasto consumato nel passato quindi la richiesta delle informazioni
 * in input e i richiami delle adeguate funzioni per i controlli e per
 * l'effettiva modifica.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @return 1 se la funzione e'andata a buon fine, 0 altrimenti.
 */
int modifica_pasto(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[]);





/**
 * Passato il pasto come parametro e l'indice su file,
 * la funzione salva il pasto sul file Storico_Pasti.sf
 * nella posizione indicePasto partendo dall ínizio del file.
 *
 * @param[in] iesimoPasto pasto che deve essere memorizzato nel file.
 * @param[in] indicePasto posizione su file in cui va memorizzato il pasto.
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti.
 */
int modifica_iesimo_pasto_su_file(pasto iesimoPasto,int indicePasto);





/**
 * Funzione che effettua tutti i controlli e modifica un pasto
 * consumato nel passato nel caso in cui la modifica riguarda
 * solo le porzioni del pasto.
 *
 * @param[in] indicePasto posizione su file in cui va memorizzato il pasto.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] ricette vettore di ricette.
 * @param[in] nuovePorzioni nuovo numero di porzioni che si volgiono modificare al pasto.
 * @return
 */
int modifica_porzioni_pasto(int indicePasto,alimento alimenti[],ricetta ricette[],int nuovePorzioni);





/**
 * Data la posizione del pasto su file come parametro,
 * la funzione restituisce il pasto letto in quella posizione.
 *
 * @param indicePasto posizione su file in cui leggere il pasto.
 * @return pasto letto nella posizione passata come parametro.
 */
pasto leggi_iesimo_pasto(int indicePasto);





/**
 * In base alla ricetta e al numero di porzioni aggiuntive passate come parametro,
 * la funzione verifica se è possibile aggiungere porzioni ad un pasto
 * consumato nel passato.
 * Principalemente verifica se gli alimenti della ricetta non sono mai stati
 * indisponibili in quanto l'aggiunta del pasto genererebbe una quantita
 * negativa di alimenti.
 *
 * @param[in] indiceRicetta indice della ricetta di cui si volgiono aggiungere porzioni.
 * @param[in] porzioniAggiuntive numero di porzioni aggiuntive.
 * @param[in] ricette vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @return true se e'possibile consumare quelle porzioni, false altrimenti.
 */
boolean is_possible_add_porzioni_pasto(int indiceRicetta,int porzioniAggiuntive,ricetta ricette[],alimento alimenti[]);





/**
 * Funzione che effettua tutti i controlli e modifica un pasto
 * consumato nel passato nel caso in cui la modifica riguarda
 * il cambio totale del pasto.
 *
 * @param[in] indicePasto posizione su file in cui va memorizzato il pasto.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se il cambio e' andato a buon fine, 0 altrimenti.
 */
int cambio_pasto(int indicePasto,alimento alimenti[],ricetta ricette[],int lunghezzaVettoreRicette);


#endif /* PASTI_TOOLS_H_ */

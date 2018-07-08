/**
 *  @file      Ricette_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la gestione di tutto quello che riguarda le ricette.
 *
 *  @details   In particolare le funzioni di questo file permettono l'inserimento, la
 *  		   modifica e la visualizzazione di qualsiasi informazione riguardanti le ricette.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#ifndef RICETTE_TOOLS_H_
#define RICETTE_TOOLS_H_





/**
 * Funzione che gestisce il menu relativo alle opzioni delle ricette cioe'
 * chiede all'utente di fare una scelta di opzione, effettua i controlli
 * e richiama le specifiche funzioni.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore alimenti.
 * @param[in,out] nuovoIndirizzoRicette  nuovo indirizzo del vettore di ricette
 * nel caso in cui viene inserita una nuova ricetta all'interno del sistema.
 * @return la lunghezza del vettore di ricette.
 */
int scelta_opzioni_ricette(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int *nuovoIndirizzoRicette);





/**
 * Funzione utilizzata per visualizzare all'utente, sul terminale, le ricette in maniera ordinata
 * in base al parametro modalitaOrdinamento.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] modalitaOrdinamento tipo di ordinamento che si vuole applicare (per kcal,frequenza o preferiti).
 * Utilizzare le opportune costanti (MODALITA_...).
 * @return 1 se la visualizzazione e' andata a buon fine.
 */
int visualizza_ricette_ordinate(ricetta ricette[], int lunghezzaVettoreRicette, int modalitaOrdinamento);





/**
 * Funzione utilizzata per visualizzare all'utente, sul terminale, le ricette in ordine di lettura
 * dal file quindi senza uno specifico ordinamento.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se la visualizzazione e' andata a buon fine.
 */
int visualizza_ricette(ricetta ricette[], int lunghezzaVettoreRicette);





/**
 * Funzione che gestisce il menu relativo alle opzioni di visualizzazione
 * delle ricette cioe' permette all'utente di decidere in che modo
 * visualizzare ordinatamente le ricette o se visualizzarle senza
 * un ordine specifico.
 * In base alla scelta, la funzione richiama le specifiche funzioni.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se tutto e' andato a buon fine.
 */
int scelta_visualizzazione_ricette(ricetta ricette[],int lunghezzaVettoreRicette);





/**
 * Funzione che si occupa di tutto quello che riguarda la cancellazione di una ricetta
 * cioe' chiede in input la ricetta da cancellare, applica i controlli adeguati
 * e effettua la cancellazione sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @return 1 se la cancellazione e' stata effettuata, 0 altimenti.
 */
int cancella_ricetta(ricetta ricette[],int lunghezzaVettoreRicette);





/**
 * Data la stringa parametriRicerca come parametro, la funzione cerca se esiste
 * una ricetta chiamata in quella maniera all'interno del vettore di ricette.
 * Se il parametro visibilita e' TRUE allora la funzione cerchera la ricetta tra tutte
 * le ricette con attributo visibilita uguale a true altrimenti la ricerchera anche tra
 * le ricette 'cancellate'.
 * Il matching non tiene conto dei caratteri minuscoli e maiuscoli e degli
 * spazi iniziali e finali.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] parametriRicerca stringa da cercare.
 * @param[in] visibilita insieme di ricette in cui cercare la stringa.
 * @return -1 se la ricerca non ha dato risultati, la posizione dalla prima
 * occorrenza altrimenti.
 */
int get_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,char parametriRicerca[],boolean visibilita);





/**
 * Data la ricetta passata come parametro, la funzione la sovrascrive
 * alla sua vecchia versione all'interno del file Ricette.sf.
 * Viene utilizzato per far riflettere le modifiche dal vettore
 * al file.
 *
 * @param[in] rice ricetta che si vuole sovrasrivere su file.
 * @return 1 se la modifica e' andata a buon fine, 0 altrimenti.
 */
int modifica_ricetta_su_file(ricetta rice);





/**
 * Funzione che gestisce il menu che riguarda la scelta del tipo di modifica da effettuare
 * sulla ricetta. La funzione chiede in input la ricetta da modificare, il tipo
 * di modifica da fare , effettua i controlli adeguati e infine richiama le
 * opportune funzioni in base al tipo di modifica.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la funzione e' andata a buon fine.
 */
int scelta_modifica_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che si occupa di tutto quello che riguarda la modifica del nome
 * di una ricetta il cui ID viene passato come parametro.
 * La funzione chiede in input un nuovo nome, controlla se e' un nome valido
 * e non ancora utilizzato e successivamente effettua la modifica sia sul vettore di ricette che
 * sul file Ricette.sf.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param indiceRicetta indice della ricetta di cui si vuole modificare il nome.
 * @return 1 se la modifica e' stata effettuata, 0 altrimenti.
 */
int modifica_nome_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,int indiceRicetta);





/**
 * Funzione che si occupa di tutto quello che riguarda la modifica delle kcal
 * per porzione di una ricetta il cui ID viene passato come parametro.
 * La funzione chiede in input un nuovo valore e successivamente effettua la modifica
 * sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @param[in] ricette vettore di ricette.
 * @param indiceRicetta indice della ricetta di cui si vuole modificare le kcal per porzione.
 * @return 1 se la modfica e' stata effettuata, 0 altrimenti.
 */
int modifica_kcalporzione_ricetta(ricetta ricette[],int indiceRicetta);





/**
 * Funzione che gestisce il menu che riguarda le opzioni di modifica degli
 * alimenti che compongono una ricetta.
 * La funzione chiede di scelgliere che tipo di modifica fare e successivamente
 * richiama le opportune funzioni.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] indiceRicetta
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la funzione e' andata a buon fine.
 */
int modifica_alimenti_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che, data una ricetta come parametro, visualizza tutti gli alimenti
 * e le relative quantita che la ricetta necessita per essere preparata.
 *
 * @param[in] ricette vettore di ricette.
 * @param indiceRicetta ricetta di cui si vogliono vedere gli alimenti.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la visualizzazione e' andata a buon fine, 0 altrimenti.
 */
int visualizza_alimenti_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che, data una ricetta come parametro, gestisce tutto quello che riguarda
 * l'aggiunta di un alimento che compone la ricetta.
 * La funzione chiede in input l'alimento da aggiungere alla ricetta, controlla se
 * e' gia usato, effettua l'aggiunta e successivamente applica la modifica sia sul x
 * modifica sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] indiceRicetta ricetta alla quale si vuole aggiungere un alimento.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se l'aggiunta e' stata effettuata, 0 altrimenti.
 */
int inserimento_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che, data una ricetta e un alimento con una quantita, aggiunge l'alimento
 * con la relativa quantita all'interno del vettore di alimenti che compongono
 * la ricetta.
 *
 * @param[in,out] rice puntatore alla ricetta alla quale si vuole aggiungere un alimento.
 * @param[in] indiceAlimento alimento che si vuole aggiungere alla ricetta.
 * @param[in] quantita quantita necessarie alla ricetta per quel alimento.
 * @return 1 se l'aggiunta e' andata a buon fine, 0 altrimenti.
 */
int salva_alimento_in_ricetta(ricetta *rice,int indiceAlimento,int quantita);





/**
 * Funzione che, data una ricetta e un alimento come parametro, controlla se
 * l'alimento serve per preparare la ricetta.
 *
 * @param[in] ricette vettore di ricette.
 * @param indiceRicetta ricetta di cui si vuole vedere se l'alimento ne fa parte.
 * @param indiceAlimento alimento che si vuole vedere se fa parte della ricetta.
 * @return -1 se la ricetta non necessita di quel alimento, l'indice della prima
 * occorrenza altrimenti.
 */
int get_alimento_ricetta(ricetta ricette[],int indiceRicetta,int indiceAlimento);





/**
 * Funzione che, data una ricetta come parametro, gestisce tutto quello che riguarda
 * la cancellazione di un alimento che compone la ricetta.
 * La funzione chiede in input l'alimento da cancellare alla ricetta, controlla se
 * fa parte della ricetta, effettua la cencellazione e successivamente applica la
 * modifica sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] indiceRicetta ricetta alla quale si vuole cancellare un alimento.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la cancellazione dell'alimento dalla ricetta e' andata a buon fine,
 * 0 altrimenti.
 */
int cancellazione_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Funzione che, data una ricetta come parametro, gestisce tutto quello che riguarda
 * la modifica della relativa quantita di un alimento che compone la ricetta.
 * La funzione chiede in input l'alimento di cui si vuole cancellare la quantita, controlla se
 * fa parte della ricetta, chiede la nuova quantita, effettua la modifica e successivamente applica la
 * modifica sia sul vettore di ricette che sul file Ricette.sf.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] indiceRicetta ricetta alla quale si vuole modificare la quantita di un alimento che lo compone.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @return 1 se la modifica della quantita dell'alimento della ricetta e' andata a buon fine, 0 altrimenti.
 */
int modifica_quantita_alimento_ricetta(ricetta ricette[],int indiceRicetta,alimento alimenti[],int lunghezzaVettoreAlimenti);





/**
 * Data una ricetta passata come parametro, la funzione calcola il numero
 * di porzioni che e' possibile preparare per quella ricetta in base alle
 * quantita degli alimenti presenti nel frigo.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param indiceRicetta ricetta di cui si vogliono calcolare il numero di porzioni possibili.
 * @return il numero di porzioni che e' possibile preparare.
 */
int get_numero_porzioni_possibili_ricetta(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceRicetta);





/**
 * Data la ricetta come parametro, la funzione ha il compito di decrementare tutte le quantita
 * disponibili degli alimenti che compongono una ricetta in maniera tale a rendere
 * effettiva la consumazione di una determinata ricetta.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param[in] indiceRicetta ricetta che si vuole consumare.
 * @param[in] porzioni porzioni di ricetta che si vuole consumare.
 * @return 1 se la consumazione della ricetta sulle quantita disponibili e' avvenuta con successo.
 */
int consuma_ricetta_su_alimenti(ricetta ricette[],int lunghezzaVettoreRicette,alimento alimenti[],int lunghezzaVettoreAlimenti,int indiceRicetta,int porzioni);





/**
 * Funzione che si occupa di tutto quello che rigurda l'aggiunta di una ricetta.
 * La funzione chiede in input tutti gli attributi della ricetta, fa gli
 * opportuni controlli e la aggiunge sia sul vettore di alimenti
 * che sul file Ricette.sf.
 * L'aggiunta sul file viene fatta dichiarando un altro vettore di ricette
 * di lunghezza maggiore di 1. Il vecchio vettore viene deallocato e viene
 * passato come valore di ritorno l'indirizzo del nuovo vettore
 * all'interno del puntatore nuovoIndirizzoRicette passato come parametro.
 *
 * @param[in] ricette vettore di ricette.
 * @param[in] lunghezzaVettoreRicette lunghezza del vettore di ricette.
 * @param[in] alimenti vettore di alimenti.
 * @param[in] lunghezzaVettoreAlimenti lunghezza del vettore di alimenti.
 * @param[in,out] nuovoIndirizzoRicette indirizzo del nuovo vettore di ricette
 * nel caso dovesse essere inserita una nuova ricetta.
 * @return lunghezza del vettore di ricette.
 */
int inserimento_ricetta(alimento alimenti[],int lunghezzaVettoreAlimenti,ricetta ricette[],int lunghezzaVettoreRicette,int *nuovoIndirizzoRicette);


#endif /* RICETTE_TOOLS_H_ */

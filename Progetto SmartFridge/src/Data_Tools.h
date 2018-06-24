/**
 *  @file Data_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la gestione delle date.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */


#ifndef DATA_TOOLS_H_
#define DATA_TOOLS_H_




/**
 * La stringa dataN passata come parametro viene controllata per verificare se al suo interno
 * e' presente una data nel formato gg/MM/AAAA e se presente, ritorna la data corrispondente
 * nei puntatori passati come parametro.
 *
 *
 * @param[in] *dataN Stringa che contiene la data da controllare.
 * @param[in,out] *giorno Puntatore ad un interno in cui viene memorizzato il giorno della data.
 * @param[in,out] *mese Puntatore ad un interno in cui viene memorizzato il mese della data.
 * @param[in,out] *anno Puntatore ad un interno in cui viene memorizzato l'anno della data.
 *
 * @return 1 se la stringa passata come parametro e' una data, 0 altrimenti.
 */
int controllo_data(char *dataN,char *giorno,char *mese,int *anno);





/**
 * Dato il carattere passato come parametro, la funzione restituisce
 * il corrispondente valore della data di sistema in fuso orario europeo(CEST).
 * anno: 					'Y'
 * mese: 					'M'
 * giorno: 					'D'
 * ora: 					'H'
 * minuti: 					'm'
 * secondi: 				's'
 * giorno della settimana: 	'W'
 *
 * @param[in] tipoOutput Carattere per la decisione dell'output della funzione.
 * @return -1 se il caratteri passato come parametro e' invalido altrimenti
 * il valore corrispondente al carattere di input della data di sistema.
 */
int get_data(char tipoOutput);





/**
 * La funzione chiede in console, all'utente, di inserire una data che viene
 * controllata e, se corretta, i valori della data vengono inseriti nei
 * puntantori passati come parametro.
 * Il messaggio da visualizzare all'utente viene anche esso passato come parametro.
 *
 *
 * @param[in,out] *giorno Puntatore dove viene memorizzato il giorno inserito dall'utente.
 * @param[in,out] *mese Puntatore dove viene memorizzato il mese inserito dall'utente.
 * @param[in,out] *anno Puntatore dove viene memorizzato l'anno inserito dall'utente.
 * @param[in] messaggio[] Messaggio che viene visualizzato all'utente per fargli inserire la data.
 * @return 1 se la procedura e' andata a buon fine e i valori interi della data.
 */
int get_data_input(char *giorno,char *mese,int *anno,char messaggio[]);





/**
 * Funzione che restituisce, all'interno di un puntatore di tipo data_ora, la data di sistema.
 *
 * @param[in,out] data Puntatore di tipo data_ora dove viene memorizzata la data di sistema.
 * @return 1 se tutto e' andato a buon fine e la data di sistema.
 */
int get_data_pointer(data_ora* data);





/**
 * In base all'orario di sistema, la funzione restituisce una stringa
 * con un augurio per il pasto.
 *
 * >=12 E <=15: "Buon Pranzo!"
 * >15  E <=18: "Buona pausa Break!"
 * >18  E <=24: "Buona Cena!"
 * >0   E <=5:  "Buono spuntino notturno!"
 * >5   E <=10: "Buona Colazione!"
 * >10  E <12:  "Buona Merenda!"
 * altro:       "".
 *
 * @return Un augurio in base al tipo di pasto che si sta per andare a consumare.
 */
char* get_tipo_pasto();





/**
 * Se il valore interno passato come parametro corrisponde ad una anno valido
 * la funzione controllera' se quell'anno e' bisestile o meno.
 *
 * @param[in] anno Anno da controllare.
 * @return 1 se l'anno e' bisestile, 0 altrimenti.
 */
int is_bisestile(int anno);





/**
 * Date le due date passate come parametro, la funzione le converte nel numero
 * di giorni dallo 0 DC e ritorna la distanza in giorni tra data2 e data1.
 * La data2 deve essere la data piu recente.
 *
 * @param[in] data1 variabile di tipo data_ora.
 * @param[in] data2 variabile di tipo data_ora.
 * @param[in] delay numero interno sommato alla differenza tra le due date.
 * @return il numero di giorni di distanza tra data2 e data1.
 */
int get_distanza_in_giorni(data_ora data1,data_ora data2,int delay);





/**
 * Data la variabile di tipo data_ora come parametro, la funzione
 * restituisce il numero di giorni dall'anno 0 fino alla data
 * passata come parametro.
 * La funzione tiene conto anche degli anni bisestili.
 *
 * @param[in] data data di cui si vuole sapere il numero di giorni dall'anno 0.
 * @return numero di giorni dall'anno 0 alla data passata come parametro.
 */
int get_data_in_giorni(data_ora data);





/**
 * In base al numero passato come parametro, la funzione
 * restituisce il giono della settimana corrispondente.
 *
 * @param[in] giorno giorno della settimana di cui si vuole sapere il nome.
 * @return Il nome del giorno della settimana corrispondente.
 *
 * @pre Il valore passato come parametro deve essere compreso da 0 e 6, estremi inclusi.
 */
char* indice_to_giorni_settimana(int giorno);





/**
 * Data la data come parametro, la funzione ritorna il giorno
 * della settimana compreso tra 0 e 6 a cui fa riferimento.
 *
 * @param[in] data data di cui si vuole sapere il giorno della settimana.
 * @return un numero tra 0 e 6, estremi inclusi, in base alla data.
 */
int data_to_giorni_settimana(data_ora data);






/**
 * Le due date passate come parametro vengono confrontate tra di loro
 * per capire quale delle due e' la piu recente.
 *
 * @param[in] data1 parametro numero 1.
 * @param[in] data2 parametro numero 2.
 * @return 1 se data2 e' successiva di data1, -1 se data2 e' antecedente
 * data1 e 0 se le due date sono uguali.
 */
int data_compare(data_ora data1, data_ora data2);


#endif /* DATA_TOOLS_H_ */

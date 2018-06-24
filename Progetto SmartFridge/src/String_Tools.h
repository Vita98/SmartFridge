/**
 *  @file String_Tools.h
 *  @brief     File contenente tutti i prototipi delle funzioni
 *  		   per la gestione delle stringhe.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#ifndef STRING_TOOLS_H_
#define STRING_TOOLS_H_



/**
 * Funzione che controlla se il vettore di caratteri passato come parametro
 * contiene solo cifre numeriche.
 *
 * @param stringa[] Stringa da controllare.
 * @return 1 se la stringa e' un numero, 0 altrimenti.
 */
int is_number(char stringa[]);




/**
 * Funzione che converte il vettore di caratteri passato come parametro
 * in un numero intero.
 *
 * @param[in] number[] Vettore di caratteri da convertire.
 * @return Il valore intero estrapolato dal vettore di caratteri.
 */
int to_number(char number[]);




/**
 * Funzione che ha lo scopo di chiedere in input all'utente un valore intero maggiore o uguale a 0.
 *
 * @param[in] text[] Messaggio che deve essere visualizzato all'utente .
 * @return La scelta, convertita in intero, fatta dall'utente.
 */
int fai_scelta(char text[]);



/**
 * La stringa passata come parametro viene suddivisa in tante stringhe utilizzanddo
 * lo spazio come marcatore.
 *
 * @param[in] stringa[] Stringa che si vuole suddividere.
 * @param[in] destination[][] Matrice di stringhe in cui vengono inserite le stringhe
 *  						  derivanti dalla suddivisione.
 * @return Numero di stringhe derivanti dalla suddivisione
 */
int explode_string(char stringa[],char destination[MASSIME_STRINGHE_ESPLOSE][LUNGHEZZA_STRINGA]);




/**
 * Rimuove tutti gli spazi all'inizio e alla fine della stringa passata come parametro
 * Rimuove anche il carattere di newLine e il carattere di endLine.
 *
 * @param[in] string[] Stringa alla quale si vogliono rimuovere gli spazi.
 * @param[in,out] stringDest[] Stringa in cui viene inserito il risultato dell'operazione.
 * @param[in] lenghtString Lunghezza della stringa.
 * @return 1 se tutto e' andato a buon fine, 0 altrimenti.
 *
 */
int remove_first_last_space(char string[],char stringDest[],int lenghtString);



/**
 * La stringa string[] passata come parametro viene portata tutta a caratteri minuscoli.
 *
 * @param[in] string[] Stringa che si vuole convertire in caratteri minuscoli.
 * @param[in,out] destinationString[] Stringa in cui viene posizionato il risultato dell'operazione.
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti.
 *
 */
int to_lower_string(char string[],char destinationString[]);




/**
 * Viene controllato se la stringa stringa[],passata come parametro, contiene all'interno un numero double.
 *
 * @param[in] stringa[] Stringa da controllare.
 * @return 1 se la stringa e' un numero double, 0 altrimenti.
 */
int is_double(char stringa[]);




/**
 * Funzione utilizzabile per chiedere in console all'utente un numero double.
 *
 * @param[in] messaggio[] Testo da far visualizzare all'utente.
 * @return Il numero inserito dall'utente sottoforma di numero in virgola mobile.
 */
double fai_scelta_double(char messaggio[]);





/**
 * Funzione utilizzabile per chiedere in console all'utente di fare una scelta di tipo SI o NO.
 *
 * @param[in] messaggio[] Testo da far visualizzare all'utente.
 * @return true se l'utente ha inserito si, false altrimenti.
 */
boolean fai_scelta_booleana(char messaggio[]);

#endif /* STRING_TOOLS_H_ */


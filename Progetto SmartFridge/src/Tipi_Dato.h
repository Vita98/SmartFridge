
/**
 *  @file Tipi_Dato.h
 *  @brief     File contenete tutte le definizioni di strutture,enum,costanti e variabili globali.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */





#ifndef TIPI_DATO_H_
#define TIPI_DATO_H_


/**
 * Lunghezza massima di una stringa.
 */
#define LUNGHEZZA_STRINGA 50


/**
 * Lunghezza massima del vettore di scadenze di un alimento.
 */
#define LUNGHEZZA_VET_SCADENZE 10


/**
 * Numero massimo di alimenti di cui una ricetta puo' essere formata.
 */
#define NUMERO_MAX_ALIMENTI 20


/**
 * Valore predefinito di soglia per determinare la lista della spesa,
 * viene memorizzato sul file di configurazione al primo avvio.
 *
 */
#define SOGLIA_SPESA 2


/**
 * Numero massimo di stringhe che possono risultare dall'esplosione di una stringa di 50 caratteri.
 */
#define MASSIME_STRINGHE_ESPLOSE 17


/**
 * Carattere usato per esplicitare l'anno nelle funzioni
 */
#define CARATTERE_ANNO 'Y'


/**
 * Carattere usato per esplicitare il mese nelle funzioni
 */
#define CARATTERE_MESE 'M'


/**
 * Carattere usato per esplicitare il giorno del mese nelle funzioni
 */
#define CARATTERE_GIORNO 'D'


/**
 * Carattere usato per esplicitare l'ora nelle funzioni
 */
#define CARATTERE_ORA 'H'


/**
 * Carattere usato per esplicitare i minuti nelle funzioni
 */
#define CARATTERE_MINUTI 'm'


/**
 * Carattere usato per esplicitare i secondi nelle funzioni
 */
#define CARATTERE_SECONDI 'S'


/**
 * Carattere usato per esplicitare il giorno della settimana nelle funzioni
 */
#define CARATTERE_GIORNO_SETTIMANA 'W'


/**
 * Numero massio usato per rappresentare i giorni della settimana.
 */
#define NUMERO_MASSIMO_GIORNI 6


/**
 * Numero di giorni di una settimana.
 */
#define NUMERO_GIORNI 7


/**
 * Differenza di orario tra GMT e CEST.
 */
#define CEST (+2)


/**
 * Numero di giorni successivi alla data odierna per determinare se
 * un alimento e' in scadenza.
 */
#define DISTANZA_GIORNI_SCADENZA 7


/**
 * Costante utilizzata per effettuare la scelta di ordinamento
 * per kcal.
 */
#define MODALITA_ORDINAMENTO_KCAL_PORZIONE 2


/**
 * Costante utilizzata per effettuare la scelta di ordinamento
 * per frequenza.
 */
#define MODALITA_ORDINAMENTO_FREQUENZA 3


/**
 * Costante utilizzata per effettuare la scelta di ordinamento
 * per preferiti (Solo per le ricette).
 */
#define MODALITA_ORDINAMENTO_PREFERITI 4





/**
 * @typedef boolean
 * Enumerazione boolean usata per definire il tipo booleano.
 */
typedef enum{

	true=1,false=0

}boolean;






#include <stdio.h>
#include <stdlib.h>
#include "String_Tools.h"
#include "Messaggi_Menu.h"


/**
 * Variabile globale usata per memorizzare il limite spesa letto dal file
 * di configurazione.
 */
int limite_spesa;







/**
 * Stuttura per la memorizzazione della data e dell'ora.
 */
typedef struct{

	char Giorno;
	char Mese;
	int Anno;

	char Ora;
	char Minuti;
	char Secondi;

}data_ora;




/**
 * Struttura utilizzata all interno di un alimento per la memorizzazione
 * delle differenti scadenze degli alimenti.
 */
typedef struct{

	int Quantita;
	data_ora Data_Scadenza;

}scadenza;










/**
 * Struttura per la gestione degli alimenti.
 */
typedef struct{

	/**
	 * Numero progressivo dell'alimento utilizzato
	 * per accedere in maniera diretta sul file.
	 */
	int ID_Alimento;
	char Nome[LUNGHEZZA_STRINGA];

	/**
	 * Apporto calorico di un alimento
	 */
	double Kcal_Pezzo;

	/**
	 * Peso di un singolo alimento non divisibile e consumabile
	 * interamente.
	 */
	int Peso;					//Peso in grammi

	/**
	 * Vettore di scadenze utilizzato per la memorizzazione delle quantita
	 * e delle relative scadenze di un alimento.
	 */
	scadenza Scadenze[LUNGHEZZA_VET_SCADENZE];

	/**
	 * Numero di volte che e' stato consumato l'alimento.
	 */
	int Utilizzo;

	/**
	 * Variabile booleana per indicare se l'alimento e'stato cancellato oppure no.
	 * La cancellazione non e' effettiva in quanto potrebbero essere
	 * presenti delle ricette con i riferimenti ad un alimento cancellato e non disponibile.
	 */
	boolean Visibilita;

}alimento;








/**
 * Struttura per la gestione delle ricette.
 */
typedef struct{

	int ID_Ricetta;
	char Nome[LUNGHEZZA_STRINGA];
	double Kcal_Porzione;
	int Alimenti_Quantita[2][NUMERO_MAX_ALIMENTI];
	int Frequenza;
	boolean Visibilita;

}ricetta;








/**
 * Struttura per la gestione dei pasti
 */
typedef struct{

	int ID_Ricetta;
	int Porzioni;
	data_ora Data_Ora;
	boolean visibilita;

}pasto;








/**
 * Struttura per la gestione dello storico spesa e della lista della spesa.
 */
typedef struct{

	int ID_Alimento;
	data_ora Data_Ora;
	int Quantita;

}elemento_spesa;



#endif /* TIPI_DATO_H_ */

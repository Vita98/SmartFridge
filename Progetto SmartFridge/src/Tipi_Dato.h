
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

	/**
	 * Numero intero che rappresenta la quantita di
	 * alimenti aventi data di scadenza Data_Scadenza.
	 */
	int Quantita;
	data_ora Data_Scadenza;

}scadenza;










/**
 * Struttura per la gestione degli alimenti.
 */
typedef struct{

	/**
	 * Numero progressivo dell'alimento utilizzato
	 * per accedere in maniera diretta sul file
	 * e per identificare univocamente gli alimenti.
	 */
	int ID_Alimento;

	char Nome[LUNGHEZZA_STRINGA];

	/**
	 * Apporto calorico di un alimento
	 */
	double Kcal_Pezzo;

	/**
	 * Peso in grammi di un singolo alimento non divisibile e consumabile
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

	/**
	 * Numero progressivo della ricetta utilizzato
	 * per accedere in maniera diretta sul file e per
	 * identificare univocamente le ricette.
	 */
	int ID_Ricetta;

	char Nome[LUNGHEZZA_STRINGA];

	/**
	 * Apporto calorico della ricetta per una
	 * singola porzione.
	 */
	double Kcal_Porzione;

	/**
	 * Matrice che contiene gli alimenti che compongono la ricetta
	 * e le rispettive quantita.
	 * Nella prima riga abbiamo gli ID degli alimenti, nella
	 * seconda riga le quantita necessarie, del rispettivo alimento,
	 * per preparare la ricetta.
	 */
	int Alimenti_Quantita[2][NUMERO_MAX_ALIMENTI];

	/**
	 * Numero di volte che è stata consumata la ricetta.
	 */
	int Frequenza;

	/**
	 * Variabile booleana per indicare se la ricetta e'stato cancellata oppure no.
	 * La cancellazione non e' effettiva in quanto potrebbero essere
	 * presenti delle consumazioni con i riferimenti ad una ricetta cancellata e non disponibile.
	 */
	boolean Visibilita;

}ricetta;








/**
 * Struttura per la gestione dei pasti e dello storico dei pasti.
 */
typedef struct{

	/**
	 * Numero identificativo della ricetta che e' stata consumata
	 * nel pasto.
	 */
	int ID_Ricetta;

	/**
	 * Numero di porzioni che vengono consumate nel pasto.
	 */
	int Porzioni;

	/**
	 * Data in cui viene consumato il pasto.
	 */
	data_ora Data_Ora;

	/**
	 * Variabile booleana per indicare se il pasto e'stato cancellata oppure no.
	 */
	boolean visibilita;

}pasto;








/**
 * Struttura per la gestione dello storico spesa e della lista della spesa.
 */
typedef struct{

	/**
	 * Numero identificativo dell'alimento che si e' acquistato (storico spesa)
	 * oppure dell'alimento che si vuole suggerire di acquistare (lista della spesa).
	 */
	int ID_Alimento;

	/**
	 * Data di acquisto dell'alimento (storico spesa).
	 */
	data_ora Data_Ora;

	/**
	 * Quantita di alimento che si e' acquistata (storico spesa).
	 */
	int Quantita;

}elemento_spesa;



#endif /* TIPI_DATO_H_ */

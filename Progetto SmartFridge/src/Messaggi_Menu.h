/**
 *  @file 	   Messaggi_Menu.h
 *  @brief     File contenente tutte le costanti definite per i messaggi da visualizzare nei vari menu
 *  		   del programma.
 *
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */

#ifndef MESSAGGI_MENU_H_
#define MESSAGGI_MENU_H_


/**
 * Messaggio del menu principale per la scelta delle varie funzionalita' del programma.
 */
#define MENU_PRINCIPALE "\nCosa desidera scegliere?\n****************************************\n1 - Suggerimento della Lista della Spesa\n2 - Suggerimento delle Ricette\n3 - Ricerca Ricette per Alimento\n4 - Opzioni Alimenti\n5 - Opzioni Ricette\n6 - Opzioni Pasti e Menu Settimanale\n7 - Opzioni Spesa\n\n8 - Uscita\n****************************************\nScelta: "

/**
 * Messaggio del menu per la scelta delle opzioni del
 */
#define MENU_SUGGERIMENTO_SPESA "\n****************************************\nLa Lista generata rispettera' una soglia minima stabilita\n1 - Genera la Lista della Spesa\n2 - Visualizza l'ultima Lista generata\n3 - Modifica soglia limite\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_ALIMENTI "\n****************************************\n1 - Visualizza la Lista degli Alimenti\n2 - Modifica Alimento\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_RICETTE "\n****************************************\n1 - Visualizza la Lista delle Ricette\n2 - Aggiungi Ricetta\n3 - Modifica Ricetta\n4 - Cancella Ricetta\n5 - Gestione Ricette Preferite\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_SUGGERIMENTO_ALIMENTI "\n****************************************\nCome desidera visualizzare gli Alimenti?\n1 - Alimenti più usati\n2 - Alimenti presenti\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_ORDINAMENTO_RICETTE "\n****************************************\nCome desidera Ordinare le Ricette?\n1 - Nessun Ordinamento\n2 - Ordinamento per kcal\n3 - Ordinamento per frequenza\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_ORDINAMENTO_ALIMENTI "\n****************************************\nCome desidera Ordinare gli Alimenti?\n1 - Nessun Ordinamento\n2 - Ordinamento per kcal\n3 - Ordinamento per frequenza di utilizzo\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_PASTI "\n****************************************\n1 - Visualizza il Menu Settimanale\n2 - Aggiungi Pasto\n3 - Modifica Pasto\n4 - Cancella Pasto\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_MODIFICA_ALIMENTI "\n****************************************\n1 - Modifica Nome Alimento\n2 - Modifica le kcal per pezzo dell'Alimento\n3 - Modifica il peso dell'Alimento\n4 - Modifica la quantita dell'Alimento\n5 - Modifica le scadenze dell'Alimento\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_OPZIONI_SPESA "\n****************************************\n1 - Inserisci alimenti comprati\n2 - Visualizza storico spesa\n\n0 - Indietro\n****************************************\nScelta: "


#define STRINGASTERISCHI "****************************************"


#define MENU_MODIFICA_RICETTE "\n****************************************\n1 - Modifica Nome Ricetta\n2 - Modifica le kcal per porzione della Ricetta\n3 - Modifica gli alimenti che compongono la Ricetta \n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_MODIFICA_ALIMENTI_RICETTA "\n****************************************\n1 - Inserisci un alimento della ricetta\n2 - Elimina un alimento della ricetta\n3 - Modifica la quantita di un alimento della ricetta\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_OPZIONI_VISUALIZZAZIONE_MENU_SETTIMANALE "Cosa vuoi vedere?\n1-Menu settimanale della settimana in corso\n2-Menu settimanale delle settimane passate\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_GESTISCI_PREFERTI "\n****************************************\n1 - Visualizza le Ricette Preferite\n2 - Aggiungi un Preferito\n3 - Cancella un Preferito\n\n0 - Indietro\n****************************************\nScelta: "


#define MENU_MODIFICA_PASTO "Cosa vuoi modificare del pasto?\n\n1 - Numero porzioni\n2 - Cambiare totalmente pasto consumato\n\n0 - Annulla\n****************************************\nScelta:"


#define MENU_OPZIONI_SUGGERIMENTO_RICETTA "Che ricette vuoi essere suggerito?\n1 - Ricette con alimenti in scadenza\n2 - Ricette che e' possibile preparare\n\n0 - Indietro\n****************************************\nScelta:"

#endif /* MESSAGGI_MENU_H_ */


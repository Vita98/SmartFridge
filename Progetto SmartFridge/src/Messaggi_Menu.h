/*
 * Messaggi_Menu.h
 *
 *  Created on: 17 mag 2018
 *      Author: My-PC
 */

#ifndef MESSAGGI_MENU_H_
#define MESSAGGI_MENU_H_


char MenuPrincipale[] =
			"\nCosa desidera scegliere?\n****************************************\n"
					"1 - Suggerimento della Lista della Spesa\n"
					"2 - Suggerimento delle Ricette\n3 - Ricerca Ricette\n"
					"4 - Opzioni Alimenti\n5 - Opzioni Ricette\n6 - Opzioni Pasti\n\n"
					"7 - Uscita\n****************************************\nScelta: ";

char MenuSuggerimentoSpesa[] =
		"\n****************************************\n"
				"La Lista generata rispetterà una soglia minima stabilita\n"
				"1 - Genera la Lista della Spesa\n2 - Visualizza l'ultima Lista generata\n"
				"3 - Modifica soglia limite\n\n0 - Indietro\n****************************************\nScelta: ";

char MenuAlimenti[] =
		"\n****************************************\n"
				"1 - Visualizza la Lista degli Alimenti\n2 - Aggiungi Alimento\n3 - Modifica Alimento"
				"\n\n0 - Indietro\n****************************************\nScelta: ";

char MenuRicette[] =
		"\n****************************************\n"
				"1 - Visualizza la Lista delle Ricette\n2 - Aggiungi Ricetta\n3 - Modifica Ricetta\n"
				"4 - Cancella Ricetta\n\n0 - Indietro\n****************************************\nScelta: ";

char MenuSuggerimentoAlimenti[] =
		"\n****************************************\n"
				"Come desidera visualizzare gli Alimenti?\n1 - Alimenti più usati\n2 - Alimenti presenti\n"
				"\n0 - Indietro\n****************************************\nScelta: ";

char MenuOrdinamentoRicette[] =
		"\n****************************************\n"
				"Come desidera Ordinare le Ricette?\n1 - Ordinamento per kcal\n2 - Ordinamento per frequenza\n"
				"\n0 - Indietro\n****************************************\nScelta: ";

char MenuPasti[] =
		"\n****************************************\n"
				"1 - Visualizza il Menù Settimanale\n2 - Aggiungi Pasto\n3 - Modifica Pasto\n"
				"4 - Cancella Pasto\n\n0 - Indietro\n****************************************\nScelta: ";


#endif /* MESSAGGI_MENU_H_ */

/*
 * Alimenti_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */
#include "Tipi_Dato.h"
#include <String.h>

/* FUNZIONE CHE SERVE PER VERIFICARE SE ESISTE L'ALIMENTO PASSATO	*
 * COME PARAMETRO Parametri_Ricerca NEL VETTORE DI ALIMENTI			*
 * 																	*
 * LA FUNZIONE ELIMINA TUTTI GLI SPAZI FINALI E INIZIALI DELLE DUE	*
 * STRINGHE E INOLTRE NE CREA UNA COPIA IN MINUSCOLO				*
 * 																	*
 * LA FUNZIONE RITORNA -1 SE NON VIENE TROVATA NESSUNA 				*
 * CORRISPONDENZA, ALTRIMENTI RITORNA LA POSIZIONE DELLA PRIMA 		*
 * OCCORRENZA														*/
int getAlimento(alimento alimenti[], int Lunghezza_Alimenti,
		char Parametri_Ricerca[]) {

	int i;
	char StringTempParametri[LUNGHEZZA_STRINGA];
	removeFirstLastSpace(Parametri_Ricerca, StringTempParametri,
			LUNGHEZZA_STRINGA);
	toLowerString(StringTempParametri, StringTempParametri);

	for (i = 0; i < Lunghezza_Alimenti; i++) {
		char StringTempVettore[LUNGHEZZA_STRINGA];
		removeFirstLastSpace(alimenti[i].Nome, StringTempVettore,
				LUNGHEZZA_STRINGA);
		toLowerString(StringTempVettore, StringTempVettore);

		//se le due stringhe sono uguali
		if (strcmp(StringTempParametri, StringTempVettore) == 0)
			return i;
	}

	return -1;
}

/* FUNZIONE CHE HA IL COMPITO DI VISUALIZZARE IN CONSOLE 	*
 * LE INFORMAZIONI DI GLI ALIMENTI PRESENTI NEL VETTORE		*
 * 															*
 * RITORNA 1 SE L'OPERAZIONE E' ANDATA A BUON FINE			*/
int Visualizza_Alimenti(alimento alimenti[], int Lunghezza_Vettore) {

	int i;

	printf("Alimenti presenti:\n");
	for (i = 0; i < Lunghezza_Vettore - 1; i++) {

		printf("%d - %s \t| Peso: %d \t| Id: %d   |   Quantita: %d\n", i,
				alimenti[i].Nome, alimenti[i].Peso, alimenti[i].ID_Alimento,
				getQuantita(alimenti[i]));
	}
	return 1;
}

/* FUNZIONE CHE EFFETTUA LA MODIFICA DI UN DETERMINATO		*
 * ALIMENTO CHIESTO IN INPUT NELLA STESSA FUNZIONE			**/
int Modifica_Alimento(alimento alimenti[], int Lunghezza_Vettore) {

	printf("\n\n             Modifica Alimento\n");
	printf("\n****************************************\n");

	char scelta[LUNGHEZZA_STRINGA];

	printf("\nInserisci il nome dell'alimento:");
	fgets(scelta, LUNGHEZZA_STRINGA, stdin);

	if (getAlimento(alimenti, Lunghezza_Vettore, scelta) > -1) {
		//se ritorna un valore >-1 vuol dire che ha trovato una corrispondenza
		printf("\n\nAlimento Trovato\n\n");

		//devo fare la modifica effettiva

	} else
		printf("\n\nNon esiste nessu alimento che si chiama in quel modo!\n\n");

	return 1;
}




/* FUNZIONE CHE RECUPERA DAL VETTORE DELLE SCADENZE			*
 * LA QUANTITA' DELL'ALIMENTO PASSATO TRAMITE IL PARAMETRO	*/
int getQuantita(alimento alim) {

	int quantita = 0, j;
	for (j = 0; j < LUNGHEZZA_VET_SCADENZE; j++) {
		quantita += alim.Scadenze[j].Quantita;
	}
	return quantita;
}




/* FUNZIONE CHE GESTISCE IL MENU RELATIVO AGLI ALIMENTI		*
 * CHIEDE ALL'UNTETE DI FARE UNA SCELTA E CONTROLLA CHE		*
 * LA SCELTA SIA VALIDA; 									*
 * SE LO E' RICHIAMA LE OPPORTUNE FUNZIONI CHE ESEGUONO		*
 * IL PARTOCOLARE COMPITO									*/
int Scelta_Opzioni_Alimenti(alimento alimenti[], int Lunghezza_Alimenti) {
	int NumScelta;

	do {
		NumScelta = FaiScelta(MenuAlimenti);

		switch (NumScelta) {
		case 1:
			Visualizza_Alimenti(alimenti, Lunghezza_Alimenti);
			break;
		case 2:
			break;
		case 3:
			//modifica dell'alimento
			Modifica_Alimento(alimenti, Lunghezza_Alimenti);

			break;
		case 0:
			//case di uscita dal sottomenu
			break;
		default:
			printf("Scelta errata! Riprova!\n");
		}

	} while (NumScelta != 0);

	return 1;
}

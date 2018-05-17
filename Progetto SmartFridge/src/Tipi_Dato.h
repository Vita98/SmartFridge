/*
 * TIpi_Dato.h
 *
 *  Created on: 16 mag 2018
 *      Author: My-PC
 */

#ifndef TIPI_DATO_H_
#define TIPI_DATO_H_

#define LUNGHEZZA_STRINGA 50
#define LUNGHEZZA_VET_SCADENZE 10
#define NUMERO_MAX_ALIMENTI 20

#include <stdio.h>
#include <stdlib.h>
#include "String_Tools.h"






/* DEFINIZIONE DELLA STRUTTURA PER   	    *
 * LA MEMORIZZAZIONE  DELLA DATA E L'ORA	*/
typedef struct{

	char Giorno;
	char Mese;
	int Anno;

	char Ora;
	char Minuti;
	char Secondi;

}data_ora;





/* DEFINIZIONE DELLA STRUTTURA UTLIZZATA		*
 * ALL'INTERNO DI UN ALIMENTO PER MEMORIZZARE	*
 * LE DIFFERENTI SCADENZE DEI PRODOTTI			*/
typedef struct{

	int Quantita;
	data_ora Data_Scadenza;

}scadenza;






/* DEFINIZIONE DI UNA ENUMERAZIONE	*
 * PER DEFINIRE IL TIPO BOOLEANO	*/
typedef enum{

	true,false

}boolean;






/* DEFINIZIONE DELLA STRUTTURA PER LA 	*
 * MEMORIZZAZIONE DEGLI ALIMENTI		*/
typedef struct{

	int ID_Alimento;
	char Nome[LUNGHEZZA_STRINGA];
	double Kcal_Pezzo;
	int Peso;					//Peso in grammi
	scadenza Scadenze[LUNGHEZZA_VET_SCADENZE];
	int Utilizzo;
	boolean Visibilita;

}alimento;





/* DEFINIZIONE DELLA STRUTTURA PER LA 	*
 * MEMORIZZAZIONE DELLE RICETTE			*/
typedef struct{

	int ID_Ricetta;
	char Nome[LUNGHEZZA_STRINGA];
	double Kcal_Porzione;
	int Alimenti_Quantita[2][NUMERO_MAX_ALIMENTI];
	int Frequenza;
	boolean Visibilita;

}ricetta;





/* DEFINIZIONE DELLA STRUTTURA PER LA 	*
 * MEMORIZZAZIONE DEI PASTI		*/
typedef struct{

	int ID_Ricetta;
	int Porzioni;
	data_ora Data_Ora;

}pasto;





/* DEFINIZIONE DELLA STRUTTURA PER LA *
 * MEMORIZZAZIONE DELL'ELEMENTO SPESA *
 * CHE VIENE MEORIZZATO NELLO STORICO *
 * SPESA E NELLA LISTA DELLA SPESA    */
typedef struct{

	int ID_Alimento;
	data_ora Data_Ora;
	int Quantita;

}elemento_spesa;



#endif /* TIPI_DATO_H_ */

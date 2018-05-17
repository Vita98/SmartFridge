/*
 ============================================================================
 Name        : Progetto.c
 Author      : Vitandrea Sorino
 Version     :
 Copyright   : Your copyright notice
 Description : Hel1lo World in C, Ansi-style
 ============================================================================
 */

#include "Tipi_Dato.h"

int FaiScelta(char[]);

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	printf("Benvenuto in SMARTFRIDGE\n\n");
	printf("Hai a dispozione varie scelte, cosa desideri?\n");
	printf("1 - Suggerimento (Ricetta/Spesa)\n2 - Visualizzazione");




	//suggerimento (spesa, ricetta(visualizzazione)
	//aggiunta/Modifica/cancellazione (Alimento ,ricetta, menu settimanale)
	//Visualizzazione (ordinamnto ricette( x alimento, kcal, per preferiti, per scadenza)
	//ricerca (ricetta x alimento, per nome, di un alimento)
	return 0;
}






/*FUNZIONE UTILIZZATA PER PRENDERE IN INPUT				*
 *UN VALORE INTERO										*
 *														*
 *LA FUNZIONE VISUALIZZA IL MESSAGGIO PASSATO COME 		*
 *PARAMETRO E CHIEDE IN INPUT UN NUMERO DI CUI VENGONO	*
 *FATTI TUTTI I CONTROLLI								*
 *														*
 *LA FUNZIONE RITORNA IL NUMERO INTERO CHIESTO			*
 *IN INPUT ALL'UTENTE									*/
int FaiScelta(char text[]){

	char scelta[LUNGHEZZA_STRINGA];

	do{
		//Stampo il messaggio passato come parametro
		printf(text);
		fgets(scelta,LUNGHEZZA_STRINGA,stdin);

		//Svuoto il buffer nel caso venga inserita una stringa piu grande della lunghezza massima
		fflush(stdin);

		//Se la stringa presa in input non e' un numero scrivo un messaggio di errore
		//altrimenti la funzione ritorna il numero preso in input convertito in intero
		if(!isNumber(scelta)) printf("Scelta errata!\n");
		else return toNumber(scelta);

		//continuo a chiedere in input la scelta fino a che non e' valida
	}while(!isNumber(scelta));
	return 0;
}

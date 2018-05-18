/*
 * String_Tools.c
 *
 *      Author: Vitandrea Sorino
 */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tipi_Dato.h"




/* FUNZIONE CHE RITORNA 1 SE LA STRINGA PASSATA     *
 * COME PARAMETRO E' UN NUMERO ALTRIMENTI RITORNA 0 *
 * */
int isNumber(char Stringa[]){
	int cont=0;
	int i;
	for(i=0;i<strlen(Stringa)-1;i++){
		if(isdigit(Stringa[i])){
			cont++;
		}else break;
	}
	if(cont==strlen(Stringa)-1) return 1;
	else return 0;
}




/* FUNZIONE CHE CONVERTE LA STRINGA PASSATA *
 * COME PARAMENTRO IN UN INTERO     		*/
int toNumber(char number[]){
	char *ptr;
	return (int)strtol(number,&ptr,0);
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
int FaiScelta(char text[]) {

	char scelta[LUNGHEZZA_STRINGA];

	do {
		//Stampo il messaggio passato come parametro
		printf(text);
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);

		//Svuoto il buffer nel caso venga inserita una stringa piu grande della lunghezza massima
		fflush(stdin);

		//Se la stringa presa in input non e' un numero scrivo un messaggio di errore
		//altrimenti la funzione ritorna il numero preso in input convertito in intero
		if (!isNumber(scelta))
			printf("Scelta errata!\n");
		else
			return toNumber(scelta);

		//continuo a chiedere in input la scelta fino a che non e' valida
	} while (!isNumber(scelta));
	return 0;
}

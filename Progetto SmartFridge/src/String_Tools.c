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





/* FUNZIONE CHE RIMUOVE GLI SPAZI ALL'INIZIO   *
 * E ALLA FINE DELLA STRINGA				   *
 *											   *
 * RITORNA LA NUOVA STRINGA SENZA GLI SPAZI    */
int removeFirstLastSpace(char String[],char StringDest[],int LenghtString){
	int i=0;
	int countFirst=0;
	int countLast=0;

	//Elimino il carattere di newline se e' presente all'interno della stringa
	for(i=0;i<LenghtString;i++) if(String[i] == '\n') String[i]= '\0';

	while(String[i]==' ' && i < LenghtString){
		countFirst++;
		i++;
	}

	i=1;
	while(String[LenghtString-i]==' ' && i <LenghtString){
			countLast++;
			i++;
	}


	for(i=0;i<(LenghtString-countFirst-countLast);i++){
		if((i+countFirst)<(LenghtString-countLast))
			StringDest[i]=String[i+countFirst];
	}
	return 1;

}





/* FUNZIONE CHE CONVERTE TUTTI I CARATTERI DELLA STRINGA   	*
 * PASSATA COME PARAMENTRO IN MINUSCOLO						*
 *
 * LA STRINGA RISULTANTE VIENE INSERITA NELLA STRINGA 		*
 * PASSATA COME PARAMETRO DestinationString					*/
int toLowerString(char string[],char DestinationString[]){
	int i;
	for(i=0;i<strlen(string);i++){
		DestinationString[i]=tolower(string[i]);
	}
	return 1;
}




/* FUNZIONE CHE ESPLODE LA STRINGA UTILIZZANDO 					*
 * LO SPAZIO COME MARCATORE 									*
 * 																*
 * LE STRINGHE DERIVATE VENGONO INSERITE ALL'INTERNO DI			*
 * UNA MATRICE PASSATA COME PARAMENTRO							*
 * 																*
 * IGNORA TUTTE LE PAROLE DI LUNGHEZZA MINORE DI 2				*/
int explodeString(char Stringa[],char Destination[MASSIME_STRINGHE_ESPLOSE][LUNGHEZZA_STRINGA]){

   const char s[2] = " ";//MARCATORE
   char *token;

   /* get the first token */
   token = strtok(Stringa, s);

   /* walk through other tokens */
   int i=0;
   while( token != NULL ) {
	  printf( "\n%s\n", token );

	  if(strlen(token) > 2){
		  strcpy(Destination[i],token);
		  i++;
	  }

	  token = strtok(NULL, s);
   }

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

/*
 * String_Tools.c
 *
 *      Author: Vitandrea Sorino
 */
#include "Tipi_Dato.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>





/* FUNZIONE CHE RITORNA 1 SE LA STRINGA PASSATA     *
 * COME PARAMETRO E' UN NUMERO ALTRIMENTI RITORNA 0 *
 * */
int is_number(char stringa[]){
	int cont=0;
	int i;
	for(i=0;i<strlen(stringa)-1;i++){
		if(isdigit(stringa[i])){
			cont++;
		}else break;
	}
	if(cont==strlen(stringa)-1) return 1;
	else return 0;
}




/* FUNZIONE CHE CONVERTE LA STRINGA PASSATA *
 * COME PARAMENTRO IN UN INTERO     		*/
int to_number(char number[]){
	char *ptr;
	return (int)strtol(number,&ptr,0);
}




/* FUNZIONE CHE RITORNA 1 SE LA STRINGA PASSATA     *
 * COME PARAMETRO E' UN NUMERO A VIRGOLA MOBILE		*
 * ALTRIMENTI RITORNA 0 							*/
int is_double(char stringa[]){
	int cont=0;
	int i;
	boolean flag=false;
	for(i=0;i<strlen(stringa)-1;i++){
		if(i==0 && stringa[i] == '.') return 0;
		else if(i==strlen(stringa)-2 && stringa[i] == '.') return 0;
		if(isdigit(stringa[i]) || (stringa[i]=='.' && flag==false)){
			cont++;
			if(stringa[i]=='.') flag=true;
		}else break;
	}
	if(cont==strlen(stringa)-1) return 1;
	else return 0;
}





/* FUNZIONE CHE RIMUOVE GLI SPAZI ALL'INIZIO   *
 * E ALLA FINE DELLA STRINGA				   *
 *											   *
 * RITORNA LA NUOVA STRINGA SENZA GLI SPAZI    */
int remove_first_last_space(char string[],char stringDest[],int lenghtString){
	int i=0;
	int countFirst=0;
	int countLast=0;

	//Elimino il carattere di newline se e' presente all'interno della stringa
	for(i=0;i<lenghtString;i++) if(string[i] == '\n') string[i]= '\0';

	while(string[i]==' ' && i < lenghtString){
		countFirst++;
		i++;
	}

	i=1;
	while(string[lenghtString-i]==' ' && i <lenghtString){
			countLast++;
			i++;
	}


	for(i=0;i<(lenghtString-countFirst-countLast);i++){
		if((i+countFirst)<(lenghtString-countLast))
			stringDest[i]=string[i+countFirst];
	}
	return 1;

}





/* FUNZIONE CHE CONVERTE TUTTI I CARATTERI DELLA STRINGA   	*
 * PASSATA COME PARAMENTRO IN MINUSCOLO						*
 *
 * LA STRINGA RISULTANTE VIENE INSERITA NELLA STRINGA 		*
 * PASSATA COME PARAMETRO DestinationString					*/
int to_lower_string(char string[],char destinationString[]){
	int i;
	for(i=0;i<strlen(string);i++){
		destinationString[i]=tolower(string[i]);
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
int explode_string(char stringa[],char destination[MASSIME_STRINGHE_ESPLOSE][LUNGHEZZA_STRINGA]){

   const char s[2] = " ";//MARCATORE
   char *token;

   /* get the first token */
   token = strtok(stringa, s);

   /* walk through other tokens */
   int i=0;
   while( token != NULL ) {
	  printf( "\n%s\n", token );

	  if(strlen(token) > 2){
		  strcpy(destination[i],token);
		  i++;
	  }

	  token = strtok(NULL, s);
   }

   return i;
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
int fai_scelta(char text[]) {

	char scelta[LUNGHEZZA_STRINGA];
	boolean flag;

	do {
		flag=false;
		//Stampo il messaggio passato come parametro
		printf(text);
		fgets(scelta, LUNGHEZZA_STRINGA, stdin);

		//Svuoto il buffer nel caso venga inserita una stringa piu grande della lunghezza massima
		fflush(stdin);

		//Se la stringa presa in input non e' un numero scrivo un messaggio di errore
		//altrimenti la funzione ritorna il numero preso in input convertito in intero
		if (!is_number(scelta) || strlen(scelta)==1)
			printf("Scelta errata!\n");
		else{
			if(to_number(scelta)<0){
				printf("Scelta errata!\n");
				flag=true;
			}else return to_number(scelta);
		}


		//continuo a chiedere in input la scelta fino a che non e' valida
	} while (!is_number(scelta) || strlen(scelta)==1 || flag==true );
	return 0;
}





/*FUNZIONE UTILIZZATA PER PRENDERE IN INPUT				*
 *UN VALORE DOUBLE										*
 *														*
 *LA FUNZIONE VISUALIZZA IL MESSAGGIO PASSATO COME 		*
 *PARAMETRO E CHIEDE IN INPUT UN NUMERO DI CUI VENGONO	*
 *FATTI TUTTI I CONTROLLI								*
 *														*
 *LA FUNZIONE RITORNA IL NUMERO INTERO CHIESTO			*
 *IN INPUT ALL'UTENTE									*/
double fai_scelta_double(char messaggio[]){

	char stringa[LUNGHEZZA_STRINGA];
	double Kcal=0.0;

	do{
		printf(messaggio);

		fgets(stringa,LUNGHEZZA_STRINGA,stdin);

		if(is_double(stringa)){
			Kcal=atof(stringa);
		}

	}while(Kcal == 0.0);

	return Kcal;
}







/* FUNZIONE CHE CHIEDE ALL'UTENTE DI FARE UNA 	*
 * SCELTA DI TIPO BOOLEANA CIOÈ SI O NO			*
 * 												*
 * COME PARAMETRO HA IL MESSAGGIO CHE DEVE 		*
 * ESSERE STAMPATO ALL'UTENTE					*
 * 												*
 * LA FUNZIONE RESTITUISCE TRUE SE L'UTENTE		*
 * HA DETTO SI, ALTRIMENTI RESTITUISCE FALSE	*/
boolean fai_scelta_booleana(char messaggio[]){

	char suggerimenti[]="(1 - SI /2 o Altro - NO) = ";
	char stringaFinal[LUNGHEZZA_STRINGA+strlen(suggerimenti)];
	strcpy(stringaFinal,messaggio);
	strcat(stringaFinal,suggerimenti);

	int scelta=fai_scelta(stringaFinal);

	if(scelta==1) return true;
	else return false;

}


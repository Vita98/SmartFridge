/**
 *  @file String_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in String_Tools.h.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include "Tipi_Dato.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>





/**
 * Funzione che controlla se il vettore di caratteri passato come parametro
 * contiene solo cifre numeriche.
 */
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






/**
 * Funzione che converte il vettore di caratteri passato come parametro
 * in un numero intero.
 * @pre La stringa passata come parametro deve avere almeno un carattere numerico.
 */
int to_number(char number[]){
	char *ptr;
	return (int)strtol(number,&ptr,0);
}






/**
 * Viene controllato se la stringa stringa[],passata come parametro, contiene all'interno un numero double.
 */
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







/**
 * Rimuove tutti gli spazi all'inizio e alla fine della stringa passata come parametro,
 * rimuove anche il carattere di newLine e il carattere di endLine.
 *
 * @pre La lunghezza della stringa deve essere la lunghezza effettiva della stringa
 * passata come parametro altrimenti la funzione potrebbe restituire valori inattesi.
 */
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








/**
 *
 * La stringa string[] passata come parametro viene portata tutta a caratteri minuscoli.
 */
int to_lower_string(char string[],char destinationString[]){
	int i;
	for(i=0;i<strlen(string);i++){
		destinationString[i]=tolower(string[i]);
	}
	return 1;
}







/**
 * La stringa passata come parametro viene suddivisa in tante stringhe utilizzanddo
 * lo spazio come marcatore.
 *
 * @pre stringa[] non deve essere vuota
 * @post vengono tralasciate tutte le stringhe di lunghezza minore o uguale di 2
 */
int explode_string(char stringa[],char destination[MASSIME_STRINGHE_ESPLOSE][LUNGHEZZA_STRINGA]){

   const char s[2] = " ";//MARCATORE
   char *token;

   /* get the first token */
   token = strtok(stringa, s);

   /* walk through other tokens */
   int i=0;
   while( token != NULL ) {

	  if(strlen(token) > 2){
		  strcpy(destination[i],token);
		  i++;
	  }

	  token = strtok(NULL, s);
   }

   return i;
}









/**
 * Funzione che ha lo scopo di chiedere in input all'utente un valore intero maggiore o uguale a 0.
 *
 * @pre La stringa passata come parametro non deve essere vuota.
 */
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








/**
 * Funzione utilizzabile per chiedere in console all'utente un numero double.
 *
 * @post La scelta fatta dall'utente viene gia controllata all'interno della funzione.
 */
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









/**
 * Funzione utilizzabile per chiedere in console all'utente di fare una scelta di tipo SI o NO.
 *
 * @post La scelta fatta dall'utente viene gia controllata all'interno della funzione.
 */
boolean fai_scelta_booleana(char messaggio[]){

	char suggerimenti[]="(1 - SI /2 o Altro - NO) = ";
	char stringaFinal[LUNGHEZZA_STRINGA+strlen(suggerimenti)];
	strcpy(stringaFinal,messaggio);
	strcat(stringaFinal,suggerimenti);

	int scelta=fai_scelta(stringaFinal);

	if(scelta==1) return true;
	else return false;

}

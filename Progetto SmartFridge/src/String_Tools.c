/*
 * String_Tools.c
 *
 *      Author: Vitandrea Sorino
 */


#include <ctype.h>
#include <stdlib.h>
#include <string.h>



/* FUNZIONE CHE RITORNA 1 SE LA STRINGA PASSATA     *
 * COME PARAMETRO E' UN NUMERO ALTRIMENTI RITORNA 0 *
 * */
int isNumber(char Stringa[]){
	int cont=0;
	int i;
	for(i=0;i<strlen(Stringa);i++){
		if(isdigit(Stringa[i])){
			cont++;
		}else break;
	}
	if(cont==strlen(Stringa)) return 1;
	else return 0;
}




/* FUNZIONE CHE CONVERTE LA STRINGA PASSATA *
 * COME PARAMENTRO IN UN INTERO     		*/
int toNumber(char number[]){
	char *ptr;
	return (int)strtol(number,&ptr,0);
}

/*
 * String_Tools.c
 *
 *      Author: Vitandrea Sorino
 */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



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

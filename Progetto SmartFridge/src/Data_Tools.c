/*
 * Data_Tools.c
 *
 *  Created on: 29 mag 2018
 *      Author: My-PC
 */

#include <String.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tipi_Dato.h"




//funzione che esegue tutti i controlli sulla data e che da come valore di ritorno un valore intero che indica se la data Ã¨ corretta o no
//Inoltre utilizzando i puntatori restituisce i valori convertiti in intero del giorno,mese,anno
int ControlloData(char *dataN,int *giorno,int *mese,int *anno){
    if(strchr(dataN,'/')!=0){     //controllo se all'interno del vettore c'e' uno /
        char *c;
        char Num[11];  //vettore che conterra'  il valore estrapolato per il giorno
        char Num1[11]; //vettore che conterra il valore estrapolato per il mese
        c=strchr(dataN,'/');      //assegno il puntatore di ritorno della funzione strchr alla variabile puntatore c
        strncpy(Num, dataN,strlen(dataN)-strlen(c));  //creo una copia di c fino all'occorrenza dello / in Num
        if((*giorno=toNumber(Num))>0 && *giorno<31){        //richiamo la funzione ParsChatInt per convertire la stringa in intero e assegno il valore intero alla variabile punattore giorno
            if(strchr(c,'/')!=0){
                char *c1=strchr(c,'/')+1;
                if(strchr(c1,'/')!=0){         //controllo se c'e' un altro / all'interno del vettore di caratteri
                    char *c2=strchr(c1,'/');   //e assegno dal quella posizione in poi al puntatore c2
                    strncpy(Num1, c1,strlen(c1)-strlen(c2));  //mi creo una copia in maniera tale che Num1 contenga il valore del mese etrapolato dal vettore di caratteri
                    if((*mese=toNumber(Num1))>0 && *mese<13){
                        *anno=atoi(strchr(c2,'/')+1);  //assegno al puntatore anno il valore intero dell'anno estrapolato dal vettore di caratteri
                        return 0;
                    }else return 1;
                }else return 1;
            }else return 1;
        }else return 1;
    }else return 1;
}





/* FUNZIONE CHE, DATO IL CARATTERE PASSATO COME	*
 * PARAMETRO, RESTITUISCE IL RISPETTIVO VALORE 	*
 * DELLA DATA NEL MOMENTO DELLA CHIAMATA CIOÈ 	*
 * I VALORI DELLA DATA DI SISTEMA				*
 * 												*
 * SE IL CARATTERE È INVALIDO LA FUNZIONE 		*
 * RESTITUISCE -1								*/
int getData(char TipoOutput){

	   time_t rawtime;
	   struct tm *info;

	   time(&rawtime);
	   /* Get GMT time */
	   info = gmtime(&rawtime );

	   switch(TipoOutput){
	   	   case CARATTERE_ANNO:
				return  1900+info->tm_year;
	   	   case CARATTERE_GIORNO:
	   		   return info->tm_mday;
	   	   case CARATTERE_MESE:
	   		   return 1+info->tm_mon;
	   	   case CARATTERE_ORA:
	   		   return info->tm_hour+2;
	   	   case CARATTERE_SECONDI:
	   		   return info->tm_sec;
	   	   case CARATTERE_MINUTI:
	   		   return info->tm_min;
	   	   default:return -1;
	   }

	   return -1;

}





/* FUNZIONE CHE CHIEDE IN INPUT ALL'UTENTE UNA DATA		*
 * CHE VIENE CONTROLLATA								*
 * LA FUNZIONE VISUALIZZA COM MESSAGGIO ALL'UNTENTE		*
 * IL MESSAGGIO PASSATO COME PARAMETRO					*
 * 														*
 * LA FUNZIONE RITORNA 1 SE È ANDATO TUTTO BENE E 		*
 * INOLTRE RESTITUISCE NEI TRE PUNTATORI AD INTERI 		*
 * PASSATI COME PARAMETRO, I VALORI DELLA DATA INSERITA *
 * DALL'UTENTE											*/
int getDataInput(int *giorno,int *mese,int *anno,char messaggio[]){

	char data[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		puts(messaggio);
		fgets(data,LUNGHEZZA_STRINGA,stdin);

		if(ControlloData(data,giorno,mese,anno)){
			printf("\nData errata!Reinseriscila!\n");
			flag=true;
		}

	}while(flag);

	return 1;

}



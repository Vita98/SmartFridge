/*
 * Data_Tools.c
 *
 *  Created on: 29 mag 2018
 *      Author: My-PC
 */

#include <String.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "Tipi_Dato.h"




//funzione che esegue tutti i controlli sulla data e che da come valore di ritorno un valore intero che indica se la data è corretta o no
//Inoltre utilizzando i puntatori restituisce i valori convertiti in intero del giorno,mese,anno
int ControlloData(char *dataN,int *giorno,int *mese,int *anno){
    if(strchr(dataN,'/')!=0){     //controllo se all'interno del vettore c'e' uno /
        char *c;
        char Num[11];  //vettore che conterra'� il valore estrapolato per il giorno
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





int getData(char TipoOutput){

	   time_t rawtime;
	   struct tm *info;

	   time(&rawtime);
	   /* Get GMT time */
	   info = gmtime(&rawtime );

	   switch(TipoOutput){
	   	   case CARATTERE_ANNO:
				return  1900+info->tm_year;
				break;
	   	   case CARATTERE_GIORNO:
	   		   return info->tm_mday;
	   		   break;
	   	   case CARATTERE_MESE:
	   		   return 1+info->tm_mon;
	   	   default:return 0;
	   }

	   return 1;

}

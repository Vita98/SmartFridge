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


int GiorniMesi[]={31,28,31,30,31,30,31,31,30,31,30,31};





/* FUNZIONE CHE CONTROLLA SE L'ANNO PASSATO		*
 * COME PARAMETRO E' BISESTILE OPPURE NO		*
 * 												*
 * RITORNA 1 SE LO E' E 0 ALTRIMENTI			*/
int isBisestile(int anno){
	if((anno%4) == 0){
		if((anno%100) != 0) return 1;
		else{
			if((anno%400) ==0) return 1;
			else return 0;
		}
	}else return 0;
}






//funzione che esegue tutti i controlli sulla data e che da come valore di ritorno un valore intero che indica se la data Ã¨ corretta o no
//Inoltre utilizzando i puntatori restituisce i valori convertiti in intero del giorno,mese,anno
int ControlloData(char *dataN,char *giorno,char *mese,int *anno){
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
                        if(*anno!=0){
                        	//controllo se l'anno e' bisestile
                        	if(isBisestile(*anno)) GiorniMesi[1]=29;
                        	else GiorniMesi[1]=28;

                        	if(*giorno<=GiorniMesi[(*mese-1)]) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
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
	   case CARATTERE_GIORNOSETTIMANA:
		   return info->tm_wday-1;
   }

   return -1;

}





int getData2(data_ora* data){

   time_t rawtime;
   struct tm *info;

   time(&rawtime);
   /* Get GMT time */
   info = gmtime(&rawtime );


   (*data).Anno=1900 + (*info).tm_year;
   (*data).Giorno= (*info).tm_mday;
   (*data).Mese=(*info).tm_mon+1;
   (*data).Ora=(*info).tm_hour+2;
   (*data).Minuti=(*info).tm_min;
   (*data).Secondi=(*info).tm_sec;

   return 1;

}





/* FUNZIONE CHE CONTROLLA L'ORARIO ATTUALE E,IN BASE	*
 * AD ESSO RESTITUISCE UNA STRINGA CON UN AUGURIO 		*
 * PER IL PASTO											*/
char* getTipoPasto(){
time_t rawtime;
   struct tm *info;

   time(&rawtime);
   /* Get GMT time */
   info = gmtime(&rawtime );

   int ora=(*info).tm_hour+2;

   if(ora >= 12 && ora <= 15) return "Buon Pranzo!";
   else if(ora > 15 && ora <= 18) return "Buona pausa Break!";
   else if(ora > 18 && ora <= 24) return "Buona Cena!";
   else if(ora > 0 && ora <= 5) return "Buono spuntino notturno!";
   else if(ora > 5 && ora <= 10) return "Buona Colazione!";
   else if(ora > 10 && ora < 12) return "Buona Merenda!";
   else return "";
}





/* FUNZIONE CHE DATO UN NUMERO TRA 0 E 6 	*
 * COME PARAMETRO, RESTITUISCE IL 			*
 * CORRISPONDENTE GIORNO DELLA SETTIMANA	*/
char* indiceToGiorniSettimana(int giorno){
	switch(giorno){
		case 0: return "Lunedi";
		case 1: return "Martedi";
		case 2: return "Mercoledi";
		case 3: return "Giovedi";
		case 4: return "Venerdi";
		case 5: return "Sabato";
		case 6: return "Domenica";
		default: return "";
	}
}






/* FUNZIONE CHE CONVERTE UNA STRUTTURA DI TIPO DATA_ORA	*
 * NEL NUMERO DI GIORNI DALLLO 0 AC						*/
int getDataInGiorni(data_ora data){
	long int giorni;
	int anniBisest=data.Anno/4;
	giorni=data.Anno*365 + anniBisest;
	int i;
	for(i=0;i<data.Mese-1;i++){
		giorni+=GiorniMesi[i];
	}
	giorni+=data.Giorno;
	return giorni;
}






/* FUNZIONE CHE RESTITUISCE LA DIFFERENZA 	*
 * IN GIORNI TRA 2 DATE						*
 *
 * LA DATA2 DEVE ESSERE QUELLA PIU RECENTE	*/
int getDistanzaInGiorni(data_ora data1,data_ora data2,int delay){

	//converto la data1 in giorni dall'anno 0
	int Giorni1=getDataInGiorni(data1);
	int Giorni2=getDataInGiorni(data2);

	return Giorni2-Giorni1+delay;

}






/* FUNZIONE CHE DATA UNA DATA COME PARAMETRO	*
 * RITORNA IL NUMERO COMPRESO TRA 0 E 6			*
 * DEL GIORNO DELLA SETIMANA DELLA DATA			*/
int dataToGiorniSettimana(data_ora data){

	int giorni=getDataInGiorni(data);
	giorni=giorni % NUMERO_GIORNI + 4;
	giorni=giorni % NUMERO_GIORNI;

	switch(giorni){
		case 0: return 0;
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 4;
		case 5: return 5;
		case 6: return 6;
		default: return -1;
	}
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
int getDataInput(char *giorno,char *mese,int *anno,char messaggio[]){

	char data[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		puts(messaggio);
		fgets(data,LUNGHEZZA_STRINGA,stdin);

		if(!ControlloData(data,giorno,mese,anno)){
			printf("\nData errata!Reinseriscila!\n");
			flag=true;
		}

	}while(flag);

	return 1;

}



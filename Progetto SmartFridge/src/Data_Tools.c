/**
 *  @file Data_Tools.c
 *  @brief     File contenente le implementazioni delle funzioni definite in Data_Tools.h.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




#include <String.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tipi_Dato.h"


/**
 * Vettore di interi con FileScope per la memorizzazione dei giorni dei mesi
 * utilizzati dalle funzioni del file Data_Tools.c
 */
int giorniMesi[]={31,28,31,30,31,30,31,31,30,31,30,31};





/**
 * Se il valore interno passato come parametro corrisponde ad una anno valido
 * la funzione controllera' se quell'anno e' bisestile o meno.
 *
 * @pre gli anni che e' possibile controllare sono gli anni a partire dall'anno 0
 * del calendario Gregoriano.
 */
int is_bisestile(int anno){
	if((anno%4) == 0){
		if((anno%100) != 0) return 1;
		else{
			if((anno%400) ==0) return 1;
			else return 0;
		}
	}else return 0;
}







/**
 * La stringa dataN passata come parametro viene controllata per verificare se al suo interno
 * e' presente una data nel formato gg/MM/AAAA e se presente, ritorna la data corrispondente
 * nei puntatori passati come parametro.
 *
 * @pre *dataN,*giorno,*mese,*anno devono puntare ad una locazione di memoria valida ed ancora allocata.
 * @post La data viene controllata anche nei termini di giorni bisestili.
 */
int controllo_data(char *dataN,char *giorno,char *mese,int *anno){
    if(strchr(dataN,'/')!=0){     //controllo se all'interno del vettore c'e' uno /
        char *c;
        char Num[11];  //vettore che conterra'  il valore estrapolato per il giorno
        char Num1[11]; //vettore che conterra il valore estrapolato per il mese
        c=strchr(dataN,'/');      //assegno il puntatore di ritorno della funzione strchr alla variabile puntatore c
        strncpy(Num, dataN,strlen(dataN)-strlen(c));  //creo una copia di c fino all'occorrenza dello / in Num
        if((*giorno=to_number(Num))>0 && *giorno<31){        //richiamo la funzione ParsChatInt per convertire la stringa in intero e assegno il valore intero alla variabile punattore giorno
            if(strchr(c,'/')!=0){
                char *c1=strchr(c,'/')+1;
                if(strchr(c1,'/')!=0){         //controllo se c'e' un altro / all'interno del vettore di caratteri
                    char *c2=strchr(c1,'/');   //e assegno dal quella posizione in poi al puntatore c2
                    strncpy(Num1, c1,strlen(c1)-strlen(c2));  //mi creo una copia in maniera tale che Num1 contenga il valore del mese etrapolato dal vettore di caratteri
                    if((*mese=to_number(Num1))>0 && *mese<13){
                        *anno=atoi(strchr(c2,'/')+1);  //assegno al puntatore anno il valore intero dell'anno estrapolato dal vettore di caratteri
                        if(*anno!=0){
                        	//controllo se l'anno e' bisestile
                        	if(is_bisestile(*anno)) giorniMesi[1]=29;
                        	else giorniMesi[1]=28;

                        	if(*giorno<=giorniMesi[(*mese-1)]) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}









/**
 * Dato il carattere passato come parametro, la funzione restituisce
 * il corrispondente valore della data di sistema in fuso orario europeo(CEST).
 * anno: 					'Y'
 * mese: 					'M'
 * giorno: 					'D'
 * ora: 					'H'
 * minuti: 					'm'
 * secondi: 				's'
 * giorno della settimana: 	'W'
 *
 * @warning Se la data di sistema e' antecedente al 1900 i risultati potrebbero
 * essere non veritieri.
 */
int get_data(char tipoOutput){

   time_t rawtime;
   struct tm *info;

   time(&rawtime);
   /* Get GMT time */
   info = gmtime(&rawtime );

   switch(tipoOutput){
	   case CARATTERE_ANNO:
			return 1900 + (*info).tm_year;
	   case CARATTERE_GIORNO:
		   return (*info).tm_mday;
	   case CARATTERE_MESE:
		   return (*info).tm_mon+1;
	   case CARATTERE_ORA:
		   return ((*info).tm_hour+CEST)%24;
	   case CARATTERE_SECONDI:
		   return (*info).tm_sec;
	   case CARATTERE_MINUTI:
		   return (*info).tm_min;
	   case CARATTERE_GIORNO_SETTIMANA:
		   //devo fare questo perche con (*info).tm_wday mi ritorno il
		   //giorno della settimana con 0 la domenica invece
		   //a me serve avere 0 il lunedi e 6 la domenica.
		   if((*info).tm_wday == 0) return 6;
		   else return (*info).tm_wday-1;
   }

   return -1;

}




/**
 * Funzione che restituisce, all'interno di un puntatore di tipo data_ora, la data di sistema.
 *
 * @pre *data deve puntare ad una locazione di memoria valida ed ancora allocata.
 */
int get_data_pointer(data_ora* data){

   time_t rawtime;
   struct tm *info;

   time(&rawtime);
   /* Get GMT time */
   info = gmtime(&rawtime );


   (*data).Anno=1900 + (*info).tm_year;
   (*data).Giorno= (*info).tm_mday;
   (*data).Mese=(*info).tm_mon+1;

   (*data).Ora=((*info).tm_hour+CEST)%24;

   (*data).Minuti=(*info).tm_min;
   (*data).Secondi=(*info).tm_sec;

   return 1;

}





/**
 * In base all'orario di sistema, la funzione restituisce una stringa
 * con un augurio per il pasto.
 *
 * @warning Non e' garantito il corretto funzionamento se la data di sistema
 * non corrisponde a qualle reale o se e' minore del 1/01/1900.
 */
char* get_tipo_pasto(){
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





/**
 * In base al numero passato come parametro, la funzione
 * restituisce il giono della settimana corrispondente.
 *
 * @warning se il giorno passato come parametro non e' valido
 * la funzione restituisce una stringa vuota.
 */
char* indice_to_giorni_settimana(int giorno){
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






/**
 * Data la variabile di tipo data_ora come parametro, la funzione
 * restituisce il numero di giorni dall'anno 0 fino alla data
 * passata come parametro.
 * La funzione tiene conto anche degli anni bisestili.
 *
 * @pre data deve essere inizializzata altrimenti la funzione
 * potrebbe restituire valori errati.
 */
int get_data_in_giorni(data_ora data){
	long int giorni;
	int anniBisest=data.Anno/4;
	giorni=data.Anno*365 + anniBisest;
	int i;
	for(i=0;i<data.Mese-1;i++){
		giorni+=giorniMesi[i];
	}
	giorni+=data.Giorno;
	return giorni;
}






/**
 * Date le due date passate come parametro, la funzione le converte nel numero
 * di giorni dallo 0 DC e ritorna la distanza in giorni tra data2 e data1.
 * La data2 deve essere la data piu recente.
 *
 * @warning se data2 e antecedente la data1 il risultato sara negativo.
 */
int get_distanza_in_giorni(data_ora data1,data_ora data2,int delay){

	//converto la data1 in giorni dall'anno 0
	int giorni1=get_data_in_giorni(data1);
	int giorni2=get_data_in_giorni(data2);

	return giorni2-giorni1+delay;

}






/**
 * Data la data come parametro, la funzione ritorna il giorno
 * della settimana compreso tra 0 e 6 a cui fa riferimento.
 *
 * @param[in] data data di cui si vuole sapere il giorno della settimana.
 * @return un numero tra 0 e 6, estremi inclusi, in base alla data.
 */
int data_to_giorni_settimana(data_ora data){

	int giorni=get_data_in_giorni(data);
	giorni=giorni % NUMERO_GIORNI + 4;
	giorni=giorni % NUMERO_GIORNI;

	return (giorni>=1 && giorni<=7) ? giorni : -1;

}










/**
 * La funzione chiede in console, all'utente, di inserire una data che viene
 * controllata e, se corretta, i valori della data vengono inseriti nei
 * puntantori passati come parametro.
 * Il messaggio da visualizzare all'utente viene anche esso passato come parametro.
 *
 * @pre *giorno,*mese,*anno devono puntare a locazioni di memoria valide ed ancora allocate.
 * @pre messaggio[] non deve essere vuoto in quanto altrimenti la funzione si mettera'
 * in attesa senza avvisare l'utente.
 */
int get_data_input(char *giorno,char *mese,int *anno,char messaggio[]){

	char data[LUNGHEZZA_STRINGA];
	boolean flag;

	do{
		flag=false;
		puts(messaggio);
		fgets(data,LUNGHEZZA_STRINGA,stdin);

		if(!controllo_data(data,giorno,mese,anno)){
			printf("\nData errata!Reinseriscila!\n");
			flag=true;
		}

	}while(flag);

	return 1;

}





/**
 * Le due date passate come parametro vengono confrontate tra di loro
 * per capire quale delle due e' la piu recente.
 *
 * @pre la due date devono essere delle date reali e quindi
 * non devono avere attributi negativi o altro di sbagliato.
 *
 * @warning non e' garantito il corretto funzionamento per date
 * precedenti l'anno 0.
 */
int data_compare(data_ora data1, data_ora data2){
	int distanza = get_distanza_in_giorni(data1,data2,0);
	if(distanza > 0) return 1;
	else if(distanza < 0) return -1;
	else{
		//distanza in giorni uguale a zero cioe le date sono nello
		//stesso giorno; bisogna controllare l'ora, minuti e secondi

		if(data1.Ora < data2.Ora) return 1;
		else if(data1.Ora > data2.Ora) return -1;
		else if(data1.Minuti < data2.Minuti) return 1;
		else if(data1.Minuti > data2.Minuti) return -1;
		else if(data1.Secondi < data2.Secondi) return 1;
		else if(data1.Secondi > data2.Secondi) return -1;
		else return 0;

	}
}



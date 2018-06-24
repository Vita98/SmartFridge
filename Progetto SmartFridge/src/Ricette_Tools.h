/*
 * Ricette_Tools.h
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#ifndef RICETTE_TOOLS_H_
#define RICETTE_TOOLS_H_


int scelta_opzioni_ricette(ricetta[],int,alimento[],int,int*);

int visualizza_ricette_ordinate(ricetta[], int);

int visualizza_ricette(ricetta[], int);

int scelta_visualizzazione_ricette(ricetta[], int);

int cancella_ricetta(ricetta[],int);

int get_ricetta(ricetta[],int,char[],boolean);

int modifica_ricetta_su_file(ricetta);

int modifica_ricetta(ricetta[],int,alimento[],int);

int modifica_nome_ricetta(ricetta[],int,int);

int modifica_kcalporzione_ricetta(ricetta[],int);




int modifica_alimenti_ricetta(ricetta[],int,alimento[],int);

int visualizza_alimenti_ricetta(ricetta[],int,alimento[],int);

int inserimento_alimento_ricetta(ricetta[],int,alimento[],int);

int salva_alimento_in_ricetta(ricetta * ,int ,int );

int get_alimento_ricetta(ricetta[],int,int);

int cancellazione_alimento_ricetta(ricetta[],int,alimento[],int);

int modifica_quantita_alimento_ricetta(ricetta[],int,alimento[],int);

int get_numero_porzioni_possibili_ricetta(ricetta[],int,alimento[],int,int);

int consuma_ricetta_su_alimenti(ricetta[],int,alimento[],int,int,int);

int inserimento_ricetta(alimento[],int,ricetta[],int,int*);


#endif /* RICETTE_TOOLS_H_ */

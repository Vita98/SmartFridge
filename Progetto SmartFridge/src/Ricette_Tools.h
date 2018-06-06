/*
 * Ricette_Tools.h
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#ifndef RICETTE_TOOLS_H_
#define RICETTE_TOOLS_H_


int Scelta_Opzioni_Ricette(ricetta[],int,alimento[],int);

int Visualizza_Ricette(ricetta[], int);


int Modifica_Ricette(ricetta[],int);

int Scelta_Visualizzazione(ricetta[], int);

int Sort_Merge_Kcal(int, int, ricetta[], double[]);

int Merging_Kcal(int, int, int, ricetta[], double[]);

int Ordina_Ricette(ricetta[],char[],int[],int);

int Cancella_Ricetta(ricetta[],int);

int getRicetta(ricetta[],int,char[],boolean);

int Modifica_Ricetta_Su_File(ricetta);

int Modifica_Ricetta(ricetta[],int,alimento[],int);

int Modifica_Nome_Ricetta(ricetta[],int,int);

int Modifica_kcalPorzione_Ricetta(ricetta[],int);

int Sort_Ricette (ricetta[], int[], int, int);

int Merge_Sort_Ricette(ricetta[], int, int, int, int);

int Merging_Ricette(ricetta[], int, int, int, int, int);



int Modifica_Alimenti_Ricetta(ricetta[],int,alimento[],int);

int Visualizza_Alimenti_Ricetta(ricetta[],int,alimento[],int);

int Inserimento_Alimento_Ricetta(ricetta[],int,alimento[],int);

int Salva_Alimento_In_Ricetta(ricetta * ,int ,int );

int getAlimentoRicetta(ricetta[],int,int);

int Cancellazione_Alimento_Ricetta(ricetta[],int,alimento[],int);

int Modifica_Quantita_Alimento_Ricetta(ricetta[],int,alimento[],int);

#endif /* RICETTE_TOOLS_H_ */

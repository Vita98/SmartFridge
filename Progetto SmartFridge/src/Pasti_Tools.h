/*
 * Pasti_Tools.h
 *
 *  Created on: 06 giu 2018
 *      Author: My-PC
 */

#ifndef PASTI_TOOLS_H_
#define PASTI_TOOLS_H_


int Scelta_Opzioni_Pasti(ricetta[],int,alimento[],int);

int Aggiungi_Pasto(ricetta[],int,alimento[],int);

int Aggiungi_Pasto_Su_File(int,int);

int Scelta_Opzioni_Visualizza_Menu_Settimanale(ricetta [],int );

int Visualizza_Menu_Settimana_In_Corso(ricetta [],int );

int Visualizza_Menu_Settimane_Passate(ricetta[],int);

int Stampa_Iesimo_Menu_Settimanale(ricetta[],int,int,int);

int Visualizza_File_Pasti(ricetta[]);

int Cancella_Pasto(ricetta[],int,alimento[]);

int Cancella_Iesimo_Pasto_Da_File(int indice,alimento[],ricetta[]);


#endif /* PASTI_TOOLS_H_ */

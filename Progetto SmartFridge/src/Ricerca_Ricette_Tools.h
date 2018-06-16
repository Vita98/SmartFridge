/*
 * Ricerca_Ricette_Tools.h
 *
 *  Created on: 09 giu 2018
 *      Author: My-PC
 */

#ifndef RICERCA_RICETTE_TOOLS_H_
#define RICERCA_RICETTE_TOOLS_H_

int ricerca_ricette_per_alimenti(ricetta[],int,alimento[],int);

boolean is_parametro_ricerca(int[],int,int);

int* get_ricette_per_alimenti(alimento[],int,int[],int,ricetta[],int,int*);

int suggerimento_ricette_in_scadenza(ricetta[],int,alimento[],int);

int* get_ricette_in_scadenza(ricetta[],int,alimento[],int,int*);

#endif /* RICERCA_RICETTE_TOOLS_H_ */

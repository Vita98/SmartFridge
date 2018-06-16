/*
 * Pasti_Tools.h
 *
 *  Created on: 06 giu 2018
 *      Author: My-PC
 */

#ifndef PASTI_TOOLS_H_
#define PASTI_TOOLS_H_


int scelta_opzioni_pasti(ricetta[],int,alimento[],int);

int aggiungi_pasto(ricetta[],int,alimento[],int);

int aggiungi_pasto_su_file(int,int);

int scelta_opzioni_visualizza_menu_settimanale(ricetta [],int );

int visualizza_menu_settimana_in_corso(ricetta [],int );

int visualizza_menu_settimane_passate(ricetta[],int);

int stampa_iesimo_menu_settimanale(ricetta[],int,int,int);

int visualizza_file_pasti(ricetta[]);

int cancella_pasto(ricetta[],int,alimento[]);

int cancella_iesimo_pasto_da_file(int,alimento[],ricetta[]);

int get_numero_settimane(int);

#endif /* PASTI_TOOLS_H_ */

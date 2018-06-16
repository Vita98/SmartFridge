/*
 * Preferiti_Tools.h
 *
 *  Created on: 06 giu 2018
 *      Author: giutu
 */

#ifndef PREFERITI_TOOLS_H_
#define PREFERITI_TOOLS_H_

boolean controllo_preferiti(ricetta[], int, char[], int*);

int aggiungi_preferito(ricetta[],int);

int visualizza_preferiti(ricetta[]);

int cancella_preferito(ricetta[],int);

int scelta_opzioni_preferiti(ricetta[],int);

boolean exist_preferito(ricetta[], int*);


#endif /* PREFERITI_TOOLS_H_ */

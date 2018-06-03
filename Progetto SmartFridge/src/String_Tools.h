/*
 * String_Tools.h
 *
 *      Author: Vitandrea Sorino
 */

#ifndef STRING_TOOLS_H_
#define STRING_TOOLS_H_

int isNumber(char[]);

int toNumber(char[]);

int FaiScelta(char[]);

int explodeString(char [],char[MASSIME_STRINGHE_ESPLOSE][LUNGHEZZA_STRINGA]);

int removeFirstLastSpace(char[],char[],int);

int toLowerString(char[],char[]);

int isDouble(char[]);

double FaiSceltaDouble(char[]);

boolean FaiSceltaBooleana(char[]);

#endif /* STRING_TOOLS_H_ */


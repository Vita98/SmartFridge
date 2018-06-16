/*
 * String_Tools.h
 *
 *      Author: Vitandrea Sorino
 */

#ifndef STRING_TOOLS_H_
#define STRING_TOOLS_H_

int is_number(char[]);

int to_number(char[]);

int fai_scelta(char[]);

int explode_string(char [],char[MASSIME_STRINGHE_ESPLOSE][LUNGHEZZA_STRINGA]);

int remove_first_last_space(char[],char[],int);

int to_lower_string(char[],char[]);

int is_double(char[]);

double fai_scelta_double(char[]);

boolean fai_scelta_booleana(char[]);

#endif /* STRING_TOOLS_H_ */


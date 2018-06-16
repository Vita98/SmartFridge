/*
 * Data_Tools.h
 *
 *  Created on: 29 mag 2018
 *      Author: My-PC
 */

#ifndef DATA_TOOLS_H_
#define DATA_TOOLS_H_

int controllo_data(char*,int*,int*,int*);

int get_data(char);

int get_data_input(char*,char*,int*,char[]);

int get_data_pointer(data_ora*);

char* get_tipo_pasto();

int is_bisestile(int);

int get_distanza_in_giorni(data_ora,data_ora,int);

int get_data_in_giorni(data_ora );

char* indice_to_giorni_settimana(int);

int data_to_giorni_settimana(data_ora);

#endif /* DATA_TOOLS_H_ */

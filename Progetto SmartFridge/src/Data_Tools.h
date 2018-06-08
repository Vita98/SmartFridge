/*
 * Data_Tools.h
 *
 *  Created on: 29 mag 2018
 *      Author: My-PC
 */

#ifndef DATA_TOOLS_H_
#define DATA_TOOLS_H_

int ControlloData(char*,int*,int*,int*);

int getData(char);

int getDataInput(char*,char*,int*,char[]);

int getData2(data_ora*);

char* getTipoPasto();

int isBisestile(int);

int getDistanzaInGiorni(data_ora,data_ora,int);

int getDataInGiorni(data_ora );

char* indiceToGiorniSettimana(int);

int dataToGiorniSettimana(data_ora);

#endif /* DATA_TOOLS_H_ */

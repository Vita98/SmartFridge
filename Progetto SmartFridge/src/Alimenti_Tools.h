/*
 * Alimenti_Tools.h
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#ifndef ALIMENTI_TOOLS_H_
#define ALIMENTI_TOOLS_H_

int getAlimento(alimento[],int,char[],boolean);

int Scelta_Opzioni_Alimenti(alimento[],int);

int Visualizza_Alimenti(alimento[],int);

int Modifica_Alimento(alimento[],int);

int getQuantita (alimento);

int Modifica_Nome_Alimento(alimento[],int,int[]);

int Modifica_Alimento_Su_File(alimento );

int Modifica_kcal_Alimento(alimento[],int);

int Modifica_Peso_Alimento(alimento[],int );

int Modifica_Quantita_Alimento(alimento[],int);

int Modifica_Scadenze_Alimento(alimento[],int );

int Visualizza_Quantita_Scadenze(alimento[],int);

int getDataScadenza(alimento,data_ora);

int Aggiungi_Alimento_Su_File(alimento);

int decrementa_Quantita_Alimento(alimento*, int);


#endif /* ALIMENTI_TOOLS_H_ */

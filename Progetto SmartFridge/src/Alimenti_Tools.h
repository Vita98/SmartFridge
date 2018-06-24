/*
 * Alimenti_Tools.h
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#ifndef ALIMENTI_TOOLS_H_
#define ALIMENTI_TOOLS_H_

int get_alimento(alimento[],int,char[],boolean);

int scelta_opzioni_alimenti(alimento[],int);

int visualizza_alimenti(alimento[],int);

int modifica_alimento(alimento[],int);

int get_quantita (alimento);

int modifica_nome_alimento(alimento[],int,int[]);

int modifica_alimento_su_file(alimento );

int modifica_kcal_alimento(alimento[],int);

int modifica_peso_alimento(alimento[],int );

int modifica_quantita_alimento(alimento[],int);

int modifica_scadenze_alimento(alimento[],int );

int visualizza_quantita_scadenze(alimento[],int);

int get_data_scadenza(alimento,data_ora);

int aggiungi_alimento_su_file(alimento);

int decrementa_quantita_alimento(alimento*, int);

int scelta_visualizzazione_alimenti(alimento alimenti[],int lunghezzaVettoreAlimenti);

int visualizza_alimenti_ordinati(alimento alimenti[],int lunghezzaVettoreAlimenti, int modalitaOrdinamento);


#endif /* ALIMENTI_TOOLS_H_ */

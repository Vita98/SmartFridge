/*
 * Gen_File.h
 *
 *  Created on: 17 mag 2018
 *      Author: My-PC
 */

#ifndef GEN_FILE_H_
#define GEN_FILE_H_

void Generazione_Alimenti();

void Read_Alimenti();

void Genera_Ricette();

void Visualizza_RicetteF();

void Carica_Configurazione();

int Carica_Alimenti(alimento alimenti[]);

int Get_Lunghezza_File_Alimenti();

int Carica_Ricette(ricetta[]);

int Get_Lunghezza_File_Ricette();

int Get_Lunghezza_File_Storico_Pasti();

#endif /* GEN_FILE_H_ */


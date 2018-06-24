/*
 * Ordinamenti_Tools.c
 *
 *  Created on: 22 giu 2018
 *      Author: My-PC
 */
#include "Tipi_Dato.h"
#include "Preferiti_Tools.h"




/*	FUNZIONE CHE PERMETTE DI DIVIDERE IL VETTORE RICETTE OTTENUTO IN SOTTOVETTORI E CONFRONTARE I 		*
 *  SINGOLI ELEMENTI PER POI SCRIVERE IL PROPRIO INDICE IN UN NUOVO VETTORE DI LUNGHEZZA PARI A QUELLO 	*
 *  ANALIZZATO OTTENENDO UN VETTORE DI INTERI FORMATO DA INDICI, IL CONETUNO DEGLI ELEMENTI E' 			*
 *  EQUIVALENTI ALL'ORDINAMENTO CRESCENTE DEGLI ELEMENTI DEL VETTORE RICETTE, LE SCELTE SONO DECISE 	*
 *  DALLA MODALITA IN CUI SI DECIDE ORDINARE LE RICETTE 												*
 *  																									*
 *  MODALITA 2 = ORDINAMENTO PER KCAL																	*
 *  MODALITA 3 = ORDINAMENTO PER FREQUENZA																*
 *  MODALITA 4 = ORDINAMENTO PER PREFERITI CIOE VENGONO PORTATI IN ALTO I PREFERITI E NELLO STESSO 		*
 *  TEMPO I PREFERITI VENGONO ORDINATI PER FREQUENZA DI USO												*/
int merging_ricette(ricetta ricette[], int inizio, int medio, int fine, int index[], int modalitaOrdinamento)
{
    int i, j, k;
    int n1 = medio - inizio + 1;
    int n2 =  fine - medio;

    // create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = index[inizio + i];
    for (j = 0; j < n2; j++)
        R[j] = index[medio + 1+ j];

    // Merge the temp arrays back into arr[inizio..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = inizio; // Initial index of merged subarray

    if (modalitaOrdinamento == MODALITA_ORDINAMENTO_KCAL_PORZIONE){
    	while (i < n1 && j < n2)
		{
			if (ricette[L[i]].Kcal_Porzione < ricette[R[j]].Kcal_Porzione)
			{
				index[k] = L[i];
				i++;
			}
			else
			{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }else if(modalitaOrdinamento == MODALITA_ORDINAMENTO_FREQUENZA){
    	while (i < n1 && j < n2)
		{
			if (ricette[L[i]].Frequenza > ricette[R[j]].Frequenza)
			{
				index[k] = L[i];
				i++;
			}
			else
			{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }else if(modalitaOrdinamento == MODALITA_ORDINAMENTO_PREFERITI){
    	while (i < n1 && j < n2)
		{
			if ((exist_preferito(ricette,&L[i]) == true) && (exist_preferito(ricette,&R[j]) == false))
			{
				index[k] = L[i];
				i++;
			}
			else if((exist_preferito(ricette,&L[i]) == true) && (exist_preferito(ricette,&R[j]) == true)){
				if(ricette[L[i]].Frequenza > ricette[R[j]].Frequenza){
					index[k] = L[i];
					i++;
				}
			}else
			{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }


    // Copy the remaining elements of L[], if there  are any
    while (i < n1)
    {
        index[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any*/
    while (j < n2)
    {
        index[k] = R[j];
        j++;
        k++;
    }

    return 1;
}








/* FUNZIONE CHE DIVIDE IL VETTORE DI RICETTE IN PIU SOTTO VETTORI E NE APPLICA IL MERGE  */
int merge_sort_ricette(ricetta ricette[], int inizio, int fine,int index[], int modalitaOrdinamento){

    if (inizio < fine)
    {
        // Same as (inizio+fine)/2, but avoids overflow for
        // large inizio and h
        int m = inizio+(fine-inizio)/2;

        // Sort first and second halves
        merge_sort_ricette(ricette, inizio, m,index,modalitaOrdinamento);
        merge_sort_ricette(ricette, m+1, fine,index,modalitaOrdinamento);

        merging_ricette(ricette, inizio, m, fine,index,modalitaOrdinamento);
        return 0;
    }
    return 1;
}




/* FUNZIONE CHE RICHIAMA IL MERGE SORT APPLICATO PASSANDO I PARAMETRI NECESSARI   */
int sort_ricette (ricetta ricette[],int index[], int lunghezzaVettore, int modalitaOrdinamento){

	int i;
	for (i=0;i<lunghezzaVettore;i++){
		index[i] = ricette[i].ID_Ricetta;
	}

	merge_sort_ricette(ricette,0,lunghezzaVettore-1,index,modalitaOrdinamento);
	return 1;
}




int merging_alimenti(alimento alimenti[], int inizio, int medio, int fine, int index[], int modalitaOrdinamento)
{
    int i, j, k;
    int n1 = medio - inizio + 1;
    int n2 =  fine - medio;

    // create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = index[inizio + i];
    for (j = 0; j < n2; j++)
        R[j] = index[medio + 1+ j];

    // Merge the temp arrays back into arr[inizio..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = inizio; // Initial index of merged subarray

    if (modalitaOrdinamento == MODALITA_ORDINAMENTO_KCAL_PORZIONE){
    	while (i < n1 && j < n2)
		{
			if (alimenti[L[i]].Kcal_Pezzo < alimenti[R[j]].Kcal_Pezzo)
			{
				index[k] = L[i];
				i++;
			}
			else
			{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }else if(modalitaOrdinamento == MODALITA_ORDINAMENTO_FREQUENZA){
    	while (i < n1 && j < n2)
		{
			if (alimenti[L[i]].Utilizzo > alimenti[R[j]].Utilizzo)
			{
				index[k] = L[i];
				i++;
			}
			else
			{
				index[k] = R[j];
				j++;
			}
			k++;
		}
    }


    // Copy the remaining elements of L[], if there  are any
    while (i < n1)
    {
        index[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any*/
    while (j < n2)
    {
        index[k] = R[j];
        j++;
        k++;
    }

    return 1;
}





/* FUNZIONE CHE DIVIDE IL VETTORE DI RICETTE IN PIU SOTTO VETTORI E NE APPLICA IL MERGE  */
int merge_sort_alimenti(alimento alimenti[], int inizio, int fine,int index[], int modalitaOrdinamento){

    if (inizio < fine)
    {
        // Same as (inizio+fine)/2, but avoids overflow for
        // large inizio and h
        int m = inizio+(fine-inizio)/2;

        // Sort first and second halves
        merge_sort_alimenti(alimenti, inizio, m,index,modalitaOrdinamento);
        merge_sort_alimenti(alimenti, m+1, fine,index,modalitaOrdinamento);

        merging_alimenti(alimenti, inizio, m, fine,index,modalitaOrdinamento);
        return 0;
    }
    return 1;
}






/* FUNZIONE CHE RICHIAMA IL MERGE SORT APPLICATO PASSANDO I PARAMETRI NECESSARI   */
int sort_alimenti (alimento alimenti[],int index[], int lunghezzaVettore, int modalita){

	int i;
	for (i=0;i<lunghezzaVettore;i++){
		index[i] = alimenti[i].ID_Alimento;
	}

	merge_sort_alimenti(alimenti,0,lunghezzaVettore-1,index,modalita);
	return 1;
}

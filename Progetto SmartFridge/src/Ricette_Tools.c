/*
 * Ricette_Tools.c
 *
 *  Created on: 22 mag 2018
 *      Author: My-PC
 */

#include "Tipi_Dato.h"
#include <String.h>


int Merging_Kcal(int inizio, int medio, int fine, ricetta a[], double b[]) {
   int l1, l2, i;

   for(l1 = inizio, l2 = medio + 1, i = inizio; l1 <= medio && l2 <= fine; i++) {
      if(a[l1].Kcal_Porzione <= a[l2].Kcal_Porzione)
         b[i] = a[l1++].Kcal_Porzione;
      else
         b[i] = a[l2++].Kcal_Porzione;
   }

   while(l1 <= medio)
      b[i++] = a[l1++].Kcal_Porzione;

   while(l2 <= fine)
      b[i++] = a[l2++].Kcal_Porzione;

   for(i = inizio; i <= fine; i++){
	    a[i].Kcal_Porzione = b[i];
   printf ("a: %.2f b: %.2f  |",a[i].Kcal_Porzione , b[i]);
   }

   printf("\n");

   return 1;
}



int Sort_Merge_Kcal(int inizio, int fine, ricetta a[], double b[]) {
   int medio;

   if(inizio < fine) {
      medio = (inizio + fine) / 2;
      Sort_Merge_Kcal(inizio, medio,a,b);
      Sort_Merge_Kcal(medio+1, fine,a,b);

      Merging_Kcal(inizio, medio, fine, a, b);
      return 0;
   } else {
      return 1;
   }
}




int Visualizza_Ricette(ricetta ricette[], int Lunghezza_Vettore) {

	int i;

	double vett_appoggio[Lunghezza_Vettore];

	printf("Ricette presenti");
	printf ("%d :\n",Lunghezza_Vettore);

	Sort_Merge_Kcal(0,Lunghezza_Vettore-1,ricette,vett_appoggio);

	for (i = 0; i <Lunghezza_Vettore -1 ; i++) {


			printf("%d - %s \t| Kcal per porzione: %.2f \t| Id: %d  \t| freq: %d \n", i,
					ricette[i].Nome, ricette[i].Kcal_Porzione,
					ricette[i].ID_Ricetta,ricette[i].Frequenza);


	}
	return 1;
}





int Scelta_Visualizzazione(ricetta ricette[],int lunghezza_vettore_ricette){


	int NumScelta;

		do {
			NumScelta = FaiScelta(MENU_VISUALIZZA_ALIMENTI);

			switch (NumScelta) {

			case 1:
				//ordina per kcal
				Visualizza_Ricette(ricette,lunghezza_vettore_ricette);
				break;

			case 2:
				//ordina per frequenza
				break;

			default:
				printf("Scelta errata! Riprova!\n");

			}
		}while(NumScelta != 0);

		return 0;


}






int Scelta_Opzioni_Ricette(ricetta ricette[], int lunghezza_vettore_ricette) {

	int NumScelta;

	do {
		NumScelta = FaiScelta(MenuRicette);

		switch (NumScelta) {
		case 1:

			//viualizza lista ricette

			Scelta_Visualizzazione(ricette, lunghezza_vettore_ricette);
			break;
		case 2:

			//aggiungi ricetta

			break;
		case 3:

			//modifica ricetta

			break;
		case 4:

			//cancella ricetta

			break;
		case 0:
			//case di uscita dal sottomenu
			break;
		default:
			printf("Scelta errata! Riprova!\n");
		}

	} while (NumScelta != 0);

	return 0;
}

/*
 ============================================================================
 Name        : Progetto.c
 Author      : Vitandrea Sorino
 Version     :
 Copyright   : Your copyright notice
 Description : Hel1lo World in C, Ansi-style
 ============================================================================
 */




/**
 * @mainpage Documentazione progetto "Smart Fridge" sviluppato da Vitandrea Sorino e Giuseppe Tutino
 *
 * \section intro_sec Introduzione
 *
 * Inserire l'introduzione del progetto
 *
 * \section install_sec Installation
 *
 * This is a section.
 *
 * \subsection step1 Step 1: Opening the box
 *
 * This is a subsection
 */




#include "Tipi_Dato.h"
#include "Caricamento_Vettori_Tools.h"
#include "Ricette_Tools.h"
#include "Alimenti_Tools.h"
#include "Lista_Spesa_Tools.h"
#include "Spesa_Tools.h"
#include "Data_Tools.h"
#include "Pasti_Tools.h"
#include "Ricerca_Ricette_Tools.h"
#include <time.h>

void genera_consumazioni_pasti(alimento alimenti[],int lunghezzaAlimenti,ricetta ricette[],int lunghezzaRicette);
void genera_acquisto_spesa(alimento alimenti[],int lunghezzaAlimenti);

void pressToContinue();

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	int numScelta;

	//creazione e caricamento del vettore di alimenti
	int lunghezzaVettoreAlimenti = Get_Lunghezza_File_Alimenti();
	alimento *alimenti=(alimento*) calloc(lunghezzaVettoreAlimenti,sizeof(alimento));
	Carica_Alimenti(alimenti);


	//creazione e caricamento del vettore di ricette
	int lunghezzaVettoreRicette=Get_Lunghezza_File_Ricette();
	ricetta *ricette=(ricetta*) calloc(lunghezzaVettoreRicette,sizeof(ricetta));
	Carica_Ricette(ricette);


	//Caricamento delle impostazioni dal file di configurazione
	Carica_Configurazione();

	visualizza_storico_spesa(alimenti,lunghezzaVettoreAlimenti);
	visualizza_file_pasti(ricette);

	/*pasto pp;
	pp=leggi_iesimo_pasto(1);
	if(pp.ID_Ricetta == 2){
		pp.Porzioni=1;
		modifica_iesimo_pasto_su_file(pp,1);
	}*/


	visualizza_alimenti(alimenti,lunghezzaVettoreAlimenti);
	visualizza_ricette(ricette,lunghezzaVettoreRicette);


	//genera_consumazioni_pasti(alimenti,lunghezzaVettoreAlimenti,ricette,lunghezzaVettoreRicette);
	//genera_acquisto_spesa(alimenti,lunghezzaVettoreAlimenti);


	int nuovoIndirizzoAlimenti;
	int nuovoIndirizzoRicette;
	printf("Benvenuto in SMARTFRIDGE\n");
	do {

		numScelta = fai_scelta(MENU_PRINCIPALE);

		switch (numScelta) {
		case 1:		//Suggerimento spesa

			scelte_spesa(alimenti,lunghezzaVettoreAlimenti);

			break;

		case 2:		//Suggerimento Ricette

			suggerimento_ricette_in_scadenza(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;

		case 3:		//Ricerca Ricette per alimento

			ricerca_ricette_per_alimenti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);


			break;
		case 4:		//Opzioni Alimenti

			scelta_opzioni_alimenti(alimenti,lunghezzaVettoreAlimenti);

			break;
		case 5:		//Opzioni Ricette

			lunghezzaVettoreRicette=scelta_opzioni_ricette(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,&nuovoIndirizzoRicette);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di una nuovo ricetta
			ricette=(ricetta *)nuovoIndirizzoRicette;

			break;
		case 6:		//Opzioni Pasti

			scelta_opzioni_pasti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;

		case 7: //Inserisci Spesa


			lunghezzaVettoreAlimenti=scelta_opzioni_spesa(alimenti,lunghezzaVettoreAlimenti,&nuovoIndirizzoAlimenti);

			//aggiorno il vettore con quello nuovo nel caso c'è stata l'aggiunta di un nuovo alimento
			alimenti=(alimento *)nuovoIndirizzoAlimenti;


			break;

		case 8:
			break;

		default:
			printf("\nScelta non valida!\n");
		}

	} while (numScelta != 8);

	//system("pause");

	return 0;
}



void genera_consumazioni_pasti(alimento alimenti[],int lunghezzaAlimenti,ricetta ricette[],int lunghezzaRicette){
	srand(time(NULL));

	int idRicettaDaConsumare;
	int porzioniDaConsumare;
	int porzioniPossibili;
	int day=1;

	int i;
	for(i=0;i<10;i++){

		do{

			idRicettaDaConsumare = rand() % lunghezzaRicette;

			porzioniDaConsumare = 1 + (rand() % 3);

			porzioniPossibili=get_numero_porzioni_possibili_ricetta(ricette,lunghezzaRicette,alimenti,lunghezzaAlimenti,idRicettaDaConsumare);

		}while(porzioniPossibili == 0 || porzioniDaConsumare > porzioniPossibili);

		//incremento la frequenza del pasto
		ricette[idRicettaDaConsumare].Frequenza+=porzioniDaConsumare;
		modifica_ricetta_su_file(ricette[idRicettaDaConsumare]);

		//decremento le quantita di alimenti utilizzate nel vettore alimenti
		consuma_ricetta_su_alimenti(ricette,lunghezzaRicette,alimenti,lunghezzaAlimenti,idRicettaDaConsumare,porzioniDaConsumare);

		FILE *file;
		pasto pp;


		pp.ID_Ricetta=idRicettaDaConsumare;
		pp.Porzioni=porzioniDaConsumare;
		pp.visibilita=true;

		get_data_pointer(&pp.Data_Ora);
		day += 1+(rand() % 2);
		pp.Data_Ora.Giorno = day;
		pp.Data_Ora.Mese = 1;

		if ((file = fopen("src/Storico_Pasti.sf", "ab+")) == NULL) {
				printf("Errore nell'apertura del file!\n");
		} else {
			fwrite(&pp,sizeof(pasto),1,file);

			fclose(file);
		}
	}


}




void genera_acquisto_spesa(alimento alimenti[],int lunghezzaAlimenti){
	FILE *fileStoricoSpesa;
	elemento_spesa elemento;

	int indiciUsati[lunghezzaAlimenti];
	int contIndici=0;

	srand(time(NULL));

	int j;
	int day=1;
	for(j=0;j<15;j++){
		get_data_pointer(&elemento.Data_Ora);

		elemento.Data_Ora.Anno=2018;
		elemento.Data_Ora.Mese=2;
		day +=1 + (rand() % 2);
		day=3;
		elemento.Data_Ora.Giorno=day;




		elemento.Quantita=1 + (rand() % 16);

		boolean flag;

		do{
			flag=false;
			int i;

			elemento.ID_Alimento = rand() % lunghezzaAlimenti;

			for(i=0;i<contIndici;i++){
				if(indiciUsati[i] == elemento.ID_Alimento){
					flag=true;
					break;
				}
			}
		}while(flag == true);

		indiciUsati[contIndici]= elemento.ID_Alimento;
		contIndici++;
		alimenti[elemento.ID_Alimento].Scadenze[0].Quantita+=elemento.Quantita;
		alimenti[elemento.ID_Alimento].Scadenze[0].Data_Scadenza.Anno =2018+ rand() % 3;
		alimenti[elemento.ID_Alimento].Scadenze[0].Data_Scadenza.Mese = 1+rand()%11;
		alimenti[elemento.ID_Alimento].Scadenze[0].Data_Scadenza.Giorno= 1 + rand()%20;
		alimenti[elemento.ID_Alimento].Scadenze[0].Data_Scadenza.Minuti=0;
		alimenti[elemento.ID_Alimento].Scadenze[0].Data_Scadenza.Secondi = 0;
		alimenti[elemento.ID_Alimento].Scadenze[0].Data_Scadenza.Ora = 0;
		alimenti[elemento.ID_Alimento].Visibilita = true;

		modifica_alimento_su_file(alimenti[elemento.ID_Alimento]);

		if ((fileStoricoSpesa = fopen("src/Storico_Spesa.sf", "ab+")) != NULL)
		{

			fwrite(&elemento,sizeof(elemento_spesa),1,fileStoricoSpesa);

			fclose(fileStoricoSpesa);
		}
	}

}




/*FUNZIONE CHE SI METTE IN ATTESA CHE   *
 *L'UTENTE PREMA QUALCHE TASTO			*/
void pressToContinue() {
	printf("Premi per continuare....");
	getchar();
	system("cls");
}


/**
 *  @file 	   "Progetto SmartFridge.c"
 *  @brief     File contenente la funzione principale del programma cioe' il main().
 *
 *  @details   All'interno del main e' presente l'inclusione di tutte le librerie che servono
 *  		   al corretto funzionamento e avviene inoltre il caricamento iniziale dei dati dai vari file.
 *  		   Viene anche visualizzato e gestito tutto il menu principale con i vari richiami.
 *  		   ad altre funzioni per svolgere le funzionalita' del programma.
 *  @author    Vitandrea Sorino.
 *  @author    Giuseppe Tutino.
 *  @version   1.0.
 *  @date      18/06/2018.
 *  @copyright GNU Public License.
 */




/**
 * @mainpage Documentazione del progetto "Smart Fridge" dei laureandi Sorino Vitandrea e Tutino Giuseppe
 *
 * \section sezione_intro Descrizione del Sistema
 *
 * La soluzione proposta simula i comportamenti di quello che viene nominato "Frigo Intelligente", ossia un elettrodomestico in grado di
 * tenere traccia degli alimenti contenuti al suo interno, registrare i piatti preparati durante la giornata (e in un arco di tempo
 * maggiore, es. settimanalmente e mensilmente) e allo stesso tempo deve saper interagire con l'utente, rendendo piu' semplice il suo utilizzo.\n
 * Quando il programma viene eseguito dal frigorifero, carica in memoria tutte le informazioni necessarie per il suo corretto funzionamento: prima di tutto
 * la lista degli alimenti conosciuti, successivamente le ricette e le impostazioni personalizzate del gruppo di utenti.\n
 * Lo Smart Fridge e' pensato per rispondere alle esigenze di una famiglia, senza differenziare i membri della stessa in quanto non si dispone di stumenti
 * avanzati di riconoscimento immediato di un componente (riconoscimento facciale o impronta digitale).\n
 * L'unico strumento a disposizione e' un pannello touch con una tastiera virtuale che renderebbe il riconoscimento degli utenti, tramite l'inserimento di
 * credenziali, lento e macchinoso.\n
 * Sul pannello touch dello Smart Fridge e' possibile accedere a tutte le funzionalita' messe a dsposizione come la visualizzazione, senza l'apertura del frigo,
 * degli alimenti presenti e delle ricette, il tutto con degli opportuni filtri (ricette preferite, ricette/alimenti piu' frequentemente usati, ricette che fanno
 * uso di alimenti in scadenza).\n
 * Queste visualizzazioni vengono ordinate in base alle abitudini familiari (se la maggior parte dei componenti della famiglia consuma una determinata ricetta
 * o alimento, esso avra priorita' maggiore rispetto a quelli meno consumati).\n
 * Un'altra funzionalita' dello smart fridge permette di tenere traccia degli alimenti acquistati, registrando uno storico delle spese effettuate.\n
 * Le esigenze della famiglia vengono cosi' riconosciute per comprendere se si necessita di acquistare ulteriori alimenti, notificando all'utente gli stessi.\n
 * In seguito ad una spesa, l'utente ha la possibilita' di inserire nuovi alimenti
 * acquistati e di incrementarne le relative quantita'.\n
 * Inoltre e' possibile modificare le informazioni relative a ciascun alimento e, in base alle quantita di alimenti presenti nel frigo e alle loro relative scadenze,
 * l'utente puo' decidere quali ricette preparare in seguito ad un suggerimento delle stesse da parte dello Smart Fridge.\n
 * Inoltre viene generato un calendario delle consumazioni a cui e' possibile accedervi per la visualizzazione e l'eventuale modifica.\n
 * Da quest'ultimo e' possibile consultare il menu settimanale sia della settimana corrente sia di settimane passate fino al primo avvio dello Smart Fridge,
 * salvo errori o danneggiamenti sul file non coperti dalla garanzia.\n
 * L'utente ha anche la possibilita' di gestire tutte le informazioni riguardanti le ricette ovvero l'aggiunta di nuove e la modifica e la cancellazione delle stesse.\n
 * Un'altra funzionalita' offerta dallo Smart Fridge e' la possibilita' di cercare le ricette che necessitano di determinati alimenti inseriti dall'utente
 * per essere preparate.\n
 * Tutte queste funzionalita' sono viusalizzate sul pannello touch attraverso un menu principale dove ad ogni voce corrisponde una macro funzione.
 *
 *
 *
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


/**
 * Funzione principale del programma.
 *
 * @return 1 se il programma e' andato a buon fine.
 */
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	int numScelta;

	//creazione e caricamento del vettore di alimenti
	int lunghezzaVettoreAlimenti = get_lunghezza_file_alimenti();
	alimento *alimenti=(alimento*) calloc(lunghezzaVettoreAlimenti,sizeof(alimento));
	if(carica_alimenti(alimenti) == 0) printf("\nIl file di alimenti non esiste o e' vuoto!\n");


	//creazione e caricamento del vettore di ricette
	int lunghezzaVettoreRicette=get_lunghezza_file_ricette();
	ricetta *ricette=(ricetta*) calloc(lunghezzaVettoreRicette,sizeof(ricetta));
	if(carica_ricette(ricette) == 0) printf("\nIl file di ricette non esiste o e' vuoto!\n");


	//Caricamento delle impostazioni dal file di configurazione
	carica_configurazione();

	/*visualizza_storico_spesa(alimenti,lunghezzaVettoreAlimenti);
	visualizza_file_pasti(ricette);


	visualizza_alimenti(alimenti,lunghezzaVettoreAlimenti);
	visualizza_ricette(ricette,lunghezzaVettoreRicette);*/


	//genera_consumazioni_pasti(alimenti,lunghezzaVettoreAlimenti,ricette,lunghezzaVettoreRicette);
	//genera_acquisto_spesa(alimenti,lunghezzaVettoreAlimenti);


	int nuovoIndirizzoAlimenti;
	int nuovoIndirizzoRicette;

	do {
		printf("Benvenuto in SMARTFRIDGE\n");

		numScelta = fai_scelta(MENU_PRINCIPALE);

		switch (numScelta) {
		case 1:		//Suggerimento spesa

			scelte_spesa(alimenti,lunghezzaVettoreAlimenti);

			break;

		case 2:		//Suggerimento Ricette

			scelta_opzioni_suggerimento_ricette(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;

		case 3:		//Ricerca Ricette per alimento

			ricerca_ricette_per_alimenti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);


			break;
		case 4:		//Opzioni Alimenti

			scelta_opzioni_alimenti(alimenti,lunghezzaVettoreAlimenti);

			break;
		case 5:		//Opzioni Ricette

			lunghezzaVettoreRicette=scelta_opzioni_ricette(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti,&nuovoIndirizzoRicette);

			//aggiorno il vettore con quello nuovo nel caso c'e' stata l'aggiunta di una nuovo ricetta
			ricette=(ricetta *)nuovoIndirizzoRicette;

			break;
		case 6:		//Opzioni Pasti

			scelta_opzioni_pasti(ricette,lunghezzaVettoreRicette,alimenti,lunghezzaVettoreAlimenti);

			break;

		case 7: //Inserisci Spesa


			lunghezzaVettoreAlimenti=scelta_opzioni_spesa(alimenti,lunghezzaVettoreAlimenti,&nuovoIndirizzoAlimenti);

			//aggiorno il vettore con quello nuovo nel caso c'e' stata l'aggiunta di un nuovo alimento
			alimenti=(alimento *)nuovoIndirizzoAlimenti;


			break;

		case 8:
			break;

		default:
			printf("\nScelta non valida!\n");
		}

		//pulisco lo schermo
		system("cls");

	} while (numScelta != 8);

	return 0;
}



void genera_consumazioni_pasti(alimento alimenti[],int lunghezzaAlimenti,ricetta ricette[],int lunghezzaRicette){
	srand(time(NULL));

	int idRicettaDaConsumare;
	int porzioniDaConsumare;
	int porzioniPossibili;
	int day=12;

	int i;
	for(i=0;i<5;i++){

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
		pp.Data_Ora.Mese = 3;

		if ((file = fopen("Storico_Pasti.sf", "ab+")) == NULL) {
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
	for(j=0;j<55;j++){
		get_data_pointer(&elemento.Data_Ora);

		elemento.Data_Ora.Anno=2018;
		elemento.Data_Ora.Mese=6;
		day +=1 + (rand() % 2);
		day=5;
		elemento.Data_Ora.Giorno=day;




		elemento.Quantita=1 + (rand() % 3);

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

		if ((fileStoricoSpesa = fopen("Storico_Spesa.sf", "ab+")) != NULL)
		{

			fwrite(&elemento,sizeof(elemento_spesa),1,fileStoricoSpesa);

			fclose(fileStoricoSpesa);
		}
	}

}


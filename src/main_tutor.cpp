// Autore: Davide Cossalter

#include <iostream>
#include <cctype>
#include <string>
#include "../include/autostrada.h"
#include "../include/veicolo.h"
#include "../include/editor.h"
#include "../include/tutor.h"


// Verifica della presenza esclusiva di numeri all'interno di una stringa
bool verificaNumeri(const std::string& s);

// Gestione delle interazioni con l'utente
int main()
{

    std::string comando;				// Input dell'utente
    bool terminazione = false;			// Terminazione del programma
	Editor modifica;					// Flusso di dati dei file testuali
    
    // Comandi di selezione
    do
    {
        std::cout << "--------------- DIGITA UNO DEI SEGUENTI COMANDI ---------------" << std::endl;
        std::cout << "- set_time <istante>" << std::endl;
        std::cout << "- reset" << std::endl;
        std::cout << "- stats" << std::endl;
        std::cout << "- exit" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::getline(std::cin, comando);
		std::string sub = comando.substr(9, comando.size() - 9);											// Intervallo temporale di avanzamento	
		int istante = 0;		

        // Gestione delle opzioni
		if((comando.substr(0, 9) == "set_time ") && (verificaNumeri(sub)))									// Avanzamento in secondi al nuovo istante temporale
		{
			std::cout << "Il nuovo istante temporale e' " << "..." << std::endl;
			istante = std::stoi(sub);												
			// TODO: chiamata a funzione
		}
		std::string ultimo = comando.substr(comando.size() - 1, 1);											// Ultimo carattere del comando
		std::string sub = comando.substr(9, comando.size() - 10);											// Intervallo temporale di avanzamento
		else if((comando.substr(0, 9) == "set_time ") && (verificaNumeri(sub)) && (ultimo == "m"))			// Avanzamento in minuti al nuovo istante temporale
		{
			std::cout << "Il nuovo istante temporale e' " << "..." << std::endl;
			istante = std::stoi(sub);												
			//TODO: chiamata a funzione
		}
		else if(comando == "reset")																			// Reset completo del sistema
		{
			//TODO: chiamata a funzione;
			std::cout << "Il sistema e' stato riportato allo stadio iniziale" << std::endl;
		}
		else if(comando == "stats")																			// Stampa delle statistiche
		{
			//num_varchi = TODO: dim vector varchi;
			std::cout << "Statistiche del sistema " << std::endl;
			/*TODO: for(int i = 0; i < num_varchi; i ++)
			{
				std::cout << "Varco n. " << num_varchi << std:: endl;
				std::cout << "- Numero medio di veicoli al minuto: " << "..." << std::endl;
				std::cout << "- Numero complessivo di veicoli transitati: " << "..." << std::endl;
			}	*/
			std::cout << std::endl;
			std::cout << "Velocità media dei veicoli: " /* << TODO: chiamata a variabile */ << " km/h" << std::endl;
			std::cout << "Numero di veicoli sanzionati: " /* << TODO: chiamata a variabile */ << std::endl;
		}
		else if(comando == "exit")																			// Terminazione del programma
		{
			terminazione = true;
		}
		else																								// Segnalazione di comando illegale
		{
			std::cout << "Errore: comando inserito non valido" << std::endl; 
		}
		
        std::cout << std::endl;
    } while (!terminazione);

    std::cout << "Il programma e' terminato." << std::endl;
    return 0;
	
}

// Verifica della presenza esclusiva di numeri all'interno di una stringa
bool verificaNumeri(const std::string& numeri) 
{ 
	for (unsigned char cifra : numeri)																			
	{ 
		if (!std::isdigit(cifra)) 																			// Scansione del contenuto della sottostringa
		{ 
			return false; 
		} 
	} 
	return !numeri.empty(); 
}
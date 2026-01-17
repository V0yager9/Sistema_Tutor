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
	Tutor sistema;						// Controllo del transito dei veicoli
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
		std::string ultimo = comando.substr(comando.size() - 1, 1);											// Ultimo carattere del comando
		std::string sub = "";																				// Intervallo temporale di avanzamento															
		double istante = 0.0;		
		
		// Selezione della tipologia di intervallo temporale
		if(ultimo == "m")																					// La presenza di "m" indica la selezione di un intervallo in minuti
			sub = comando.substr(9, comando.size() - 10);													// Intervallo temporale in minuti
		else
			sub = comando.substr(9, comando.size() - 9);													// Intervallo temporale in secondi
		
        // Gestione delle opzioni
		if((comando.substr(0, 9) == "set_time ") && (verificaNumeri(sub)) && (verificaNumeri(ultimo)))		// Avanzamento in secondi al nuovo istante temporale
		{
			istante = std::stod(sub);												
			// TODO: chiamata a funzione
			std::cout << "Il nuovo istante temporale e' " << sistema.getTempo() << std::endl;
		}
		else if(comando.substr(0, 9) == "set_time ") && (verificaNumeri(sub)) && (ultimo == "m"))			// Avanzamento in minuti al nuovo istante temporale
		{
			istante = std::stod(sub);
			istante = istante * 60;																			// Conversione in secondi
			//TODO: chiamata a funzione
			std::cout << "Il nuovo istante temporale e' " << sistema.getTempo() << std::endl;
		}
		else if(comando == "reset")																			// Reset completo del sistema
		{
			sistema.reset();
			std::cout << "Il sistema e' stato riportato allo stadio iniziale" << std::endl;
		}
		else if(comando == "stats")																			// Stampa delle statistiche
		{
			//num_varchi = TODO: quantità varchi;
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
    if(numeri.empty())
	{
        return false;												// Rilevamento di stringa vuota
	}
    if((numeri.front() == '.') || (numeri.back() == '.'))			// Il punto non può essere né primo né ultimo
   	{
		return false;
	}
    bool puntoTrovato = false;
    for(unsigned char c : numeri)									// Scansione del contenuto della stringa						
    {
        if(c == '.') 
		{
            if(puntoTrovato)
                return false;   									// Rilevamento di più punti
            puntoTrovato = true;
            continue;
        }
        if(!std::isdigit(c))
            return false;											// Rilevamento di carattere illegale
    }
    return true;													// La stringa contiene solo caratteri numerici
}



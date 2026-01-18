// Autore: Davide Cossalter

#include <iostream>
#include <cctype>
#include <string>
#include "../include/tutor.h"


// Verifica della presenza esclusiva di numeri all'interno di una stringa
bool verificaNumeri(const std::string& s);

// Conversione del formato del tempo (HH:MM:SS)
std::string conversioneTempo(double tot_secondi)

// Gestione delle interazioni con l'utente
int main()
{
	Tutor sistema;						// Controllo del transito dei veicoli
    std::string comando;				// Input dell'utente
    bool termine = false;				// Terminazione del programma
    
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
		bool parole = false;
		if(comando.size() > 9)
		{
			parole = (comando.substr(0, 9) == "set_time ");													// Verifica della presenza del comando set_time 
		}
		
		// Gestione delle opzioni
		if(parole)
		{
			std::string ultimo = comando.substr(comando.size() - 1, 1);										// Ultimo carattere del comando
			std::string sub = "";																			// Intervallo temporale di avanzamento
			if (ultimo == "m")   																			// La presenza di "m" indica la selezione di un intervallo in minuti
				sub = comando.substr(9, comando.size() - 10);												// Intervallo temporale in minuti
			else                
				sub = comando.substr(9, comando.size() - 9);												// Intervallo temporale in secondi
		
			bool numeriValidi = verificaNumeri(sub);														// Verifica del contenuto numerico della stringa		
			bool ultimoValido = (verificaNumeri(ultimo)) || (ultimo == "m");								// Verifica della validità dell'ultimo carattere
			if ((!numeriValidi) || (!ultimoValido))															// Segnalazione di comando illegale
			{
				std::cout << "Errore: formato del comando set_time non valido" << std::endl;
			}
			else																							// Avanzamento al nuovo istante temporale
			{
				double istante = std::stod(sub);
				if (ultimo == "m")
					istante *= 60;   																		// Conversione in secondi
				sistema.progressioneTempo(istante);
				double numSecondi = sistema.getTempo();
				std::string orario = conversioneTempo(numSecondi);											// Il formato diventa HH:MM:SS
				std::cout << "Il nuovo istante temporale e' " << orario << std::endl;
			}
		}
		else if(comando == "reset")																			// Ripristino del sistema allo stato iniziale
		{
			sistema.reset();
			std::cout << "Il sistema e' stato riportato allo stadio iniziale" << std::endl;
		}
		else if(comando == "stats")																			// Stampa delle statistiche
		{
			sistema.stampaStatistiche();
		}
		else if(comando == "exit")																			// Terminazione del programma
		{
			termine = true;
		}
		else																								// Segnalazione di comando illegale
		{
			std::cout << "Errore: comando inserito non valido" << std::endl; 
		}
		
        std::cout << std::endl;
    } while (!termine);

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

// Conversione del formato del tempo (HH:MM:SS)
std::string conversioneTempo(double tot_secondi)
{
	int tot = static_cast<int>(tot_secondi);
	int ore = tot / 3600;
	int minuti = (tot - ore * 3600) / 60;
	int secondi = tot - ore * 3600 - minuti * 60;
	std::string orologio = 											// Eventuale aggiunta di zeri riempitivi se necessario
		(ore < 10 ? "0" : "") + std::to_string(ore) + ":" + 
		(minuti < 10 ? "0" : "") + std::to_string(minuti) + ":" + 
		(secondi < 10 ? "0" : "") + std::to_string(secondi);

	return orologio;
}


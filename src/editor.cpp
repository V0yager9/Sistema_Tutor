// Autore: Davide Cossalter

#include "../include/Editor.h"


// Inizializzazione della directory di destinazione del file testuale
Editor::Editor(std::string title) 
{
	dir = "../data/";
	dir = dir + title;																	// Nome del file testuale
	document.open(dir.c_str(), std::ios_base::out);										// Creazione e apertura del file testuale
	if(!document.is_open())																// Verifica di chiusura del file testuale
	{
		std::cout << "Errore di apertura del file testuale" << std::endl;				// Messaggio di errore
	}
	closer();																			// Chiusura del file testuale
}

// Operazione di lettura del file testuale
std::string Editor::reader()
{
	std::string line;
	document.open(dir, std::ios_base::in);												// Apertura del file testuale in lettura
	std::getline(document, line);														// Memorizzazione della riga di testo
	closer();																			// Chiusura del file testuale
	return line;
}

// Operazione di scrittura del file testuale
void Editor::writer(std::string change) 
{
	document.open(dir, std::ios_base::app);												// Apertura del file testuale in scrittura
	if(document.is_open())																// Verifica dello stato di apertura del file
	{
		document << change << std::endl;												// Scrittura nel file testuale
	}
	closer();																			// Chiusura del file testuale
}

// Operazione di chiusura del file testuale
void Editor::closer() 
{
	document.close();
	if(document.is_open())																// Verifica di chiusura del file testuale
	{														
		std::cout << "Errore di chiusura del file testuale" << std::endl;				// Messaggio di errore
	}
}


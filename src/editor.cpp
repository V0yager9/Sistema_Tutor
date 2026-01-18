// Autore: Davide Cossalter

#include <ifstream>
#include "../include/editor.h"


// Costruttore di default
Editor::Editor() 
{
    dir = "data/";																// Cartella contenente i file testuali del progetto
}

// Inizializzazione della directory di destinazione del file testuale
Editor::Editor(std::string title)
{
    dir = "data/";
    dir += titolo;																// Nome del file testuale
    document.open(dir.c_str(), std::ios_base::out | std::ios_base::app);		// Il file testuale viene lasciato aperto
    if(!documento.is_open())													// Segnalazione di errore
    {
        std::cout << "Errore di apertura del file testuale." << std::endl;
    }
}

// Distruttore
Editor::~Editor()
{
    if(documento.is_open())
    {
        documento.close();														// Chiusura automatica del file testuale
    }
}

// Operazione di modifica della directory
void Editor::setDir(std::string titolo)
{
	dir = "data/";
    dir += titolo;																// Nuova directory
}

// Operazione di lettura del file testuale
std::string Editor::reader()
{
    std::ifstream in(dir.c_str());												// Apertura del file testuale per la lettura
    if(!in.is_open())															// Segnalazione di errore
    {
        std::cout << "Errore di apertura del file testuale." << std::endl;
        return "";
    }
    std::string contenuti;														// Contenuti del file testuale
    std::string riga;															// Linea estratta dal file testuale
    while (std::getline(in, riga))												// Estrazione dell'intero contenuto del file testuale
    {
        contenuti += riga;
        contenuti += "\n";
    }
    return contenuti;
}

// Operazione di scrittura sul file testuale
void Editor::writer(std::string change)
{
    if(documento.is_open())
    {
        documento << change << "\n";											// Scrittura nel file testuale
    }
    else																		// Segnalazione di errore
    {
        std::cout << "Errore di apertura del file testuale: scrittura non riuscita." << std::endl;
    }
}

// Operazione di chiusura del file testuale
void Editor::closeDoc()
{
    if(documento.is_open())
    {
        documento.close();														// Chiusura manuale del file testuale
    }
    if(documento.is_open())														// Segnalazione di errore
    {
        std::cout << "Errore di chiusura del file testuale." << std::endl;
    }
}


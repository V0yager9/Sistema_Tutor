// Autore: Davide Cossalter

#include "../include/editor.h"

Editor::Editor() {
    dir = "";
}

Editor::Editor(std::string title)
{
    dir = "data/";
    dir = dir + title;

    // Apro una sola volta il file e tengo aperto
    document.open(dir.c_str(), std::ios_base::out | std::ios_base::app);
    if(!document.is_open())
    {
        std::cout << "Errore di apertura del file testuale" << std::endl;
    }
}

Editor::~Editor()
{
    if(document.is_open())
    {
        document.close();
    }
}

std::string Editor::reader()
{
    // Apro un ifstream separato per la lettura.
    // Restituisco l'intero contenuto del file (tutte le righe).
    std::ifstream in(dir.c_str());
    if(!in.is_open())
    {
        std::cout << "Errore di apertura del file testuale" << std::endl;
        return "";
    }

    std::string content;
    std::string line;
    while (std::getline(in, line))
    {
        content += line;
        content += "\n";
    }
    return content;
}

void Editor::writer(std::string change)
{
    if(document.is_open())
    {
        document << change << "\n";
    }
    else
    {
        std::cout << "File non aperto, impossibile scrivere" << std::endl;
    }
}

void Editor::closeDoc()
{
    if(document.is_open())
    {
        document.close();
    }
    if(document.is_open())
    {
        std::cout << "Errore di chiusura del file testuale" << std::endl;
    }
}
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
    std::ifstream in(dir.c_str());	// Apro un ifstream separato per la lettura
    std::string line;
    std::getline(in, line);
    return line;
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

void Editor::closer()
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
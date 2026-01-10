// Autore: Davide Cossalter

#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <fstream>
#include <string>


// Editing di file testuali (txt)
class Editor
{ 
	public:
		Editor();  // Costruttore vuoto

		// Inizializzazione della directory di destinazione del file testuale
		Editor(std::string title);

		// Distruttore
		~Editor();
		
		// Operazione di lettura del file testuale
		std::string reader();
		
		// Operazione di scrittura del file testuale
		void writer(std::string change);	
		
		// Operazione di chiusura del file testuale
		void closer();
			
	private:
		// Directory dei file testuali
		std::string dir;
		
		// Flusso dei dati
		std::fstream document;
};

#endif
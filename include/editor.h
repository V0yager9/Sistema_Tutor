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
		// Costruttore di default
		Editor();

		// Inizializzazione della directory di destinazione del file testuale
		Editor(std::string titolo);

		// Distruttore
		~Editor();
		
		// Operazione di modifica della directory
		void setDir(std::string titolo);
		
		// Operazione di lettura del file testuale
		std::string reader();
		
		// Operazione di scrittura sul file testuale
		void writer(std::string modifica);	
		
		// Operazione di chiusura del file testuale
		void closeDoc();
			
	private:
		// Directory dei file testuali
		std::string dir;
		
		// Flusso dei dati
		std::fstream documento;
};

#endif
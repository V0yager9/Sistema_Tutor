// Autore: Davide Cossalter

#include "../include/tutor.h"

// Costruttore di default
Tutor::Tutor() 
{
	//TODO: conteggio del numero totale di varchi
	// Estrazione dei dati dal primo file testuale
	Editor editing("passages.txt");							
	std::string testo = editing.reader();
	editing.closeDoc();
	std::string riga; 
	std::stringstream ss1(testo);
	while (std::getline(ss, riga, '\n')) 					// Scansione del testo del documento
	{ 
		std::stringstream ssRiga(riga); 
		std::string parola;
		int cont = 0;
		while (ssLinea >> parola) 							// Scansione delle righe di testo
		{ 
			if(cont = 0)									// Registrazione del primo dato della riga
				transiti[cont].varco = std::stoi(parola);
			else if(cont = 1)								// Registrazione del secondo dato della riga
				transiti[cont].targa = parola;
			else											// Registrazione del terzo dato della riga
				transiti[cont].istante = std::stod(parola);
			
			cont ++;
		}
	}
	testo = "";
	riga = "";
	ss.clear();
	
	// Estrazione dei dati dal secondo file testuale
	editing.setDir("runs.txt");	
	testo = editing.reader();
	editing.closeDoc();
	ss.str(testo);
	while (std::getline(ss, riga, '\n')) 							// Scansione del testo del documento
	{ 
		std::stringstream ssRiga(riga); 
		std::string parola;
		std::vector<std::string> restanti; 							// Parole successive alle prime 4
		int cont = 0;
		while (ssRiga >> parola) 									// Scansione della prima parte della riga di testo
		{ 
			switch (cont)
			{
				case 0: stats.targa = parola; break;				// Registrazione della prima parola
				case 1: stats.ingresso = stoi(parola); break;		// Registrazione della seconda parola
				case 2: stats.uscita = stoi(parola); break;			// Registrazione della terza parola
				case 3: stats.partenza = stod(parola); break;		// Registrazione della quarta parola
				default: restanti.push_back(parola); break;			// Parole rimanenti
			}
			cont ++;
		}
															
	    for (std::size_t i = 0; i + 1 < restanti.size(); i += 2) 	// Registrazione delle coppie di dati <v t>
		{													
			std::string v = restanti[i];
			std::string t = restanti[i + 1];
			if (!t.empty() && t.back() == ',') 						// Rimozione delle virgole indesiderate
				t.pop_back();
			stats.v_t.emplace_back(v, t);								// Registrazione dei valori di v e t
		}
	}
}

// Restituizione del tempo corrente 
double Tutor::getTempo() const
{ 
	return tempoCorrente; 
}

// Avanzamento al nuovo istante temporale
void Tutor::progressioneTempo(double intervalloTemporale)
{
	//TODO: elaborazione dei dati al nuovo istante
	if (intervalloTemporale > 0)
	{
		setTempo(intervalloTemporale);
		tempoCorrente += intervallo;
	}
	else {}
}
/*
// Registrazione del passaggio di veicoli
void Tutor::registrazionePassaggi(const std::string& targa, int varco)
{ 

} */

// Ripristino del sistema allo stato iniziale
void Tutor::reset() 
{ 
	transiti.clear(); 
	stats.clear(); 
	tempoCorrente = 0; 
} 

// Stampa delle statistiche
void Tutor::stampaStatistiche() const; 
{
	//TODO: calcolo delle statistiche
	if (stats.empty()) 
	{ 
		std::cout << "Nessun dato disponibile." << std::endl; 
		return; 
	} 
	else
	{
		std::cout << "STATISTICHE DEL SISTEMA" << std::endl;
		std:cout << "Statistiche dei singoli varchi" << std::endl;
		for(int i = 0; i < numVarchi; i ++)
		{
			std::cout << "- Varco n. " << i + 1 << std:: endl;
			std::cout << "	Numero medio di veicoli al minuto: " << "..." << std::endl;
			std::cout << "	Numero complessivo di veicoli transitati: " << "..." << std::endl;
		}
		std::cout << "Statistiche complessive:" << std::endl;
		std::cout << "- Velocità media dei veicoli: "  << "..." << " km/h" << std::endl;
		std::cout << "- Numero di veicoli sanzionati: "  << "..." << std::endl;
	}
}
	

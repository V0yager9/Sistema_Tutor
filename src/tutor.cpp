// Autore: Davide Cossalter

#include "../include/tutor.h"


// Costruttore di default
Tutor::Tutor() 
{

}

// Avanzamento al nuovo istante temporale
void Tutor::setTempo(double intervallo)
{
	tempoCorrente += intervallo;
}

// Restituizione del tempo corrente 
double Tutor::getTempo() const
{ 
	return tempoCorrente; 
}

// Avanza il tempo simulato 
void Tutor::avanzaTempo(double intervalloTemporale)
{
	if (intervalloTemporale > 0)
	{
		setTempo(intervalloTemporale);
	}
	else {}
}

// Registra un passaggio 
void Tutor::registraPassaggio(const std::string& targa, int varco)
{ 
	transiti[targa].push_back({tempoCorrente, varco}); 
	auto& v = transiti[targa]; 
	if (v.size() >= 2) 
	{ 
		auto p1 = v[v.size() - 2]; 
		auto p2 = v[v.size() - 1]; 
		if (p2.varco == (p1.varco + 1)) 
		{ 
			double deltaT = (p2.istante - p1.istante) / 60.0; 						// Ore 
			double velocita = distanzaTraVarchi / deltaT; 
			bool infrazione = velocita > limite; 
			stats.push_back({targa, p1.varco, p2.varco, velocita, infrazione}); 
		} 
	} 
} 

// Reset del sistema 
void Tutor::reset() 
{ 
	transiti.clear(); 
	stats.clear(); 
	tempoCorrente = 0; 
} 

// Stampa delle statistiche
void Tutor::stampaStatistiche() const; 
{
	if (stats.empty()) 
	{ 
		std::cout << "Nessun dato disponibile.\n"; 
		return; 
	} 
	/*for (const auto& s : stats) 
	{ 
		std::cout << "Veicolo: " << s.targa
		<< " | Tratta " << s.varco1 << " -> " << s.varco2
		<< " | Velocità media: " << std::fixed << std::setprecision(2)
		<< s.velocita << " km/h" << " | Infrazione: " << (s.infrazione ? "SI" : "NO")
		<< "\n"; 
	} */
}
	

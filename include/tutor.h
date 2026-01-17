// Autore: Davide Cossalter

#ifndef TUTOR_H
#define TUTOR_H

#include <unordered_map> 
#include <iostream> 
#include <iomanip>
#include <vector> 
#include <string> 


// Sistema di controllo del transito dei veicoli
class Tutor 
{
	private: 
	
		// Attaversamento dei varchi da parte dei veicoli
		struct Passaggio 
		{ 
			int istante; 							// Istante del passaggio 
			int varco; 								// Numero del varco 
		}; 	
		
		// Storico passaggi per ogni veicolo 
		std::unordered_map<std::string, std::vector<Passaggio>> transiti;
		
		// Statistiche rilevate per veicolo
		struct Stat
		{ 
			std::string targa; 
			int varco1, varco2; 
			double velocita; 
			bool infrazione; 
		}; 
		std::vector<Stat> stats; 					// Statistiche complessive
		double tempoCorrente = 0.0;					// Unità di misura: secondi
		double distanzaTraVarchi = 0.0;		 		// Unità di misura: chilometri
		const double limite = 130.0; 				// Unità di misura: chilometri orari
		
		// Nuovo istante temporale
		void setTempo(double intervalloTemporale);
		
	public: 
		// Costruttore di default
		Tutor();
		
		// Restituzione del tempo corrente 
		double getTempo() const;
		
		// Avanza il tempo simulato 
		bool avanzaTempo(double intervalloTemporale);
		
		// Registra un passaggio 
		void registraPassaggio(const std::string& targa, int varco);  
		
		// Reset del sistema 
		void reset();
		
		// Stampa statistiche
		void stampaStatistiche() const;
		
};


#endif
// Autore: Davide Cossalter

#ifndef TUTOR_H
#define TUTOR_H

#include <unordered_map> 
#include <iostream> 
#include <sstream>
#include <iomanip>
#include <vector> 
#include <string> 
#include "../include/editor.h"


// Sistema di controllo del transito dei veicoli
class Tutor 
{
	private: 
	
		// Attraversamento dei varchi da parte dei veicoli
		struct Passaggio 
		{ 
			std::string targa = ""; 
			double istante = 0.0; 						// Istante del passaggio 
			int varco = 0; 								// Numero del varco 
		}; 	
		
		// Storico dei passaggi per ogni veicolo
		std::vector<Passaggio> transiti;
		
		// Statistiche rilevate per veicolo
		struct Stat
		{ 
			std::string targa = ""; 
			int ingresso = 0, uscita = 0;				// Svincoli 
			double partenza = 0.0;						// Unitò di misura: secondi
			double velocita = 0.0;						// Unitò di misura: chilometri orari
			std::vector<std::pair<int, int>> v_t;		// Intervalli <v t> generati nella simulazione
			bool infrazione = false; 
		}; 
		std::vector<Stat> stats; 						// Statistiche complessive
		int numVarchi = 0;								// Numero totale di varchi
		double tempoCorrente = 0.0;						// Unità di misura: secondi
		const double LIMITE = 130.0; 					// Unità di misura: chilometri orari
		
	public: 
		// Costruttore di default
		Tutor();
		
		// Restituzione del tempo corrente 
		double getTempo() const;
		
		// Avanzamento al nuovo istante temporale
		void progressioneTempo(double intervalloTemporale);
		
/*		// Registrazione del passaggio di veicoli
		void registrazionePassaggi(const std::string& targa, int varco);  */
		
		// Ripristino del sistema allo stato iniziale
		void reset();
		
		// Stampa delle statistiche
		void stampaStatistiche() const;
		
};


#endif



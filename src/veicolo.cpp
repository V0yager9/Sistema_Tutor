// Autore: Giovanni Arcaro

#include "../include/veicolo.h"

// costruttore di default
Veicolo::Veicolo()
    : targa(""),
      svincoloIngresso(-1),
      svincoloUscita(-1),
      istantePartenza(0.0) {}

Veicolo::Veicolo(const std::string& targa,int svincoloIngresso,int svincoloUscita,double istantePartenza)
    : targa(targa),
      svincoloIngresso(svincoloIngresso),
      svincoloUscita(svincoloUscita),
      istantePartenza(istantePartenza) {}

const std::string& Veicolo::getTarga() const {
    return targa;
}

int Veicolo::getSvincoloIngresso() const {
    return svincoloIngresso;
}

int Veicolo::getSvincoloUscita() const {
    return svincoloUscita;
}

double Veicolo::getIstantePartenza() const {
    return istantePartenza;
}

void Veicolo::aggiungiIntervallo(double velocitaKmH, double durataSecondi) {
    profiloVelocita.emplace_back(velocitaKmH, durataSecondi);
}

const std::vector<std::pair<double, double>>& Veicolo::getProfiloVelocita() const {
    return profiloVelocita;
}

double Veicolo::distanzaPercorsa() const {
    double distanza = 0.0;

    for (size_t i = 0; i < profiloVelocita.size(); ++i) {
        const auto& intervallo = profiloVelocita[i];
        double velocita = intervallo.first; //primo elemento del pair
        double durata = intervallo.second; //secondo elemento del pair
        distanza += velocita * (durata / 3600.0);
    }
    return distanza;
}

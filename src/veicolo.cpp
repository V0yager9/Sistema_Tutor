#include "../include/veicolo.h"

// costruttore di default
Veicolo::Veicolo()
    : m_targa(""),
      m_svincoloIngresso(-1),
      m_svincoloUscita(-1),
      m_istantePartenza(0.0) {}

Veicolo::Veicolo(const std::string& targa,int svincoloIngresso,int svincoloUscita,double istantePartenza)
    : m_targa(targa),
      m_svincoloIngresso(svincoloIngresso),
      m_svincoloUscita(svincoloUscita),
      m_istantePartenza(istantePartenza) {}

const std::string& Veicolo::getTarga() const {
    return m_targa;
}

int Veicolo::getSvincoloIngresso() const {
    return m_svincoloIngresso;
}

int Veicolo::getSvincoloUscita() const {
    return m_svincoloUscita;
}

double Veicolo::getIstantePartenza() const {
    return m_istantePartenza;
}

void Veicolo::aggiungiIntervallo(double velocitaKmH, double durataSecondi) {
    m_profiloVelocita.emplace_back(velocitaKmH, durataSecondi);
}

const std::vector<std::pair<double, double>>& Veicolo::getProfiloVelocita() const {
    return m_profiloVelocita;
}

double Veicolo::distanzaPercorsa() const {
    double distanza = 0.0;

    for (const auto& intervallo : m_profiloVelocita) {
        double velocita = intervallo.first;
        double durata = intervallo.second;
        distanza += velocita * (durata / 3600.0);
    }

    return distanza;
}

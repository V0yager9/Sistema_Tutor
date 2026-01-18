// Autore: Giovanni Arcaro

#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <vector>
#include <utility>

class Veicolo {
public:
    Veicolo(); // costruttore di default
    Veicolo(const std::string& targa,
            int svincoloIngresso,
            int svincoloUscita,
            double istantePartenza);

    const std::string& getTarga() const;
    int getSvincoloIngresso() const;
    int getSvincoloUscita() const;
    double getIstantePartenza() const;

    void aggiungiIntervallo(double velocitaKmH, double durataSecondi);
    const std::vector<std::pair<double, double>>& getProfiloVelocita() const;

    double distanzaPercorsa() const;

private:
    std::string targa;
    int svincoloIngresso;
    int svincoloUscita;
    double istantePartenza;

    std::vector<std::pair<double, double>> profiloVelocita;
};

#endif

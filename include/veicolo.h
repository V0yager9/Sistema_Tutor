#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <vector>
#include <utility>

class Veicolo {
public:
    Veicolo();
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
    std::string m_targa;
    int m_svincoloIngresso;
    int m_svincoloUscita;
    double m_istantePartenza;

    std::vector<std::pair<double, double>> m_profiloVelocita;
};

#endif

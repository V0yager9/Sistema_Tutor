#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <vector>
#include <utility>

/*
 * Classe Veicolo
 * Rappresenta un veicolo che percorre l'autostrada con un certo profilo di velocità
 */

class Veicolo {
public:
    // Costruttori
    Veicolo();
    Veicolo(const std::string& targa,
            int svincoloIngresso,
            int svincoloUscita,
            double istantePartenza);

    // Getter
    const std::string& getTarga() const;
    int getSvincoloIngresso() const;
    int getSvincoloUscita() const;
    double getIstantePartenza() const;

    // Profilo di velocità
    void aggiungiIntervallo(double velocitaKmH, double durataSecondi);
    const std::vector<std::pair<double, double>>& getProfiloVelocita() const;

    // Utilità
    double distanzaPercorsa() const;

private:
    std::string m_targa;
    int m_svincoloIngresso;
    int m_svincoloUscita;
    double m_istantePartenza;

    // coppia <velocità km/h, durata in secondi>
    std::vector<std::pair<double, double>> m_profiloVelocita;
};

#endif // VEICOLO_H

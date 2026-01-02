#ifndef AUTOSTRADA_H
#define AUTOSTRADA_H

#include <vector>
#include <string>

/*
 * Classe Autostrada
 * Gestisce la struttura dell'autostrada: varchi e svincoli
 */

class Autostrada {
public:
    struct Varco {
        int id;
        double km;
    };

    struct Svincolo {
        int id;
        double km;
    };

    // Costruttori
    Autostrada();

    // Caricamento da file
    bool caricaDaFile(const std::string& nomeFile);

    // Getter
    const std::vector<Varco>& getVarchi() const;
    const std::vector<Svincolo>& getSvincoli() const;

    // Utilità
    double getKmVarco(int id) const;
    double getKmSvincolo(int id) const;

    int numeroVarchi() const;
    int numeroSvincoli() const;

private:
    std::vector<Varco> m_varchi;
    std::vector<Svincolo> m_svincoli;

    // Metodi di supporto
    void assegnaId();
    bool verificaVincoli() const;
};

#endif // AUTOSTRADA_H

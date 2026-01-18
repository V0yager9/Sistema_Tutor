// Autore: Giovanni Arcaro

#ifndef AUTOSTRADA_H
#define AUTOSTRADA_H

#include <vector>
#include <string>

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

    Autostrada(); // costruttore di default

    bool caricaDaFile(const std::string& nomeFile);

    const std::vector<Varco>& getVarchi() const;
    const std::vector<Svincolo>& getSvincoli() const;

    double getKmVarco(int id) const;
    double getKmSvincolo(int id) const;

    int numeroVarchi() const;
    int numeroSvincoli() const;

private:
    std::vector<Varco> varchi;
    std::vector<Svincolo> svincoli;

    void assegnaId();
    bool verificaVincoli() const;
};

template <typename T> 
bool confrontaPerKm(const T& a, const T& b) { // funzione di confronto per l'ordinamento
    return a.km < b.km; 
}

#endif

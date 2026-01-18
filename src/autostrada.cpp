// Autore: Giovanni Arcaro

#include "../include/autostrada.h"
#include "../include/editor.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>

Autostrada::Autostrada() {}

// lettura file Highway.txt
bool Autostrada::caricaDaFile(const std::string& nomeFile) {
    Editor editor(nomeFile);
    const std::string contenuto = editor.reader();
    editor.closeDoc();
    if (contenuto.empty()){
        throw std::runtime_error("Highway.txt vuoto o non leggibile");
    }

    varchi.clear();
    svincoli.clear();

    //legge i dati riga per riga come se fosse uno stream
    std::istringstream contenutoFile(contenuto);
    std::string linea;
    int nlinea = 1;

    while (std::getline(contenutoFile, linea)) { //salva una riga del file in "linea"
        std::istringstream contenutoLinea(linea); //crea uno stream per la singola linea del file

        contenutoLinea >> std::ws; // passa tutti gli spazi e tab 
        if (contenutoLinea.eof()){//se è alla fine della linea significa che era vuota
            continue; //la riga è vuota e quindi il codice passa al prossimo ciclo
        } 

        double km = 0.0;
        char tipo = '\0';
        if (!(contenutoLinea >> km >> tipo)) {
            throw std::runtime_error("Formato non valido in Highway.txt alla riga " + std::to_string(nlinea) + ": attesa distanza in km  e tipo V o S");
        }

        // verifica che non ci siano colonne in più rispetto alle due colonne richieste
        contenutoLinea >> std::ws;
        if (!contenutoLinea.eof()) { //se non è alla fine della linea significa che ci sono dati in più
            throw std::runtime_error("Formato non valido in Highway.txt alla riga " + std::to_string(nlinea) + ": presenti colonne extra");
        }

        if (km < 0.0) {
            throw std::runtime_error("Valore distanza negativo in Highway.txt alla riga " + std::to_string(nlinea));
        }

        if (tipo == 'V') {
            varchi.push_back({0, km}); //aggiunge un varco con id 0 (verrà assegnato dopo) e la distanza in km
        } 

        else if (tipo == 'S') {
            svincoli.push_back({0, km}); //aggiunge uno svincolo con id 0 (verrà assegnato dopo) e la distanza in km
        }

        else {
            throw std::runtime_error("Tipo non valido in Highway.txt alla riga " + std::to_string(nlinea) +": usare V (Varco) o S (Svincolo) ");
        }
        ++nlinea;
    }

    if (varchi.empty() && svincoli.empty()){
        throw std::runtime_error("Highway.txt non contiene varchi/svincoli");
    }

    if (!verificaVincoli()) { //controlla i vincoli richiesti
        throw std::runtime_error("Highway.txt non conforme ai vincoli: almeno 2 varchi, almeno 1 svincolo prima del primo varco e 1 dopo l'ultimo, distanza minima varco-svincolo = 1 km.");
    }

    assegnaId();
    return true;
}

// assegna ID ordinati per km, confrontPerKm è un template in autostrada.h
void Autostrada::assegnaId() {
    std::sort(varchi.begin(), varchi.end(), confrontaPerKm<Varco>);
    std::sort(svincoli.begin(), svincoli.end(), confrontaPerKm<Svincolo>);

    for (size_t i = 0; i < varchi.size(); ++i){
        varchi[i].id = static_cast<int>(i + 1);
    }

    for (size_t i = 0; i < svincoli.size(); ++i){
        svincoli[i].id = static_cast<int>(i + 1);
    }
}

bool Autostrada::verificaVincoli() const {
    if (varchi.size() < 2){ //controlla che ci siano almeno 2 varchi
        return false; 
    }

    if (svincoli.empty()){ //controlla che ci sia almeno 1 svincolo
        return false;
    }
        
    double primoVarco = varchi.front().km;
    double ultimoVarco = varchi.back().km;

    bool prima = false;
    bool dopo = false;

    for (int i = 0; i < svincoli.size(); ++i) {
        if (svincoli[i].km <= primoVarco - 1.0) { //controlla che ci sia almeno uno svincolo prima del primo varco
            prima = true;
        }

        if (svincoli[i].km >= ultimoVarco + 1.0) { //controlla che ci sia almeno uno svincolo dopo l'ultimo varco
            dopo = true;
        }
    }

    if (!prima || !dopo){ //se manca uno dei due svincoli richiesti
        return false;
    }

    // distanza minima varco-svincolo = 1 km
    for (int i = 0; i < static_cast<int>(varchi.size()); ++i) {
        for (int j = 0; j < static_cast<int>(svincoli.size()); ++j) {
            if (std::abs(varchi[i].km - svincoli[j].km) < 1.0) {
                return false;
            }
        }
    }
    return true;
}

const std::vector<Autostrada::Varco>& Autostrada::getVarchi() const {
    return varchi;
}

const std::vector<Autostrada::Svincolo>& Autostrada::getSvincoli() const {
    return svincoli;
}

double Autostrada::getKmVarco(int id) const {
    if (id <= 0 || id > static_cast<int>(varchi.size())){
        throw std::out_of_range("ID varco non valido");
    }   
    return varchi[id - 1].km;
}

double Autostrada::getKmSvincolo(int id) const {
    if (id <= 0 || id > static_cast<int>(svincoli.size())){
        throw std::out_of_range("ID svincolo non valido");
    }
    return svincoli[id - 1].km;
}

int Autostrada::numeroVarchi() const {
    return static_cast<int>(varchi.size());
}

int Autostrada::numeroSvincoli() const {
    return static_cast<int>(svincoli.size());
}

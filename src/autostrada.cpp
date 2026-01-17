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
    if (contenuto.empty())
        throw std::runtime_error("Highway.txt vuoto o non leggibile");

    m_varchi.clear();
    m_svincoli.clear();

    // lettura robusta riga-per-riga (il file e' scritto a mano)
    std::istringstream iss(contenuto);
    std::string linea;
    int nlinea = 0;

    while (std::getline(iss, linea)) {
        ++nlinea;
        std::istringstream ls(linea);

        // salta righe vuote o contenenti solo spazi
        ls >> std::ws;
        if (ls.eof())
            continue;

        double km = 0.0;
        char tipo = '\0';
        if (!(ls >> km >> tipo)) {
            throw std::runtime_error("Formato non valido in Highway.txt alla riga " + std::to_string(nlinea) + ": atteso '<distanza_km> <V|S>'");
        }

        // verifica che non ci siano token extra dopo i due richiesti
        ls >> std::ws;
        if (!ls.eof()) {
            throw std::runtime_error("Formato non valido in Highway.txt alla riga " + std::to_string(nlinea) + ": presenti token extra");
        }

        if (km < 0.0) {
            throw std::runtime_error("Valore distanza negativo in Highway.txt alla riga " + std::to_string(nlinea));
        }

        if (tipo == 'V') {
            m_varchi.push_back({0, km});
        } else if (tipo == 'S') {
            m_svincoli.push_back({0, km});
        } else {
            throw std::runtime_error("Tipo non valido in Highway.txt alla riga " + std::to_string(nlinea) +": usare 'V' (Varco) o 'S' (Svincolo) ");
        }
    }

    if (m_varchi.empty() && m_svincoli.empty())
        throw std::runtime_error("Highway.txt non contiene varchi/svincoli");

    assegnaId();

    if (!verificaVincoli()) {
        throw std::runtime_error(
            "Highway.txt non conforme ai vincoli: "
            "almeno 2 varchi, almeno 1 svincolo prima del primo varco e 1 dopo l'ultimo, "
            "distanza minima varco-svincolo = 1 km.");
    }

    return true;
}


// assegna ID ordinati per km, confrontPerKm è un template in autostrada.h
void Autostrada::assegnaId() {
    std::sort(m_varchi.begin(), m_varchi.end(), confrontaPerKm<Varco>);
    std::sort(m_svincoli.begin(), m_svincoli.end(), confrontaPerKm<Svincolo>);

    for (size_t i = 0; i < m_varchi.size(); ++i)
        m_varchi[i].id = static_cast<int>(i + 1);

    for (size_t i = 0; i < m_svincoli.size(); ++i)
        m_svincoli[i].id = static_cast<int>(i + 1);
}

// verifica vincoli del progetto
bool Autostrada::verificaVincoli() const {
    if (m_varchi.size() < 2)
        return false;

    if (m_svincoli.empty())
        return false;

    double primoVarco = m_varchi.front().km;
    double ultimoVarco = m_varchi.back().km;

    bool prima = false;
    bool dopo = false;

    for (const auto& s : m_svincoli) {
        if (s.km <= primoVarco - 1.0)
            prima = true;
        if (s.km >= ultimoVarco + 1.0)
            dopo = true;
    }

    if (!prima || !dopo)
        return false;

    // distanza minima varco-svincolo = 1 km
    for (const auto& v : m_varchi) {
        for (const auto& s : m_svincoli) {
            if (std::abs(v.km - s.km) < 1.0)
                return false;
        }
    }

    return true;
}

const std::vector<Autostrada::Varco>& Autostrada::getVarchi() const {
    return m_varchi;
}

const std::vector<Autostrada::Svincolo>& Autostrada::getSvincoli() const {
    return m_svincoli;
}

double Autostrada::getKmVarco(int id) const {
    if (id <= 0 || id > static_cast<int>(m_varchi.size()))
        throw std::out_of_range("ID varco non valido");
    return m_varchi[id - 1].km;
}

double Autostrada::getKmSvincolo(int id) const {
    if (id <= 0 || id > static_cast<int>(m_svincoli.size()))
        throw std::out_of_range("ID svincolo non valido");
    return m_svincoli[id - 1].km;
}

int Autostrada::numeroVarchi() const {
    return static_cast<int>(m_varchi.size());
}

int Autostrada::numeroSvincoli() const {
    return static_cast<int>(m_svincoli.size());
}

#include "../include/autostrada.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>

Autostrada::Autostrada() {}

// Lettura file Highway.txt
bool Autostrada::caricaDaFile(const std::string& nomeFile) {
    std::ifstream file(nomeFile);
    if (!file.is_open())
        return false;

    m_varchi.clear();
    m_svincoli.clear();

    double km;
    char tipo;

    while (file >> km >> tipo) {
        if (tipo == 'V') {
            m_varchi.push_back({0, km});
        } else if (tipo == 'S') {
            m_svincoli.push_back({0, km});
        } else {
            return false;
        }
    }

    assegnaId();
    return verificaVincoli();
}

// Assegna ID ordinati per km
void Autostrada::assegnaId() {
    std::sort(m_varchi.begin(), m_varchi.end(),
              [](const Varco& a, const Varco& b) {
                  return a.km < b.km;
              });

    std::sort(m_svincoli.begin(), m_svincoli.end(),
              [](const Svincolo& a, const Svincolo& b) {
                  return a.km < b.km;
              });

    for (size_t i = 0; i < m_varchi.size(); ++i)
        m_varchi[i].id = static_cast<int>(i + 1);

    for (size_t i = 0; i < m_svincoli.size(); ++i)
        m_svincoli[i].id = static_cast<int>(i + 1);
}

// Verifica vincoli del progetto
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

// Getter
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

#include "../include/simulatore.h"
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

static const int VEICOLI = 10000;

Simulatore::Simulatore(const Autostrada& hw) : m_hw(hw) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));  //Inizializzo il generatore di numeri casuali
}

int Simulatore::randomInt(int min, int max) {
    return min + std::rand() % (max - min + 1); //Ritorna un intero nell'intervallo [min, max]
}

double Simulatore::randomDouble(double min, double max) {
    return min + (max - min) * (std::rand() / static_cast<double>(RAND_MAX)); //Ritorna un double nell'intervallo [min, max]
}

std::string Simulatore::randomPlate() {  //Genera una targa casuale nel formato AA000AA
    std::string t;

    t += char('A' + randomInt(0, 25));
    t += char('A' + randomInt(0, 25));

    for (int i = 0; i < 3; ++i)
        t += char('0' + randomInt(0, 9));

    t += char('A' + randomInt(0, 25));
    t += char('A' + randomInt(0, 25));

    return t;
}

void Simulatore::run() {
    std::ofstream runs("data/Runs.txt");
    std::ofstream pass("data/Passages.txt");

    double tempoCorrente = 0.0; //Tempo globale del simulatore in secondi

    for (int i = 0; i < VEICOLI; ++i) {

        std::string targa = randomPlate();  //Genero la targa del veicolo

        int ingresso = randomInt(0, m_hw.getSvincoli().size() - 2);
        int uscita = randomInt(ingresso + 1, m_hw.getSvincoli().size() - 1);

        double distanza = m_hw.getSvincoli()[uscita].km - m_hw.getSvincoli()[ingresso].km;

        //Scrivo i dati nel file runs.txt
        runs << targa << " " << m_hw.getSvincoli()[ingresso].id << " " << m_hw.getSvincoli()[uscita].id << " " << tempoCorrente << " ";

        double percorso = 0.0;
        double tempoVeicolo = tempoCorrente;

        while (percorso < distanza) {   //Genero il profilo di velocità del veicolo
            int velocita = randomInt(80, 190);
            int minuti = randomInt(5, 15);
            double secondi = minuti * 60.0;

            double kmPercorsi = velocita * (secondi / 3600.0);

            runs << "<" << velocita << " " << secondi << "> ";

            for (const auto& v : m_hw.getVarchi()) {    //Controllo passaggi ai varchi
                double posizione = v.km - m_hw.getSvincoli()[ingresso].km;

                if (posizione >= percorso && posizione < percorso + kmPercorsi) {
                    double deltaT = (posizione - percorso) / velocita * 3600.0;

                    pass << v.id << " " << targa << " "
                         << std::fixed << std::setprecision(2)
                         << tempoVeicolo + deltaT << "\n";
                }
            }
            percorso += kmPercorsi;
            tempoVeicolo += secondi;
        }
        runs << "\n";

        tempoCorrente += randomDouble(0.5, 10.0);   //Incremento il tempo per la partenza del prossimo veicolo
    }
}
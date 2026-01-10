#include "../include/simulatore.h"
#include "../include/editor.h"

#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

static const int VEICOLI = 10000;

Simulatore::Simulatore(const Autostrada& hw) : m_hw(hw) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));  // Inizializzo il generatore di numeri casuali
}

int Simulatore::randomInt(int min, int max) {
    return min + std::rand() % (max - min + 1); // Ritorna un intero nell'intervallo [min, max]
}

double Simulatore::randomDouble(double min, double max) {
    return min + (max - min) * (std::rand() / static_cast<double>(RAND_MAX)); // Ritorna un double nell'intervallo [min, max]
}

std::string Simulatore::randomPlate() {  // Genera una targa casuale nel formato AA000AA
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
    Editor runs("runs.txt");    // Utilizzo la classe Editor per scrivere i file di output (in append)
    Editor pass("passages.txt");

    double tempoCorrente = 0.0; // Tempo globale del simulatore in secondi

    const auto& svincoli = m_hw.getSvincoli();
    const auto& varchi   = m_hw.getVarchi();   // Assumo ordinati per km

    for (int i = 0; i < VEICOLI; ++i) {

        std::string targa = randomPlate();  // Genero la targa del veicolo

        int ingresso = randomInt(0, static_cast<int>(svincoli.size()) - 2);
        int uscita   = randomInt(ingresso + 1, static_cast<int>(svincoli.size()) - 1);

        double kmIngresso = svincoli[ingresso].km;
        double kmUscita   = svincoli[uscita].km;

        double distanza = kmUscita - kmIngresso;

        // Scrivo i dati in Runs.txt su una riga
        std::string rigaRuns =
            targa + " " +
            std::to_string(svincoli[ingresso].id) + " " +
            std::to_string(svincoli[uscita].id) + " " +
            std::to_string(tempoCorrente) + " ";

        double percorso = 0.0;
        double tempoVeicolo = tempoCorrente;

        bool primo = true;

        // Mi posiziono sul primo varco >= ingresso, i varchi sono ordinati per km
        std::size_t idxVarco = 0;
        while (idxVarco < varchi.size() && varchi[idxVarco].km < kmIngresso) {
            idxVarco++;
        }

        while (percorso < distanza) {   // Genero il profilo di velocità del veicolo
            int velocita = randomInt(80, 190);
            int minuti   = randomInt(5, 15);
            double secondi = minuti * 60.0;

            double kmPercorsi = velocita * (secondi / 3600.0);

            double kmRimanenti = distanza - percorso;
            if (kmPercorsi > kmRimanenti) {
                kmPercorsi = kmRimanenti;   // Se supero la distanza, tronco il valore
                secondi = (kmPercorsi / velocita) * 3600.0;
            }

            if (!primo)
                rigaRuns += ", ";

            primo = false;
            rigaRuns += std::to_string(velocita) + " " + std::to_string((int)secondi);

            // Controllo passaggi ai varchi
            while (idxVarco < varchi.size() && varchi[idxVarco].km <= kmUscita) {
                double posizione = varchi[idxVarco].km - kmIngresso;    // km dal punto di ingresso

                // Se il varco è oltre il tratto corrente, lo controllo nel prossimo tratto
                if (posizione > percorso + kmPercorsi)
                    break;

                if (posizione >= percorso) {
                    double deltaT = (posizione - percorso) / velocita * 3600.0;

                    pass.writer(
                        std::to_string(varchi[idxVarco].id) + " " +
                        targa + " " +
                        std::to_string(tempoVeicolo + deltaT)
                    );
                }
                idxVarco++;
            }
            percorso += kmPercorsi;
            tempoVeicolo += secondi;
        }
        runs.writer(rigaRuns);
        tempoCorrente += randomDouble(0.5, 10.0);   // Incremento il tempo per la partenza del prossimo veicolo
    }
    // Chiusura dei file aperti in Editor
    runs.closer();
    pass.closer();
}
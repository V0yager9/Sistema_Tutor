#include "../include/autostrada.h"
#include "../include/simulatore.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

int main() {
    try {
        Autostrada hw;
        hw.caricaDaFile("data/highway.txt");

        std::cout << "File highway.txt caricato correttamente\n";

        Simulatore sim(hw);

        std::cout << "Avvio simulazione...\n";
        sim.run();

        std::cout << "File runs.txt generato\n";
        std::cout << "File passages.txt generato\n";
        std::cout << "Simulazione completata :)\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
        return 1;
    }
}
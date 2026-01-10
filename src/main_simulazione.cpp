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

        Simulatore sim(hw);
        sim.run();

        std::cout << "\n🚗 Simulazione completata!\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
        return 1;
    }
}

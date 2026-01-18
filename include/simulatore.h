// Autore: Michele Coffele

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "autostrada.h"
#include <string>

class Simulatore {
public:
    Simulatore(const Autostrada& hw);
    void run();

private:
    const int VEICOLI = 10000;

    const Autostrada& mhw;

    std::string randomTarga();

    int randomInt(int min, int max);
    double randomDouble(double min, double max);
};
#endif
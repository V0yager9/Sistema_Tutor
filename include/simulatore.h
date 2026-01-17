#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "autostrada.h"
#include <string>

class Simulatore {
public:
    explicit Simulatore(const Autostrada& hw);
    void run();

private:
    const Autostrada& mhw;

    std::string randomTarga();

    int randomInt(int min, int max);
    double randomDouble(double min, double max);
};
#endif
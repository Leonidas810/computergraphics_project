#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Pelota.hpp"
#include "Palo.hpp"

class Simulador {
public:
    Simulador(Pelota& pelota,Palo& palo, double tiempoTotal, double deltaTime);
    void simular();

private:
    Pelota &pelota;
    Palo &palo;
    double tiempoTotal;
    double deltaTime;
};

#endif

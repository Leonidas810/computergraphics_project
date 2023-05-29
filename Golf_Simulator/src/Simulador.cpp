#include <iostream>
#include "../include/Simulador.hpp"

// Simulador.cpp
Simulador::Simulador(Pelota& pelota,Palo& palo, double tiempoTotal, double deltaTime)
    : pelota(pelota),palo(palo), tiempoTotal(tiempoTotal), deltaTime(deltaTime) {
}

void Simulador::simular() {
    double tiempoActual = 0.0;

    while (tiempoActual < tiempoTotal) {
        pelota.actualizar(deltaTime);
        tiempoActual += deltaTime;
    }
}

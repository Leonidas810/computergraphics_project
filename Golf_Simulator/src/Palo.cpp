#include "../include/Palo.hpp"

Palo::Palo(Vertex posicion) {
    this->posicion = posicion;
}


Vertex Palo::getPosicion()  {
    return this->posicion;
}
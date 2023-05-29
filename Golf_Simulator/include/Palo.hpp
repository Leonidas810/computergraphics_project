#ifndef PALO_H
#define PALO_H

#include "Vertex.hpp"

class Palo {

private:
    Vertex posicion;
public:
    Palo(Vertex posicion);
    Vertex getPosicion();
};

#endif

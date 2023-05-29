#ifndef PELOTA_H
#define PELOTA_H

#include "Vertex.hpp"

class Pelota {

private:
    Vertex posicion;
    Vertex velocidad;
    double radio;
    double friccion;
    double gravedad;
    double masa;
public:
    Pelota(Vertex posicion, double radio);
    void actualizar(double dt);
    void setVelocidad( Vertex& velocidad);
    Vertex getPosicion();
    double getRadio();
};

#endif

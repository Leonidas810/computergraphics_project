#ifndef VERTEX_H
#define VERTEX_H

#pragma once

#include <armadillo>

class Vertex{
private:
    double x,y,z; //24 Bytes
public:
    // Constructor
    Vertex(){};
    Vertex(double x,double y,double z);

    // Operadores sobrecargados
    Vertex operator+(Vertex op);
    Vertex operator-(Vertex op);
    Vertex operator*(double op);

    // Métodos de acceso
    double getX();
    double getY();
    double getZ();

    // Métodos de modificación
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    // Otros métodos
    arma::Col<double> toHomogeneous();
    arma::vec::fixed<3> toArmaVec();
    void printf();
};

#endif
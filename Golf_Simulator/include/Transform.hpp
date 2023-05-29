#ifndef TRANSFORM_H
#define TRANSFORM_H

#pragma once

#include <armadillo>
#include "Vertex.hpp"

class Transform
{
public:
    Transform(){};
    arma::Mat<double> T(double dx, double dy, double dz);
    arma::Mat<double> S(double dx, double dy, double dz);
    arma::Mat<double> Rx(double theta);
    arma::Mat<double> Ry(double theta);
    arma::Mat<double> Rz(double theta);

    arma::Mat<double> Rp1p2(Vertex P1, Vertex P2,double theta);
private:

};

#endif
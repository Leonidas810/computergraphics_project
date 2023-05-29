#ifndef FACE_H
#define FACE_H

#pragma once

#include <vector>
#include "Edge.hpp"
#include <armadillo>

using namespace std;

class Face{
private:
    vector<Edge> edges;
    arma::vec normal;
    void  calc_normal();
public:
    Face(vector<Edge> edges);
    void printf();
    vector<Edge> get_edges();
    bool is_visible(float eye_X,float eye_Y,float eye_Z,arma::Mat<double> transf);
    arma::vec get_normal();
};


#endif
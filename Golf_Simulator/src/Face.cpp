#include <iostream>
#include "../include/Face.hpp"
#include "../include/Edge.hpp"

using namespace std;

Face::Face(vector<Edge> edges){
    this->edges=edges;
    this->calc_normal();
}
void Face::printf(){
    cout<<"{";
    for (Edge e:this->edges)
    {
        e.printf();
        cout<<", ";
    }
    cout<<"}";
}

vector<Edge> Face::get_edges(){
    return this->edges;
}

void Face::calc_normal() {
    arma::vec v1 = this->edges[0].get_vi().toArmaVec();
    arma::vec v2 = this->edges[1].get_vi().toArmaVec();
    arma::vec v3 = this->edges[2].get_vi().toArmaVec();
    this->normal = arma::normalise(arma::cross(v2-v1,v3-v1));
}

arma::vec Face::get_normal(){
    return this->normal;
}


bool Face::is_visible(float eye_X, float eye_Y, float eye_Z, arma::Mat<double> transf) {
    arma::vec dop = {eye_X, eye_Y, eye_Z};
    arma::vec dop_n = arma::normalise(dop);
    arma::vec normal_transf = arma::normalise(transf * arma::vec({this->normal(0), this->normal(1), this->normal(2)}));//terminate called after throwing an instance of 'std::logic_error'
    double visibility = 0.0;                                                                                           //what():  matrix multiplication: incompatible matrix dimensions: 4x4 and 3x1
    
    if (dop_n.size() == normal_transf.size()) {                                                                         //terminate called after throwing an instance of 'std::logic_error'
        visibility = arma::dot(dop_n, normal_transf);                                                                   //what():  dot(): objects must have the same number of elements
    } else {
        // Manejo del error, por ejemplo, lanzar una excepción o devolver un valor predeterminado
    }
    if (visibility < 0) {
        return true;
    } else {
        return false;
    }
}


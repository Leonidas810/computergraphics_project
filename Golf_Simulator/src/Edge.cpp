#include <iostream>
#include "../include/Edge.hpp"

using namespace std;

Edge::Edge(Vertex vi, Vertex vf){
    this->vi=vi;
    this->vf=vf;
}
void Edge::printf(){
    this->vi.printf();
    cout << "-";
    this->vf.printf();
}

Vertex Edge::get_vi(){
    return this->vi;
}

Vertex Edge::get_vf(){
    return this->vf;
}
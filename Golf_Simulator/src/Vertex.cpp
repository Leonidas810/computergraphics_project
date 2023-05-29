#include <iostream>
#include "../include/Vertex.hpp"

using namespace std;

Vertex::Vertex(double x,double y,double z){
    this->x=x;
    this->y=y;
    this->z=z;
}

Vertex Vertex::operator+(Vertex op){
    return Vertex(this->x+op.x,this->y+op.y,this->z+op.z);
}

Vertex Vertex::operator-(Vertex op){
    return Vertex(this->x-op.x,this->y-op.y,this->z-op.z);
}

Vertex Vertex::operator*(double op){
    return Vertex(this->x*op, this->y*op, this->z*op);
}

arma::Col<double> Vertex::toHomogeneous(){
    arma::Col<double> homg={this->x,this->y,this->z,1};
    return homg;
}

arma::vec::fixed<3> Vertex::toArmaVec() {
    arma::vec::fixed<3> armaVec;
    armaVec(0) = this->x;
    armaVec(1) = this->y;
    armaVec(2) = this->z;
    return armaVec;
}

double Vertex::getX(){
    return this->x;
}

double Vertex::getY(){
    return this->y;
}

double Vertex::getZ(){
    return this->z;  
}

void Vertex::setX(double newX){
    this->x=newX;
}

void Vertex::setY(double newY){
    this->y=newY;
}

void Vertex::setZ(double newZ){
    this->z=newZ;
}

void Vertex::printf(){
    cout<<"("<<this->x<<", "<<this->y<<", "<<this->z<<")"<<endl;
}

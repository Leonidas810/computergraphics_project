#ifndef MODELS_H
#define MODELS_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Face.hpp"

using namespace std;

class Models{
protected:
    Models(string fname);
    Models(){};
    string fname;
    vector <Vertex> vertices;
    vector <Face> faces;
    virtual void load()=0;
    vector <string> split(const string& str, const string& delim);
    double r,g,b;
    double ka;
    double kd;
public:
    void load_model(string fname);
    void line(Vertex vi,Vertex vf,double dt);
    void hermite(Vertex p1,Vertex p4,Vertex r1,Vertex r4,double dt);
    void bezier(Vertex p1,Vertex p2,Vertex p3,Vertex p4,double dt);
    vector<Face> get_faces();
    void set_material(double r,double g,double b,double ka,double kd);
    double get_r();
    double get_g();
    double get_b();
    double get_ka();
    double get_kd();
};

#endif
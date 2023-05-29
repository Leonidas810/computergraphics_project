#include <iostream>
#include "../include/Models.hpp"
#include <armadillo>

using namespace std;

Models::Models(string fname){
    this->fname=fname;
}

void Models::load_model(string fname){
    this->fname=fname;
    this->load();
}

vector<string> Models::split(const string& str, const string& delim){

    vector <string> tokens;
    size_t prev=0,pos=0;
    do{
        pos=str.find(delim,prev);
        if(pos==string::npos) pos=str.length();
        string token =str.substr(prev,pos-prev);
        if(!token.empty())tokens.push_back(token);
        prev=pos+delim.length();
    }
    while (pos<str.length() && prev < str.length());
    return tokens;
}

void Models::line(Vertex vi,Vertex vf,double dt){
    for (double t = 0.0; t <= 1.0; t+=dt)
    {
        Vertex v = vi + ((vf-vi) * t);
        cout<<"t= "<<t<<" ";
        v.printf();
        cout<<endl;
    }
}

void Models::hermite(Vertex p1,Vertex p4,Vertex r1,Vertex r4,double dt){
    arma::Mat<double> MH = {{2, -2, 1, 1},
                            {-3, 3, -2, -1},
                            {0, 0, 1, 0},
                            {1, 0, 0, 0}};

    arma::Mat<double> GH = {{p1.getX(), p1.getY(), p1.getZ()},
                            {p4.getX(), p4.getY(), p4.getZ()},
                            {r1.getX(), r1.getY(), r1.getZ()},
                            {r4.getX(), r4.getY(), r4.getZ()}};
    
    for (double t = 0.0; t <= 1; t += dt) {
        arma::Row<double> T = {pow(t, 3), pow(t, 2), t, 1};
        arma::Mat<double> Qt = T * MH * GH;
        Vertex v (Qt(0, 0), Qt(0, 1), Qt(0, 2));
        cout << "t = " << t << "\t";
        v.printf();
        cout << endl; 
    }
}

void Models::bezier(Vertex p1,Vertex p2,Vertex p3,Vertex p4,double dt){
    arma::Mat<double> MB = {{-1, 3,-3, 1},
                            {3, -6, 3, 0},
                            {-3, 3, 0, 0},
                            {1, 0, 0, 0}};

    arma::Mat<double> GB = {{p1.getX(), p1.getY(), p1.getZ()},
                            {p2.getX(), p2.getY(), p2.getZ()},
                            {p3.getX(), p3.getY(), p3.getZ()},
                            {p4.getX(), p4.getY(), p4.getZ()}};
    
    for (double t = 0.0; t <= 1; t += dt) {
        arma::Row<double> T = {pow(t, 3), pow(t, 2), t, 1};
        arma::Mat<double> Qt = T * MB * GB;
        Vertex v (Qt(0, 0), Qt(0, 1), Qt(0, 2));
        cout << "t = " << t << "\t";
        v.printf();
        cout << endl; 
    }
}

vector<Face> Models::get_faces(){
    return this->faces;
}

void Models::set_material(double r,double g,double b,double ka,double kd){
    this->r=r;
    this->g=g;
    this->b=b;
    this->ka=ka;
    this->kd=kd;
}

double Models::get_r(){
    return this->r;
}

double Models::get_g(){
    return this->g;
}

double Models::get_b(){
    return this->b;
}

double Models::get_ka(){
    return this->ka;
}

double Models::get_kd(){
    return this->kd;
}
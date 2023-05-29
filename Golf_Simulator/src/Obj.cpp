#include "../include/Obj.hpp"
#include "../include/Models.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Obj::Obj(string fname) : Models(fname){

    //Leer un archivo OBJ
    string line;
    this->vertices={};
    vector <Edge> edges={};
    this->faces={};

    ifstream archivoOBJ(fname);
    while (getline(archivoOBJ,line))
    {
        vector<string> elems=split(line," ");
        if(!elems.empty()){
            if(elems[0]=="v"){
                //Crear un objeto Vertice
                double x=stod(elems[1]);
                double y=stod(elems[2]);
                double z=stod(elems[3]);
                Vertex v(x,y,z);
                vertices.push_back(v);
            }
            if(elems[0]== "f"){
                vector<unsigned long> indices = {};
                for(unsigned long i=1; i<=elems.size()-1;i++)
                {
                    unsigned long ind = stol(split(elems[i], "/")[0]) - 1;
                    indices.push_back(ind);
                }
                for (int k = 0; k < indices.size() - 1; k++)
                {
                    edges.push_back(Edge(vertices[indices[k]], vertices[indices[k + 1]]));
                }
                edges.push_back(Edge(vertices[indices[indices.size() - 1]], vertices[indices[0]]));
                faces.push_back(Face(edges));
                edges.clear();
            }
        }
    }

    archivoOBJ.close();
}

void Obj::load()
{
    // implementación de la función load
    cout<<"Archivo obj cargado";
}
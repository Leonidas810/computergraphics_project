#include "../include/Ply.hpp"
#include "../include/Models.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


Ply::Ply(string fname) : Models(fname){

    //Leer un archivo Ply
    int i=0,j=0;
    string line;
    this->vertices={};
    vector <Edge> edges={};
    this->faces={};

    ifstream archivoPLY(fname);
    while (getline(archivoPLY,line))
    {
        if (line == "end_header") { // Fin de la sección de encabezado
        break;
        }else if (line.substr(0, 14) == "element vertex") { // Número de vértices
            stringstream ss(line.substr(15));
            ss >> num_vertices;
        }else if (line.substr(0, 12) == "element face") { // Número de caras
            stringstream ss(line.substr(13));
            ss >> num_faces;
        }
        
    }

    vertices.reserve(num_vertices);
    faces.reserve(num_faces);

    while (getline(archivoPLY,line))
    {
        vector<string> elems=split(line," ");
        if(!elems.empty()){
            if(i < num_vertices){
                //Crear un objeto Vertice
                double x=stod(elems[0]);
                double y=stod(elems[1]);
                double z=stod(elems[2]);
                Vertex v(x,y,z);
                vertices.push_back(v);
                i++;
            }else if(j < num_faces){
                stringstream ss(line);
                vector<unsigned long> indices = {};
                 unsigned long v;
                char num_v;
                while (ss >> num_v) {
                    while (ss >> v)
                    {
                    indices.push_back(v);
                    }
                }

                for (int k = 0; k < indices.size() - 1; k++)
                {
                    edges.push_back(Edge(vertices[indices[k]], vertices[indices[k + 1]]));
                }
                edges.push_back(Edge(vertices[indices[indices.size() - 1]], vertices[indices[0]]));
                faces.push_back(Face(edges));
                edges.clear();
                j++;
            }
        }
    }
    archivoPLY.close();
}

void Ply::load()
{
    // implementación de la función load
    cout<<"Archivo obj cargado";
}
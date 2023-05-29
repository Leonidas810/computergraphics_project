#ifndef EDGE_H
#define EDGE_H

#pragma once

#include "Vertex.hpp"

class Edge{
private:
    Vertex vi, vf;
public:
    Edge(Vertex vi, Vertex vf);
    void printf();
    Vertex get_vi();
    Vertex get_vf();
};

#endif
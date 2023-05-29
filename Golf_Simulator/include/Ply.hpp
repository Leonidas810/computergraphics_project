#ifndef PLY_H
#define PLY_H

#pragma once

#include "Models.hpp"
#include "Object.hpp"

using namespace std;

class Ply : public Models
{
private:
    int num_vertices = 0, num_faces = 0;
    void load();
public:
    Ply(string fname);
};

#endif
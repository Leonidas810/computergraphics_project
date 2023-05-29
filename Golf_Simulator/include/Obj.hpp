#ifndef OBJ_H
#define OBJ_H

#pragma once

#include "Models.hpp"
#include "Object.hpp"

using namespace std;

class Obj: public Models
{
private:
    void load();
public:
    Obj(string fname);
};

#endif
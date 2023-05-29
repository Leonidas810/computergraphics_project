#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include "Obj.hpp"
#include "Ply.hpp"


template <class T>
class Object:public T{
public:
    Object(string fname) : T(fname){}

};

#endif
#pragma once
#include "vector.hpp"
#include "ray.hpp"

class Primitive
{
  public:
    Vector position;

    virtual bool intersection(Ray ray, double &t);
};
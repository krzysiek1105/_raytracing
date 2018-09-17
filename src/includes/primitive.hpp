#pragma once
#include "vector.hpp"
#include "ray.hpp"

class Primitive
{
  public:
    Vector position;

    virtual bool intersection(Ray ray, double &t);
    virtual Vector get_normal(Vector &hit_point);
};
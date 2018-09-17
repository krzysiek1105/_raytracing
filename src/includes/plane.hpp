#pragma once
#include "primitive.hpp"

class Plane : public Primitive
{
  public:
    Vector normal;

    Plane();
    Plane(Vector _position, Vector _normal);
    ~Plane();

    bool intersection(Ray ray, double &t);
    Vector get_normal(Vector &hit_point);
};
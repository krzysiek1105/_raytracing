#pragma once
#include "primitive.hpp"

class Sphere : public Primitive
{
  public:
    double radius;

    Sphere();
    Sphere(Vector _position, double _radius);
    ~Sphere();
    bool intersection(Ray ray, double &t);
};
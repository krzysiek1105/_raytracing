#pragma once
#include "primitive.hpp"

class Triangle : public Primitive
{
  public:
    Vector normals[3];
    Vector vertices[3];

    Triangle(Vector _vertices[3], Vector _normals[3]);
    ~Triangle();

    bool intersection(Ray ray, double &t);
    Vector get_normal(Vector &hit_point);
};
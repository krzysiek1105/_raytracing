#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"

class Triangle
{
  public:
    Vector normals[3];
    Vector vertices[3];
    char material_name[64];

    Triangle(Vector _vertices[3], Vector _normals[3]);
    ~Triangle();

    bool intersection(Ray ray, double &t);
    Vector get_normal(Vector &hit_point);
};
#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include <string>
#include <cmath>

class Triangle
{
  public:
    Vector normals[3];
    Vector vertices[3];
    std::string material_name;

    Triangle(Vector _vertices[3], Vector _normals[3]);

    bool intersection(Ray ray, double &t);
    Vector getNormal(Vector &hit_point);
};
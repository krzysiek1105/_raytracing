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
  std::string materialName;

  Triangle(Vector vertices[3], Vector normals[3]);

  bool intersection(Ray ray, double &t) const;
  Vector getNormal(Vector &hitPoint) const;
};
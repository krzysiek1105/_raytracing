#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include <string>
#include <cmath>

double get_triangle_area(double a, double b, double c);

class Triangle
{
  public:
	Vector normals[3];
	Vector vertices[3];
	Vector tex_coor[3];
	std::string material_name;

	Triangle(Vector _vertices[3], Vector _normals[3], Vector _uv[3]);
	~Triangle();

	bool intersection(Ray ray, double &t);
	Vector get_normal(Vector &hit_point);
};
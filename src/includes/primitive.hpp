#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include <stdio.h>

class Primitive
{
  public:
	Vector position;

	virtual ~Primitive();
	virtual bool intersection(Ray ray, double &t);
	virtual Vector get_normal(Vector &hit_point);
};
#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "triangle.hpp"

#include <memory>
#include <vector>
#include <algorithm>

class AABB
{
  public:
	Vector min;
	Vector max;

	AABB(std::vector<Triangle> &triangles);
	bool ray_intersection(Ray ray);
};
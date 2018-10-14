#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "triangle.hpp"

#include <memory>
#include <vector>
#include <algorithm>
#include <utility>

class AABB
{
  public:
	Vector min;
	Vector max;

	AABB();
	AABB(std::vector<Triangle> &triangles);
	bool is_point_in_aabb(Vector &point);
	bool ray_intersection(Ray ray);
	void extend(Vector &point);
};
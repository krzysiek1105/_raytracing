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
	bool isPointInAABB(Vector &point) const;
	bool rayIntersection(Ray ray) const;
	void extend(Vector &point);
};
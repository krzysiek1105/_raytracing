#pragma once
#include "aabb.hpp"
#include "triangle.hpp"
#include <vector>
#include <array>

struct Node
{
    AABB aabb;
    std::vector<Triangle> triangles;
};

class Octtree
{
    public:
    std::array<Node, 8> nodes;
    Octtree();
    Octtree(std::vector<Triangle> &triangles);
};
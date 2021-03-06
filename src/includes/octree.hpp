#pragma once
#include "aabb.hpp"
#include "triangle.hpp"
#include <vector>
#include <array>

#define MAX_RECURSION_LEVEL 4
#define MAX_TRIANGLES_IN_NODE 16

struct Node
{
    AABB aabb;
    std::vector<Triangle> triangles;
    std::vector<Node> nodes;
    void split();
};

class Octree
{
    public:
    Node root;
    Octree();
    Octree(std::vector<Triangle> &triangles);
};
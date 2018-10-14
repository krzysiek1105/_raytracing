#pragma once
#include "ray.hpp"
#include "triangle.hpp"
#include "octtree.hpp"

Triangle *hit_info(Ray ray, Octtree &octtree, double &t)
{
    std::vector<Node *> nodes;
    for(Node &node : octtree.nodes)
        if(node.aabb.ray_intersection(ray))
            nodes.push_back(&node);

    double t_min = INFINITY;
    Triangle *hit = nullptr;

    for(auto &&node : nodes)
    {
        for(Triangle &triangle : node->triangles)
        {
            if (triangle.intersection(ray, t) && t < t_min)
            {
                t_min = t;
                hit = &triangle;
            }
        }
    }

    t = t_min;
    return hit;
}
#pragma once
#include "ray.hpp"
#include "triangle.hpp"
#include "octtree.hpp"

void find(std::vector<Node *> &nodes, Node &current, Ray ray)
{
    if(current.nodes.size() == 0)
        return;
    if(current.aabb.ray_intersection(ray))
        nodes.push_back(&current);
    for(int i = 0; i < 8; i++)
    {
        if(current.nodes[i].aabb.ray_intersection(ray))
            nodes.push_back(&current.nodes[i]);
        find(nodes, current.nodes[i], ray);
    }
}

Triangle *hit_info(Ray ray, Octtree &octtree, double &t)
{
    std::vector<Node *> nodes;
    find(nodes, octtree.root, ray);

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
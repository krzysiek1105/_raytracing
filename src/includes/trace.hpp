#pragma once
#include "ray.hpp"
#include "triangle.hpp"
#include "octree.hpp"

void find(std::vector<Node *> &nodes, Node &current, Ray ray)
{
    if (current.aabb.rayIntersection(ray))
        nodes.push_back(&current);
    for (Node &subnode : current.nodes)
    {
        if (subnode.aabb.rayIntersection(ray))
            nodes.push_back(&subnode);
        find(nodes, subnode, ray);
    }
}

Triangle *hitInfo(Ray ray, Octree &octree, double &t)
{
    std::vector<Node *> nodes;
    find(nodes, octree.root, ray);

    double t_min = INFINITY;
    Triangle *hit = nullptr;

    for (auto &&node : nodes)
    {
        for (Triangle &triangle : node->triangles)
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
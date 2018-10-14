#include "includes/octtree.hpp"

Octtree::Octtree(std::vector<Triangle> &triangles)
{
    AABB aabb(triangles);

    nodes[0].aabb = aabb;
    nodes[0].aabb.max.x /= 2;
    nodes[0].aabb.max.y /= 2;
    nodes[0].aabb.max.z /= 2;

    nodes[1].aabb = aabb;
    nodes[1].aabb.min.x = aabb.max.x / 2;
    nodes[1].aabb.max.y /= 2;
    nodes[1].aabb.max.z /= 2;

    nodes[2].aabb = aabb;
    nodes[2].aabb.max.x /= 2;
    nodes[2].aabb.min.y = aabb.max.y / 2;
    nodes[2].aabb.max.z /= 2;

    nodes[3].aabb = aabb;
    nodes[3].aabb.min.x = aabb.max.x / 2;
    nodes[3].aabb.min.y = aabb.max.y / 2;
    nodes[3].aabb.max.z /= 2;

    nodes[4].aabb = aabb;
    nodes[4].aabb.max.x /= 2;
    nodes[4].aabb.max.y /= 2;
    nodes[4].aabb.min.z = aabb.max.z / 2;

    nodes[5].aabb = aabb;
    nodes[5].aabb.min.x = aabb.max.x / 2;
    nodes[5].aabb.max.y /= 2;
    nodes[5].aabb.min.z = aabb.max.z / 2;

    nodes[6].aabb = aabb;
    nodes[6].aabb.max.x /= 2;
    nodes[6].aabb.min.y = aabb.max.y / 2;
    nodes[6].aabb.min.z = aabb.max.z / 2;

    nodes[7].aabb = aabb;
    nodes[7].aabb.min.x = aabb.max.x / 2;
    nodes[7].aabb.min.y = aabb.max.y / 2;
    nodes[7].aabb.min.z = aabb.max.z / 2;

    for(Triangle &triangle : triangles)
    {
        double min_dist = INFINITY;
        Node *n = NULL;
        
        for(Node &node : nodes)
        {
            Vector triangle_middle = (triangle.vertices[0] + triangle.vertices[1] + triangle.vertices[2]) * (1.0 / 3.0);
            Vector aabb_middle = node.aabb.min + ((node.aabb.max - node.aabb.min) * 0.5);

            double dist = triangle_middle.distance(aabb_middle);
            if(dist < min_dist)
            {
                min_dist = dist;
                n = &node;
            }
        }

        n->triangles.push_back(triangle);
        n->aabb.extend(triangle.vertices[0]);
        n->aabb.extend(triangle.vertices[1]);
        n->aabb.extend(triangle.vertices[2]);
    }
}
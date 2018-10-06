#include "includes/aabb.hpp"

AABB::AABB(std::vector<Triangle> &triangles)
{
    min = triangles[0].vertices[0];
    max = triangles[0].vertices[0];

    for(auto &&t : triangles)
    {
        double tmp;
        tmp = std::min(std::min(t.vertices[0].x, t.vertices[1].x), std::min(t.vertices[0].x, t.vertices[2].x));
        if(tmp < min.x)
            min.x = tmp;
        tmp = std::max(std::max(t.vertices[0].x, t.vertices[1].x), std::max(t.vertices[0].x, t.vertices[2].x));
        if(tmp > max.x)
            max.x = tmp;

        tmp = std::min(std::min(t.vertices[0].y, t.vertices[1].y), std::min(t.vertices[0].y, t.vertices[2].y));
        if(tmp < min.y)
            min.y = tmp;
        tmp = std::max(std::max(t.vertices[0].y, t.vertices[1].y), std::max(t.vertices[0].y, t.vertices[2].y));
        if(tmp > max.y)
            max.y = tmp;

        tmp = std::min(std::min(t.vertices[0].z, t.vertices[1].z), std::min(t.vertices[0].z, t.vertices[2].z));
        if(tmp < min.z)
            min.z = tmp;
        tmp = std::max(std::max(t.vertices[0].z, t.vertices[1].z), std::max(t.vertices[0].z, t.vertices[2].z));
        if(tmp > max.z)
            max.z = tmp;
    }

}
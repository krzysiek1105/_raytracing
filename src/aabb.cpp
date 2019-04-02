#include "includes/aabb.hpp"

AABB::AABB()
{
}

AABB::AABB(std::vector<Triangle> &triangles)
{
    min = triangles[0].vertices[0];
    max = triangles[0].vertices[0];

    for (auto &&t : triangles)
    {
        double tmp;
        tmp = std::min(std::min(t.vertices[0].x, t.vertices[1].x), std::min(t.vertices[0].x, t.vertices[2].x));
        if (tmp < min.x)
            min.x = tmp;
        tmp = std::max(std::max(t.vertices[0].x, t.vertices[1].x), std::max(t.vertices[0].x, t.vertices[2].x));
        if (tmp > max.x)
            max.x = tmp;

        tmp = std::min(std::min(t.vertices[0].y, t.vertices[1].y), std::min(t.vertices[0].y, t.vertices[2].y));
        if (tmp < min.y)
            min.y = tmp;
        tmp = std::max(std::max(t.vertices[0].y, t.vertices[1].y), std::max(t.vertices[0].y, t.vertices[2].y));
        if (tmp > max.y)
            max.y = tmp;

        tmp = std::min(std::min(t.vertices[0].z, t.vertices[1].z), std::min(t.vertices[0].z, t.vertices[2].z));
        if (tmp < min.z)
            min.z = tmp;
        tmp = std::max(std::max(t.vertices[0].z, t.vertices[1].z), std::max(t.vertices[0].z, t.vertices[2].z));
        if (tmp > max.z)
            max.z = tmp;
    }
}

bool AABB::isPointInAABB(Vector &point) const
{
    return (point.x <= max.x && point.x >= min.x) && (point.y <= max.y && point.y >= min.y) && (point.z <= max.z && point.z >= min.z);
}

void AABB::extend(Vector &point)
{
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    min.z = std::min(min.z, point.z);

    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
    max.z = std::max(max.z, point.z);
}

bool AABB::rayIntersection(Ray ray) const // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
{
    double tmin = (min.x - ray.origin.x) / ray.direction.x;
    double tmax = (max.x - ray.origin.x) / ray.direction.x;

    if (tmin > tmax)
        std::swap(tmin, tmax);

    double tymin = (min.y - ray.origin.y) / ray.direction.y;
    double tymax = (max.y - ray.origin.y) / ray.direction.y;

    if (tymin > tymax)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    double tzmin = (min.z - ray.origin.z) / ray.direction.z;
    double tzmax = (max.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax)
        std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}
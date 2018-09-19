#include "includes/plane.hpp"
#include <stdio.h>

Plane::Plane()
{
    position = Vector();
    normal = Vector(0.0, 1.0, 0.0);
}

Plane::Plane(Vector _position, Vector _normal)
{
    position = _position;
    normal = _normal;
}

Plane::~Plane()
{

}

bool Plane::intersection(Ray ray, double &t)
{
    Vector r_dir = -ray.direction;
    double dot = normal.dot_product(r_dir);
    if(dot <= 0.001)
        return false;

    Vector v = ray.origin - position;
    t = v.dot_product(normal) / dot;
    return t > 0.0;
}

Vector Plane::get_normal(Vector &hit_point)
{
    return normal;
}
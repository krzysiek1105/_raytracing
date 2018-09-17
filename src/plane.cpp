#include "includes/plane.hpp"

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
    Vector n = normal.normalized();
    Vector d = ray.direction.normalized();
    Vector o = ray.origin.normalized();
    Vector p = position.normalized();

    double dot = n.dot_product(d);
    if(dot <= 0.01)
        return false;

    Vector v = p - o;
    t = v.dot_product(n) / dot;
    return t > 0;
}

Vector Plane::get_normal(Vector &hit_point)
{
    return normal;
}
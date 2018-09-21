#include "includes/sphere.hpp"
#include <stdio.h>

Sphere::Sphere()
{
    position = Vector();
    radius = 1.0;
}

Sphere::Sphere(Vector _position, double _radius)
{
    position = _position;
    radius = _radius;
}

Sphere::~Sphere()
{
    printf("Sphere object destroyed\n");
}

bool Sphere::intersection(Ray ray, double &t)
{
    Vector v = ray.origin - position;
    double a = ray.direction.dot_product(ray.direction);
    double b = 2 * v.dot_product(ray.direction);
    double c = v.dot_product(v) - radius * radius;

    double delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;

    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);

    if (t1 < 0 && t2 < 0)
        return false;

    t = t1 < t2 ? (t1 >= 0 ? t1 : t2) : (t2 >= 0 ? t2 : t1);
    return true;
}

Vector Sphere::get_normal(Vector &hit_point)
{
    return (hit_point - position).normalized();
}
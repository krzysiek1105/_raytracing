#include "includes/primitive.hpp"

bool Primitive::intersection(Ray ray, double &t)
{
    return false;
}

Primitive::~Primitive()
{
    // printf("Primitive object destroyed\n");
}

Vector Primitive::get_normal(Vector &hit_point)
{
    return hit_point;
}
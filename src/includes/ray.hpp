#pragma once
#include "vector.hpp"

class Ray
{
    public:
    Vector origin;
    Vector direction;

    Ray(Vector _origin, Vector _direction);
    ~Ray();
};
#pragma once
#include "vector.hpp"

class Ray
{
    public:
    Vector origin;
    Vector direction;

    Ray(Vector origin, Vector direction);
};
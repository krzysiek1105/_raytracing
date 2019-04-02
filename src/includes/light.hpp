#pragma once
#include "vector.hpp"

class Light
{
    public:
    Vector direction;
    double intensity;

    Light(Vector direction, double intensity);
    double brightness(Vector normal);
};
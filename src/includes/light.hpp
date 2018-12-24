#pragma once
#include "vector.hpp"

class Light
{
    public:
    Vector direction;
    double intensity;

    Light(Vector _direction, double _intensity);
    double brightness(Vector normal);
};
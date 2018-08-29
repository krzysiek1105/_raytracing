#pragma once
#include "vector.hpp"

class Light
{
    public:
    Vector position;
    double intensity;

    Light(Vector _position, double _intensity);
    ~Light();
};
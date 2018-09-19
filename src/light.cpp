#include "includes/light.hpp"

Light::Light(Vector _direction, double _intensity)
{
    direction = _direction;
    intensity = _intensity;
}

Light::~Light()
{
}
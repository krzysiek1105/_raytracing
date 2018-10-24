#include "includes/light.hpp"

Light::Light(Vector _direction, double _intensity)
{
    direction = _direction;
    intensity = _intensity;
}

double Light::brightness(Vector normal)
{
    return (normal.dot_product(-direction) / (normal.length() * direction.length())) * intensity;
}

Light::~Light()
{
}
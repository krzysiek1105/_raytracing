#include "includes/light.hpp"

Light::Light(Vector _direction, double _intensity)
{
    direction = _direction;
    intensity = _intensity;
}

double Light::brightness(Vector normal)
{
    return (normal.dotProduct(-direction) / (normal.length() * direction.length())) * intensity;
}
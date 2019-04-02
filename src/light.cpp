#include "includes/light.hpp"

Light::Light(Vector direction, double intensity)
{
    this->direction = direction;
    this->intensity = intensity;
}

double Light::brightness(Vector normal) const
{
    return (normal.dotProduct(-direction) / (normal.length() * direction.length())) * intensity;
}
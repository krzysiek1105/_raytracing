#include "includes/light.hpp"

Light::Light(Vector _position, double _intensity)
{
    position = _position;
    intensity = _intensity;
}

Light::~Light()
{
}
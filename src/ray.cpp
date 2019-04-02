#include "includes/ray.hpp"

Ray::Ray(Vector origin, Vector direction)
{
    this->origin = origin;
    this->direction = direction;
}
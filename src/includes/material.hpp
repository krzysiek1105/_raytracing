#pragma once
#include <memory>
#include "texture.hpp"
#include "vector.hpp"
#include "triangle.hpp"

struct Color
{
    double r;
    double g;
    double b;
};

class Material
{
    public:
    Material();
    Color diffuse;
    Texture *texture_diffuse;
    Color get_diffuse(Vector uv[3], Vector hit_point);
};
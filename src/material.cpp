#include "includes/material.hpp"

Material::Material()
{
    texture_diffuse = nullptr;
}

Color Material::get_diffuse(Vector uv[3], Vector hit_point)
{
    if (texture_diffuse == nullptr)
        return diffuse;
    else
    {
        Color out = {0.0, 0.0, 0.0};

        double a = uv[0].distance(uv[1]);
        double b = uv[0].distance(uv[2]);
        double c = uv[1].distance(uv[2]);

        double d0 = hit_point.distance(uv[0]);
        double d1 = hit_point.distance(uv[1]);
        double d2 = hit_point.distance(uv[2]);

        double a2 = get_triangle_area(a, d0, d1);
        double a1 = get_triangle_area(b, d0, d2);
        double a0 = get_triangle_area(c, d1, d2);

        Vector v = (uv[0] * a0 + uv[1] * a1 + uv[2] * a2) / (a0 + a1 + a2);

        out.r = 3 * (v.x * texture_diffuse->width + (v.y * texture_diffuse->height) * texture_diffuse->height) + 0;
        out.g = 3 * (v.x * texture_diffuse->width + (v.y * texture_diffuse->height) * texture_diffuse->height) + 1;
        out.b = 3 * (v.x * texture_diffuse->width + (v.y * texture_diffuse->height) * texture_diffuse->height) + 2;
        return out;
    }
}
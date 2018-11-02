#pragma once

struct Color
{
    double r;
    double g;
    double b;
};

class Material
{
    public:
    char name[64];
    Color diffuse;
};
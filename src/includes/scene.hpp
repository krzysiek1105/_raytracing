#pragma once
#include <vector>
#include "camera.hpp"
#include "light.hpp"
#include "triangle.hpp"
#include "octtree.hpp"
#include "obj_parser.hpp"

class Scene
{
    public:
    std::vector<Triangle> triangles;
    std::vector<Light> lights;
    Camera camera;
    Octtree octtree;

    Scene(const char *file);
};
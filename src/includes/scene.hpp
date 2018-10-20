#pragma once
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstring>

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

    int background_color;

    int width;
    int height;
    int fov;

    Scene(const char *scene_filename);
};
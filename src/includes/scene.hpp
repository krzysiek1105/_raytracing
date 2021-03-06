#pragma once
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <string>
#include <unordered_map>

#include "camera.hpp"
#include "light.hpp"
#include "triangle.hpp"
#include "octree.hpp"
#include "obj_parser.hpp"
#include "material.hpp"

class Scene
{
    public:
    std::vector<Triangle> triangles;
    std::unordered_map<std::string, Material> materials;
    std::vector<Light> lights;
    Camera camera;
    Octree octtree;

    int backgroundColor;

    int width;
    int height;
    int fov;

    Scene(const char *scene_filename);
};
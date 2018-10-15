#include "includes/scene.hpp"

#define FOV 90
#define WIDTH 1920
#define HEIGHT 1080

Scene::Scene(const char *file)
{
    if (!load_obj_from_file(file, triangles))
        printf("Error: %s not found\n", file);

    octtree = Octtree(triangles);

    lights.push_back(Light(Vector(0.0, -1.0, 0.0), 0.5));
    lights.push_back(Light(Vector(0.0, -1.0, 1.0), 0.5));
    lights.push_back(Light(Vector(-1.0, 0.0, 0.0), 0.25));

    camera = Camera(WIDTH, HEIGHT, FOV, Vector(0.0, 1.0, 1.5), Vector(-45.0, 0.0, 0.0));
}
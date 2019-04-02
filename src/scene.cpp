#include "includes/scene.hpp"

Scene::Scene(const char *scene_filename)
{
    FILE *f = fopen(scene_filename, "r");
    if(f == nullptr)
        throw std::invalid_argument("Could not open scene file");

    Vector camPos = Vector();
    Vector camRot = Vector();

    while(!feof(f))
    {
        char line[128] = {0};
        fgets(line, 128, f);
        if(sscanf(line, "WIDTH=%d\n", &width) == 1) continue;
        else if(sscanf(line, "HEIGHT=%d\n", &height) == 1) continue;
        else if(sscanf(line, "FOV=%d\n", &fov) == 1) continue;
        else if(sscanf(line, "BACKGROUND=%d\n", &backgroundColor) == 1) continue;
        else if(sscanf(line, "CAMERA=%lf %lf %lf | %lf %lf %lf\n", &camPos.x, &camPos.y, &camPos.z, &camRot.x, &camRot.y, &camRot.z) == 6) continue;
        else
        {
            char tmp[64];
            if(sscanf(line, "OBJ=%s\n", tmp) == 1)
                if (!loadOBJFromFile(tmp, triangles, materials))
                    throw std::invalid_argument("Could not open OBJ file");

            double x, y, z, i;
            if(sscanf(line, "LIGHT=%lf %lf %lf | %lf\n", &x, &y, &z, &i) == 4)
                lights.push_back(Light(Vector(x, y, z), i));
        }
    }

    fclose(f);
    octtree = Octree(triangles);
    camera = Camera(width, height, fov, camPos, camRot);
}
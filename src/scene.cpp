#include "includes/scene.hpp"

Scene::Scene(const char *scene_filename)
{
    FILE *f = fopen(scene_filename, "r");
    if(f == nullptr)
        printf("Error: could not read %s\n", scene_filename);

    Vector cam_pos = Vector();
    Vector cam_rot = Vector();

    while(!feof(f))
    {
        char line[128] = {0};
        fgets(line, 128, f);
        if(sscanf(line, "WIDTH=%d\n", &width) == 1) continue;
        else if(sscanf(line, "HEIGHT=%d\n", &height) == 1) continue;
        else if(sscanf(line, "FOV=%d\n", &fov) == 1) continue;
        else if(sscanf(line, "CAMERA=%lf %lf %lf | %lf %lf %lf\n", &cam_pos.x, &cam_pos.y, &cam_pos.z, &cam_rot.x, &cam_rot.y, &cam_rot.z) == 6) continue;
        else
        {
            char tmp[64];
            if(sscanf(line, "OBJ=%s\n", tmp) == 1)
            {
                if (!load_obj_from_file(tmp, triangles))
                    printf("Error: %s not found\n", tmp);
                continue;
            }

            double x, y, z, i;
            if(sscanf(line, "LIGHT=%lf %lf %lf | %lf\n", &x, &y, &z, &i) == 4)
                lights.push_back(Light(Vector(x, y, z), i));
        }
    }

    fclose(f);
    octtree = Octtree(triangles);
    camera = Camera(width, height, fov, cam_pos, cam_rot);
}
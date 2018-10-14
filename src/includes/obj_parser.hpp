#pragma once
#include <stdio.h>
#include "triangle.hpp"

bool load_obj_from_file(const char *file_name, std::vector<Triangle> &triangles)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return false;

    std::vector<Vector> vertices;
    std::vector<Vector> normals;

    while (!feof(f))
    {
        char line[128] = {0};
        fgets(line, 128, f);
        if (line[0] == 'v' && line[1] != 'n')
        {
            double x, y, z;
            sscanf(line, "v %lf %lf %lf", &x, &y, &z);
            vertices.push_back(Vector(x, y, z));
        }
        else if (line[0] == 'v' && line[1] == 'n')
        {
            double x, y, z;
            sscanf(line, "vn %lf %lf %lf", &x, &y, &z);
            normals.push_back(Vector(x, y, z));
        }
        else if (line[0] == 'f')
        {
            int v1, n1, v2, n2, v3, n3;
            sscanf(line, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);

            Vector v[3];
            v[0] = vertices[v1 - 1];
            v[1] = vertices[v2 - 1];
            v[2] = vertices[v3 - 1];

            Vector n[3];
            n[0] = normals[n1 - 1];
            n[1] = normals[n2 - 1];
            n[2] = normals[n3 - 1];

            triangles.push_back(Triangle(v, n));
        }
    }

    fclose(f);
    return true;
}
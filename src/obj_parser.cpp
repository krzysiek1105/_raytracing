#include "includes/obj_parser.hpp"

bool loadMTLFromFile(const char *fileName, std::unordered_map<std::string, Material> &materials)
{
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
        return false;

    while (!feof(f))
    {
        char line[128] = {0};
        fgets(line, 128, f);
        if (strstr(line, "newmtl") != NULL)
        {
            char name[32] = {0};
            sscanf(line, "newmtl %s", name);
            strtok(name, "\n");

            Material tmp;

            fgets(line, 128, f);
            while (strstr(line, "illum") == NULL)
            {
                fgets(line, 128, f);
                if (strstr(line, "Kd") != NULL)
                    sscanf(line, "Kd %lf %lf %lf", &tmp.diffuse.r, &tmp.diffuse.g, &tmp.diffuse.b);
            }
            materials.insert({name, tmp});
        }
    }

    fclose(f);
    return true;
}

bool loadOBJFromFile(const char *fileName, std::vector<Triangle> &triangles, std::unordered_map<std::string, Material> &materials)
{
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
        return false;

    std::vector<Vector> vertices;
    std::vector<Vector> normals;

    char currentMat[64] = "none";
    while (!feof(f))
    {
        char line[128] = {0};
        fgets(line, 128, f);

        if (sscanf(line, "usemtl %s", currentMat) == 1)
            strtok(currentMat, "\n");

        double x, y, z;
        int v1, n1, v2, n2, v3, n3;
        char fName[32] = {0};

        if (sscanf(line, "v %lf %lf %lf", &x, &y, &z) == 3)
            vertices.push_back(Vector(x, y, z));
        else if (sscanf(line, "vn %lf %lf %lf", &x, &y, &z) == 3)
            normals.push_back(Vector(x, y, z));
        else if (sscanf(line, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3) == 6)
        {
            Vector v[3];
            v[0] = vertices[v1 - 1];
            v[1] = vertices[v2 - 1];
            v[2] = vertices[v3 - 1];

            Vector n[3];
            n[0] = normals[n1 - 1];
            n[1] = normals[n2 - 1];
            n[2] = normals[n3 - 1];

            Triangle t(v, n);
            t.materialName = currentMat;
            triangles.push_back(t);
        }
        else if (sscanf(line, "mtllib %s", fName) == 1)
        {
            strtok(fName, "\n");

            char path[64] = {0};
            strcpy(path, fileName);

            char *p = strrchr(path, '/');
            if (p != NULL)
                *p = '\0';
            strcat(path, "/");
            strcat(path, fName);

            if (!loadMTLFromFile(path, materials))
                return false;
        }
    }

    fclose(f);
    return true;
}
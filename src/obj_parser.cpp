#include "includes/obj_parser.hpp"

int findSeparatorInPath(const char *const path)
{
    if (path != NULL)
    {
        for (int i = strlen(path) - 1; i >= 0; i--)
            if (path[i] == '/' || path[i] == '\\')
                return i;
    }
    return -1;
}

bool loadMTLFromFile(const char *fileName, std::unordered_map<std::string, Material> &materials)
{
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
        return false;

    while (!feof(f))
    {
        char line[64] = {0};
        fgets(line, 64, f);
        if (strstr(line, "newmtl") != NULL)
        {
            char name[64] = {0};
            sscanf(line, "newmtl %63s", name);
            strtok(name, "\n");

            Material tmp;

            fgets(line, 64, f);
            while (strstr(line, "illum") == NULL)
            {
                fgets(line, 64, f);
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
        char line[64] = {0};
        fgets(line, 64, f);
        strtok(line, "\n");

        double x, y, z;
        int v1, n1, v2, n2, v3, n3;
        char fName[64] = {0};

        sscanf(line, "usemtl %63s", currentMat);
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
        else if (sscanf(line, "mtllib %63s", fName) == 1)
        {
            char path[64] = {0};
            int p = findSeparatorInPath(fileName);
            if (p != -1)
                memcpy(path, fileName, (p + 1) * sizeof(char));
            strcat(path, fName);

            if (!loadMTLFromFile(path, materials))
            {
                fclose(f);
                return false;
            }
        }
    }

    fclose(f);
    return true;
}
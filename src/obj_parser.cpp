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
        if (strstr(line, "newmtl") != nullptr)
        {
            char name[32] = {0};
            sscanf(line, "newmtl %s", name);
            strtok(name, "\n");

            Material tmp;

            fgets(line, 128, f);
            while (strstr(line, "illum") == nullptr)
            {
                fgets(line, 128, f);
                if (strstr(line, "Kd") != nullptr)
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
        if (strstr(line, "usemtl") != nullptr)
        {
            sscanf(line, "usemtl %s", currentMat);
            strtok(currentMat, "\n");
        }
        else if (line[0] == 'v' && line[1] != 'n')
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

            Triangle t(v, n);
            t.materialName = currentMat;
            triangles.push_back(t);
        }
        else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l' && line[4] == 'i' && line[5] == 'b') // wtf
        {

            char fName[32] = {0};
            sscanf(line, "mtllib %s", fName);
            strtok(fName, "\n");

            char path[64] = {0};
            strcpy(path, fileName);

            char *p = strrchr(path, '/');
            if (p != nullptr)
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
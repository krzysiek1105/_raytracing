#include "includes/obj_parser.hpp"

bool load_mtl_from_file(const char *file_name, std::unordered_map<std::string, Material> &materials)
{
    FILE *f = fopen(file_name, "r");
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

bool load_obj_from_file(const char *file_name, std::vector<Triangle> &triangles, std::unordered_map<std::string, Material> &materials)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return false;

    std::vector<Vector> vertices;
    std::vector<Vector> normals;

    char current_mat[64] = "none";
    while (!feof(f))
    {
        char line[128] = {0};

        fgets(line, 128, f);
        if (strstr(line, "usemtl") != nullptr)
        {
            sscanf(line, "usemtl %s", current_mat);
            strtok(current_mat, "\n");
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
            t.material_name = current_mat;
            triangles.push_back(t);
        }
        else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l' && line[4] == 'i' && line[5] == 'b') // wtf
        {

            char f_name[32] = {0};
            sscanf(line, "mtllib %s", f_name);
            strtok(f_name, "\n");

            char path[64] = {0};
            strcpy(path, file_name);

            char *p = strrchr(path, '/');
            if (p != nullptr)
                *p = '\0';
            strcat(path, "/");
            strcat(path, f_name);

            if (!load_mtl_from_file(path, materials))
                return false;
        }
    }

    fclose(f);
    return true;
}
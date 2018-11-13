#include "includes/obj_parser.hpp"

bool load_texture_from_file(const char *file_name, Texture *texture)
{
    FILE *f = fopen(file_name, "rb");
    if (f == NULL)
        return false;

    unsigned int w, h;
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    // if (w <= 0 || h <= 0)
    // {
    // fclose(f);
    // return false;
    // }

    while (!feof(f))
    {
        unsigned char tmp;
        fread(&tmp, sizeof(unsigned char), 1, f);
        texture->bitmap.push_back(tmp);
    }

    // if (texture->bitmap.size() != w * h * 3)
    // {
    // fclose(f);
    // return false;
    // }

    fclose(f);
    return true;
}

bool load_mtl_from_file(const char *file_name, std::unordered_map<std::string, Material> &materials)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return false;

    while (!feof(f))
    {
        char line[128] = {0};
        char name[32] = {0};
        fgets(line, 128, f);
        if (strstr(line, "newmtl") != nullptr)
        {
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
        else if (strstr(line, "map_Kd") != nullptr)
        {
            char f_name[32] = {0};
            sscanf(line, "map_Kd %s", f_name);
            strtok(f_name, "\n");

            char path[64] = {0};
            strcpy(path, file_name);

            char *p = strrchr(path, '/');
            if (p != nullptr)
                *p = '\0';
            strcat(path, "/");
            strcat(path, f_name);

            Texture *tmp = new Texture();
            if (!load_texture_from_file(path, tmp))
            {
                printf("Texture error\n");
                return false;
            }
            // auto mat = materials.find(name);
            // if (mat != materials.end())
                // mat->second.texture_diffuse = tmp;
            // else
                // printf("err %s", name);
            materials.begin()->second.texture_diffuse = tmp;
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
    std::vector<Vector> uv;

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
        else if (line[0] == 'v')
        {
            if (line[1] == 'n')
            {
                double x, y, z;
                sscanf(line, "vn %lf %lf %lf", &x, &y, &z);
                normals.push_back(Vector(x, y, z));
            }
            else if (line[1] == 't')
            {
                double u, v;
                sscanf(line, "vt %lf %lf", &u, &v);
                uv.push_back(Vector(u, v, 0.0));
            }
            else
            {
                double x, y, z;
                sscanf(line, "v %lf %lf %lf", &x, &y, &z);
                vertices.push_back(Vector(x, y, z));
            }
        }
        else if (line[0] == 'f')
        {
            Vector v[3];
            Vector n[3];
            Vector tex[3];
            int v1, t1, n1, v2, t2, n2, v3, t3, n3;

            if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3) == 9)
            {
                v[0] = vertices[v1 - 1];
                v[1] = vertices[v2 - 1];
                v[2] = vertices[v3 - 1];

                n[0] = normals[n1 - 1];
                n[1] = normals[n2 - 1];
                n[2] = normals[n3 - 1];

                tex[0] = uv[t1 - 1];
                tex[1] = uv[t2 - 1];
                tex[2] = uv[t3 - 1];
            }
            else if (sscanf(line, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3) == 6)
            {
                v[0] = vertices[v1 - 1];
                v[1] = vertices[v2 - 1];
                v[2] = vertices[v3 - 1];

                n[0] = normals[n1 - 1];
                n[1] = normals[n2 - 1];
                n[2] = normals[n3 - 1];
            }

            Triangle t(v, n, tex);
            t.material_name = current_mat;
            triangles.push_back(t);
        }
        else if (strstr(line, "mtllib") != nullptr)
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
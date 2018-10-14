#include "includes/light.hpp"
#include "includes/ray.hpp"
#include "includes/vector.hpp"
#include "includes/camera.hpp"
#include "includes/matrix.hpp"
#include "includes/triangle.hpp"
#include "includes/aabb.hpp"
#include "includes/octtree.hpp"

#include <vector>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <memory>
#include <algorithm>
#include <string>
#include <thread>
#include <array>
#include <stdlib.h>

#define FOV 90
#define WIDTH 1920
#define HEIGHT 1080
#define SHADOW_BIAS 0.01

Triangle *hit_info(Ray ray, Octtree &octtree, double &t)
{
    std::vector<Node *> nodes;
    for(Node &node : octtree.nodes)
        if(node.aabb.ray_intersection(ray))
            nodes.push_back(&node);

    double t_min = INFINITY;
    Triangle *hit = nullptr;

    for(auto &&node : nodes)
    {
        for(Triangle &triangle : node->triangles)
        {
            if (triangle.intersection(ray, t) && t < t_min)
            {
                t_min = t;
                hit = &triangle;
            }
        }
    }

    t = t_min;
    return hit;
}

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

void render(Octtree &octtree, std::vector<Light> &lights, Camera &camera, unsigned char **bitmap, int thread_id, int THREAD_COUNT)
{
    for (int y = thread_id; y < HEIGHT; y += THREAD_COUNT)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Ray ray = camera.camera_ray(x, y);

            double t;
            Triangle *hit = hit_info(ray, octtree, t);

            if (hit == nullptr)
                bitmap[y][x] = 32; // background has been hit
            else
            {
                Vector hit_point = ray.direction * t + ray.origin;
                Vector normal = hit->get_normal(hit_point);

                int color = 0;
                for (Light &l : lights)
                {
                    Vector l_dir = -l.direction.normalized();
                    double angle_cos = normal.dot_product(l_dir) / (normal.lenght() * l_dir.lenght());
                    int tmp = (int)(255 * angle_cos * l.intensity);

                    Vector shadow_point = normal * SHADOW_BIAS + hit_point;
                    Vector shadow_dir = l_dir.normalized();
                    Ray shadow_ray(shadow_point, shadow_dir);

                    Triangle *shadow_hit = hit_info(shadow_ray, octtree, t);
                    if (shadow_hit != nullptr && shadow_hit != hit)
                        continue;

                    color += std::clamp(tmp, 0, 255);
                }

                bitmap[y][x] = std::clamp(color, 0, 255);
            }
        }

        if (y % 16 == 0)
        {
            system("cls");
            printf("%.2f%%\n", 100.0f * y / HEIGHT);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        return 1;

    clock_t start = clock();

    std::vector<Triangle> triangles;
    if (!load_obj_from_file(argv[2], triangles))
    {
        printf("Error: %s not found\n", argv[2]);
        return 2;
    }

    std::vector<Light> lights;
    lights.push_back(Light(Vector(0.0, -1.0, 0.0), 0.5));
    lights.push_back(Light(Vector(0.0, -1.0, 1.0), 0.5));
    lights.push_back(Light(Vector(-1.0, 0.0, 0.0), 0.25));

    Camera camera(WIDTH, HEIGHT, FOV, Vector(3.0, 3.75, 3.0), Vector(-10.0, 70.0, 30.0));
    // Camera camera(WIDTH, HEIGHT, FOV, Vector(0.0, 1.0, 1.5), Vector(-45.0, 0.0, 0.0));

    Octtree octtree(triangles);

    FILE *f = fopen("o.raw", "wb");
    unsigned char **bitmap = new unsigned char *[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        bitmap[i] = new unsigned char[WIDTH];

    int THREAD_COUNT = atoi(argv[1]);
    std::vector<std::thread> threads;

    for (int i = 0; i < THREAD_COUNT; i++)
        threads.push_back(std::thread(render, std::ref(octtree), std::ref(lights), std::ref(camera), std::ref(bitmap), i, THREAD_COUNT));

    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i].join();

    for (int i = 0; i < HEIGHT; i++)
        fwrite(bitmap[i], sizeof(unsigned char), WIDTH, f);
    fclose(f);

    system("cls");
    printf("100.00%%\nt = %.3fs\n", (clock() - (double)start) / CLOCKS_PER_SEC);
    printf("Total triangles: %llu\n", triangles.size());
    for(int i = 0; i < 8; i++)
        printf("%llu ", octtree.nodes[i].triangles.size());
    return 0;
}
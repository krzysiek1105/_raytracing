#include "includes/light.hpp"
#include "includes/plane.hpp"
#include "includes/primitive.hpp"
#include "includes/ray.hpp"
#include "includes/sphere.hpp"
#include "includes/vector.hpp"
#include "includes/camera.hpp"
#include "includes/matrix.hpp"

#include <vector>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <memory>

#define FOV 90
#define WIDTH 1000
#define HEIGHT 1300
#define SHADOW_BIAS 0.01

Primitive *hit_info(Ray ray, std::vector<Primitive *> primitives, double &t)
{
    double t_min = INFINITY;
    Primitive *hit = nullptr;

    for (Primitive *p : primitives)
    {
        if (p->intersection(ray, t) && t < t_min)
        {
            t_min = t;
            hit = p;
        }
    }

    t = t_min;
    return hit;
}

int main()
{
    clock_t start = clock();

    std::vector<Primitive *> primitives;
    primitives.push_back(new Sphere(Vector(0.0, 0.0, -3.0), 1.0));
    primitives.push_back(new Sphere(Vector(0.1, -1.5, -3.0), 0.4));
    primitives.push_back(new Sphere(Vector(0.3, -0.5, -2.5), 0.4));
    primitives.push_back(new Sphere(Vector(0.0, 1.5, -2.75), 0.5));
    primitives.push_back(new Plane(Vector(0.0, -3.0, -7.0), Vector(0.0, 1.0, 0.0)));

    std::vector<Light> lights;
    lights.push_back(Light(Vector(0.0, 0.0, -1.0), 0.25));
    lights.push_back(Light(Vector(1.0, -1.0, -1.0), 0.5));

    Camera camera(WIDTH, HEIGHT, FOV, Vector(0.0, 0.0, 0.0), Vector(-5.0, 0.0, 0.0));

    FILE *f = fopen("o.raw", "wb");
    unsigned char **bitmap = new unsigned char *[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        bitmap[i] = new unsigned char[WIDTH];

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Ray ray = camera.camera_ray(x, y);

            double t;
            Primitive *hit = hit_info(ray, primitives, t);

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

                    Primitive *shadow_hit = hit_info(shadow_ray, primitives, t);
                    if (shadow_hit != nullptr && shadow_hit != hit)
                        tmp = 0;

                    if (tmp > 255)
                        tmp = 255;
                    if (tmp < 0)
                        tmp = 0;

                    color += tmp;
                }

                if (color > 255)
                    color = 255;
                if (color < 0)
                    color = 0;

                bitmap[y][x] = color;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++)
        fwrite(bitmap[i], sizeof(unsigned char), WIDTH, f);
    fclose(f);
    printf("t = %f\n", (clock() - (double)start) / CLOCKS_PER_SEC);
    return 0;
}
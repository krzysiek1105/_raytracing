#include "includes/light.hpp"
#include "includes/plane.hpp"
#include "includes/primitive.hpp"
#include "includes/ray.hpp"
#include "includes/sphere.hpp"
#include "includes/vector.hpp"

#include <vector>
#include <stdio.h>
#include <time.h>

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

    return hit;
}

int main()
{
    clock_t start = clock();

    std::vector<Primitive *> primitives;
    primitives.push_back(new Sphere(Vector(-1.0, 0.0, 3.0), 0.4));
    primitives.push_back(new Sphere(Vector(0.0, 0.0, 3.0), 1.0));
    primitives.push_back(new Sphere(Vector(0.1, -1.5, 3.0), 0.4));
    primitives.push_back(new Sphere(Vector(0.4, 2.0, 3.5), 0.75));

    std::vector<Light> lights;
    lights.push_back(Light(Vector(-5.0, -1.0, -3.0), 20.0));
    lights.push_back(Light(Vector(5.0, 1.0, -3.0), 20.0));
    lights.push_back(Light(Vector(0.0, -6.0, -2.0), 30.0));

    Vector origin(0.0, 0.0, -1.0);

    FILE *f = fopen("o.raw", "wb");
    unsigned char bitmap[HEIGHT][WIDTH] = {0};

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            double aspect_ratio = (double)WIDTH / HEIGHT;

            Vector point_on_plane(x / (double)WIDTH - 0.5, (y / (double)HEIGHT - 0.5) / aspect_ratio, 0.0);
            Vector dir = (point_on_plane - origin).normalized();
            Ray ray(origin, dir);

            double t;
            Primitive *hit = hit_info(ray, primitives, t);

            if (hit == nullptr)
                bitmap[y][x] = 32; // background has been hit
            else
            {
                Vector hit_point = ray.direction * t + ray.origin;
                Vector normal = (hit_point - hit->position).normalized();

                int color = 0;
                for (Light l : lights)
                {
                    double angle_cos = normal.dot_product(l.position) / (1.0 * l.position.lenght()); // normal.lenght() = 1.0
                    int tmp = (int)(255 * angle_cos * l.intensity / (l.position.distance(hit_point) * l.position.distance(hit_point)));

                    Vector shadow_point = normal * SHADOW_BIAS + hit_point;
                    Vector shadow_dir = (l.position - hit_point).normalized();
                    Ray shadow_ray(shadow_point, shadow_dir);

                    Primitive *shadow_hit = hit_info(shadow_ray, primitives, t);
                    Vector s_hit = shadow_dir * t + shadow_point;
                    if (shadow_hit != nullptr && shadow_hit != hit && s_hit.distance(hit_point) < l.position.distance(hit_point))
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

    fwrite(bitmap, sizeof(unsigned char), WIDTH * HEIGHT, f);
    fclose(f);
    printf("%f\n", (clock() - (double)start) / CLOCKS_PER_SEC);
    return 0;
}
#pragma once
#include "light.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "matrix.hpp"
#include "triangle.hpp"
#include "aabb.hpp"
#include "octtree.hpp"
#include "obj_parser.hpp"
#include "trace.hpp"

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
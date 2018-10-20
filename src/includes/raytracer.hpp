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
#include "scene.hpp"

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
#include <iostream>
#include <cstring>

#define SHADOW_BIAS 0.01

void render(Scene scene, std::vector<unsigned char> &bitmap, int thread_id, int thread_count)
{
    for (int y = thread_id; y < scene.camera.height; y += thread_count)
    {
        for (int x = 0; x < scene.camera.width; x++)
        {
            Ray ray = scene.camera.camera_ray(x, y);

            double t;
            Triangle *hit = hit_info(ray, scene.octtree, t);

            if (hit == nullptr)
                bitmap[y * scene.camera.width + x] = scene.background_color;
            else
            {
                Vector hit_point = ray.direction * t + ray.origin;
                Vector normal = hit->get_normal(hit_point);

                int color = 0;
                for (Light &l : scene.lights)
                {
                    Vector l_dir = -l.direction.normalized();
                    double angle_cos = normal.dot_product(l_dir) / (normal.lenght() * l_dir.lenght());
                    int tmp = (int)(255 * angle_cos * l.intensity);

                    Vector shadow_point = normal * SHADOW_BIAS + hit_point;
                    Vector shadow_dir = l_dir.normalized();
                    Ray shadow_ray(shadow_point, shadow_dir);

                    Triangle *shadow_hit = hit_info(shadow_ray, scene.octtree, t);
                    if (shadow_hit != nullptr && shadow_hit != hit)
                        continue;

                    color += std::clamp(tmp, 0, 255);
                }

                bitmap[y * scene.camera.width + x] = std::clamp(color, 0, 255);
            }
        }

        if (y % 16 == 0)
        {
            system("cls");
            printf("%.2f%%\n", 100.0f * y / scene.camera.height);
        }
    }
}
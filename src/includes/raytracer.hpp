#pragma once
#include "light.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "matrix.hpp"
#include "triangle.hpp"
#include "aabb.hpp"
#include "octree.hpp"
#include "obj_parser.hpp"
#include "trace.hpp"
#include "scene.hpp"
#include "material.hpp"

#include <vector>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <memory>
#include <algorithm>
#include <string>
#include <array>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <atomic>

#define SHADOW_BIAS 0.01

void render(Scene scene, std::vector<unsigned char> &bitmap, int thread_id, int thread_count, std::atomic<int> *pixels_done)
{
    for (int y = thread_id; y < scene.camera.height; y += thread_count)
    {
        for (int x = 0; x < scene.camera.width; x++)
        {
            Ray ray = scene.camera.camera_ray(x, y);

            double t;
            Triangle *hit = hit_info(ray, scene.octtree, t);

            if (hit == nullptr)
            {
                bitmap[3 * (y * scene.camera.width + x) + 0] = scene.background_color;
                bitmap[3 * (y * scene.camera.width + x) + 1] = scene.background_color;
                bitmap[3 * (y * scene.camera.width + x) + 2] = scene.background_color;
            }
            else
            {
                Vector hit_point = ray.direction * t + ray.origin;
                Vector normal = hit->get_normal(hit_point);

                Color color = {0.0, 0.0, 0.0};
                for (Light &l : scene.lights)
                {
                    Vector shadow_point = normal * SHADOW_BIAS + hit_point;
                    Vector shadow_dir = (-(l.direction)).normalized();
                    Ray shadow_ray(shadow_point, shadow_dir);

                    Triangle *shadow_hit = hit_info(shadow_ray, scene.octtree, t);
                    if (shadow_hit == nullptr)
                    {
                        double b = std::clamp(l.brightness(normal), 0.0, 1.0);

                        auto mat = scene.materials.find(hit->material_name);
                        if (mat != scene.materials.end())
                        {
                            color.r += mat->second.diffuse.r * b;
                            color.g += mat->second.diffuse.g * b;
                            color.b += mat->second.diffuse.b * b;
                        }
                        else
                        {
                            color.r += b;
                            color.g += b;
                            color.b += b;
                        }
                    }
                }
                bitmap[3 * (y * scene.camera.width + x) + 0] = std::clamp((int)(255 * color.r), 0, 255);
                bitmap[3 * (y * scene.camera.width + x) + 1] = std::clamp((int)(255 * color.g), 0, 255);
                bitmap[3 * (y * scene.camera.width + x) + 2] = std::clamp((int)(255 * color.b), 0, 255);
            }
            (*pixels_done)++;
        }
    }
}
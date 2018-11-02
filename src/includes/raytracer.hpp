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
                        if (scene.materials.size() > 0)
                        {
                            Material *mat = nullptr;
                            for (Material &m : scene.materials)
                            {
                                if (strcmp(m.name, hit->material_name) == 0)
                                {
                                    mat = &m;
                                    break;
                                }
                            }

                            color.r += std::clamp(mat->diffuse.r * l.brightness(normal), 0.0, 1.0);
                            color.g += std::clamp(mat->diffuse.g * l.brightness(normal), 0.0, 1.0);
                            color.b += std::clamp(mat->diffuse.b * l.brightness(normal), 0.0, 1.0);
                        }
                        else
                        {
                            color.r += std::clamp(1.0 * l.brightness(normal), 0.0, 1.0);
                            color.g += std::clamp(1.0 * l.brightness(normal), 0.0, 1.0);
                            color.b += std::clamp(1.0 * l.brightness(normal), 0.0, 1.0);
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
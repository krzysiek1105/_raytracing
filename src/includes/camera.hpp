#pragma once
#include "vector.hpp"
#include "ray.hpp"

class Camera
{
    public:
    int width;
    int height;
    int fov;
    Vector position;
    Vector rotation;

    private:
    double aspect_ratio;
    Vector origin;

    public:
    Camera(int _width, int _height, int _fov, Vector _position, Vector _rotation);
    Ray camera_ray(int x, int y);
    ~Camera();
};
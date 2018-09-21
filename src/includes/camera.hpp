#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"

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
    Matrix *rot_x;
    Matrix *rot_y;
    Matrix *rot_z;

    public:
    Camera(int _width, int _height, int _fov, Vector _position, Vector _rotation);
    Ray camera_ray(int x, int y);
    ~Camera();
};
#pragma once
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"

#define M_PI 3.14159265359

class Camera
{
  public:
    int width;
    int height;
    int fov;
    Vector position;
    Vector rotation;

  private:
    double aspectRatio;
    Vector origin;
    Matrix rot_x{3, 3};
    Matrix rot_y{3, 3};
    Matrix rot_z{3, 3};

  public:
    Camera();
    Camera(int _width, int _height, int _fov, Vector _position, Vector _rotation);
    Ray camera_ray(int x, int y);
};
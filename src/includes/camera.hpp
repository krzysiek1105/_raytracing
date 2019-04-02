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
    Matrix rotX{3, 3};
    Matrix rotY{3, 3};
    Matrix rotZ{3, 3};

  public:
    Camera();
    Camera(int width, int height, int fov, Vector position, Vector rotation);
    Ray cameraRay(int x, int y);
};
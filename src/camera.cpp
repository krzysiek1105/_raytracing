#include "includes/camera.hpp"

Camera::Camera(int _width, int _height, int _fov, Vector _position, Vector _rotation)
{
    width = _width;
    height = _height;
    fov = _fov;
    position = _position;
    rotation = _rotation;

    origin = Vector(position.x, position.y, position.z);
    aspect_ratio = (double)width / height;
}

Ray Camera::camera_ray(int x, int y)
{
    Vector point_on_screen((2 * ((x + 0.5) / (double)width) - 1) * aspect_ratio * tan(fov / 2 * M_PI / 180.0) + position.x, (1 - 2 * ((y + 0.5) / (double)height)) * tan(fov / 2 * M_PI / 180.0) + position.y, -1.0 + position.z);

    Vector dir = (point_on_screen - origin).normalized();
    return Ray(origin, dir);
}

Camera::~Camera()
{
}
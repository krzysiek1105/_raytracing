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

    double angle_x = rotation.x;
    double angle_y = rotation.y;
    double angle_z = rotation.z;

    rot_x = new Matrix(3, 3);
    rot_x->matrix[0][0] = 1.0;
    rot_x->matrix[0][1] = 0.0;
    rot_x->matrix[0][2] = 0.0;

    rot_x->matrix[1][0] = 0.0;
    rot_x->matrix[1][1] = cos(M_PI / 180.0 * angle_x);
    rot_x->matrix[1][2] = -sin(M_PI / 180.0 * angle_x);

    rot_x->matrix[2][0] = 0.0;
    rot_x->matrix[2][1] = sin(M_PI / 180.0 * angle_x);
    rot_x->matrix[2][2] = cos(M_PI / 180.0 * angle_x);

    rot_y = new Matrix(3, 3);
    rot_y->matrix[0][0] = cos(M_PI / 180.0 * angle_y);
    rot_y->matrix[0][1] = 0.0;
    rot_y->matrix[0][2] = sin(M_PI / 180.0 * angle_y);

    rot_y->matrix[1][0] = 0.0;
    rot_y->matrix[1][1] = 1.0;
    rot_y->matrix[1][2] = 0.0;

    rot_y->matrix[2][0] = -sin(M_PI / 180.0 * angle_y);
    rot_y->matrix[2][1] = 0.0;
    rot_y->matrix[2][2] = cos(M_PI / 180.0 * angle_y);

    rot_z = new Matrix(3, 3);
    rot_z->matrix[0][0] = cos(M_PI / 180.0 * angle_z);
    rot_z->matrix[0][1] = -sin(M_PI / 180.0 * angle_z);
    rot_z->matrix[0][2] = 0.0;

    rot_z->matrix[1][0] = sin(M_PI / 180.0 * angle_z);
    rot_z->matrix[1][1] = cos(M_PI / 180.0 * angle_z);
    rot_z->matrix[1][2] = 0.0;

    rot_z->matrix[2][0] = 0.0;
    rot_z->matrix[2][1] = 0.0;
    rot_z->matrix[2][2] = 1.0;
}

Ray Camera::camera_ray(int x, int y)
{
    Matrix a(3, 1);
    a.matrix[0][0] = (2 * ((x + 0.5) / (double)width) - 1) * aspect_ratio * tan(fov / 2 * M_PI / 180.0);
    a.matrix[1][0] = (1 - 2 * ((y + 0.5) / (double)height)) * tan(fov / 2 * M_PI / 180.0);
    a.matrix[2][0] = -1.0;

    Matrix out = *rot_z * (*rot_x * (*rot_y * a));
    Vector point_on_screen(out.matrix[0][0] + position.x, out.matrix[1][0] + position.y, out.matrix[2][0] + position.z);

    Vector dir = (point_on_screen - origin).normalized();
    return Ray(origin, dir);
}

Camera::~Camera()
{
}
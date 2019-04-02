#include "includes/camera.hpp"

Camera::Camera()
{
}

Camera::Camera(int width, int height, int fov, Vector position, Vector rotation)
{
    this->width = width;
    this->height = height;
    this->fov = fov;
    this->position = position;
    this->rotation = rotation;

    origin = Vector(position.x, position.y, position.z);
    aspectRatio = (double)width / height;

    double angle_x = rotation.x * (M_PI / 180.0);
    double angle_y = rotation.y * (M_PI / 180.0);
    double angle_z = rotation.z * (M_PI / 180.0);

    rotX.matrix[0][0] = 1.0;
    rotX.matrix[0][1] = 0.0;
    rotX.matrix[0][2] = 0.0;

    rotX.matrix[1][0] = 0.0;
    rotX.matrix[1][1] = cos(angle_x);
    rotX.matrix[1][2] = -sin(angle_x);

    rotX.matrix[2][0] = 0.0;
    rotX.matrix[2][1] = sin(angle_x);
    rotX.matrix[2][2] = cos(angle_x);

    rotY.matrix[0][0] = cos(angle_y);
    rotY.matrix[0][1] = 0.0;
    rotY.matrix[0][2] = sin(angle_y);

    rotY.matrix[1][0] = 0.0;
    rotY.matrix[1][1] = 1.0;
    rotY.matrix[1][2] = 0.0;

    rotY.matrix[2][0] = -sin(angle_y);
    rotY.matrix[2][1] = 0.0;
    rotY.matrix[2][2] = cos(angle_y);

    rotZ.matrix[0][0] = cos(angle_z);
    rotZ.matrix[0][1] = -sin(angle_z);
    rotZ.matrix[0][2] = 0.0;

    rotZ.matrix[1][0] = sin(angle_z);
    rotZ.matrix[1][1] = cos(angle_z);
    rotZ.matrix[1][2] = 0.0;

    rotZ.matrix[2][0] = 0.0;
    rotZ.matrix[2][1] = 0.0;
    rotZ.matrix[2][2] = 1.0;
}

Ray Camera::cameraRay(int x, int y) const
{
    Matrix a(3, 1);
    double angle = tan((fov / 2) * (M_PI / 180.0));
    a.matrix[0][0] = (2 * ((x + 0.5) / (double)width) - 1) * aspectRatio * angle;
    a.matrix[1][0] = (1 - 2 * ((y + 0.5) / (double)height)) * angle;
    a.matrix[2][0] = -1.0;

    Matrix d = rotY * a;
    Matrix c = rotX * d;
    Matrix out = rotZ * c;
    Vector point_on_screen(out.matrix[0][0] + position.x, out.matrix[1][0] + position.y, out.matrix[2][0] + position.z);

    Vector dir = (point_on_screen - origin).normalized();
    return Ray(origin, dir);
}
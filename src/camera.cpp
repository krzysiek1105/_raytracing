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

    double angleX = rotation.x * (M_PI / 180.0);
    double angleY = rotation.y * (M_PI / 180.0);
    double angleZ = rotation.z * (M_PI / 180.0);

    rotX.matrix[0][0] = 1.0;
    rotX.matrix[0][1] = 0.0;
    rotX.matrix[0][2] = 0.0;

    rotX.matrix[1][0] = 0.0;
    rotX.matrix[1][1] = cos(angleX);
    rotX.matrix[1][2] = -sin(angleX);

    rotX.matrix[2][0] = 0.0;
    rotX.matrix[2][1] = sin(angleX);
    rotX.matrix[2][2] = cos(angleX);

    rotY.matrix[0][0] = cos(angleY);
    rotY.matrix[0][1] = 0.0;
    rotY.matrix[0][2] = sin(angleY);

    rotY.matrix[1][0] = 0.0;
    rotY.matrix[1][1] = 1.0;
    rotY.matrix[1][2] = 0.0;

    rotY.matrix[2][0] = -sin(angleY);
    rotY.matrix[2][1] = 0.0;
    rotY.matrix[2][2] = cos(angleY);

    rotZ.matrix[0][0] = cos(angleZ);
    rotZ.matrix[0][1] = -sin(angleZ);
    rotZ.matrix[0][2] = 0.0;

    rotZ.matrix[1][0] = sin(angleZ);
    rotZ.matrix[1][1] = cos(angleZ);
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
    Vector pointOnScreen(out.matrix[0][0] + position.x, out.matrix[1][0] + position.y, out.matrix[2][0] + position.z);

    Vector dir = (pointOnScreen - origin).normalized();
    return Ray(origin, dir);
}
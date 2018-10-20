#include "includes/vector.hpp"

Vector::Vector()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector::Vector(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector Vector::operator+(Vector v)
{
    return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector Vector::operator-(Vector &v)
{
    return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector Vector::operator-()
{
    return Vector(-this->x, -this->y, -this->z);
}

Vector Vector::operator*(double value)
{
    return Vector(this->x * value, this->y * value, this->z * value);
}

double Vector::dot_product(Vector &v)
{
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector Vector::cross_product(Vector &v)
{
    return Vector(this->y * v.z - this->z * v.y, -(this->x * v.z - this->z * v.x), this->x * v.y - this->y * v.x);
}

double Vector::length()
{
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector Vector::normalized()
{
    return (*this) * (1.0 / this->length());
}

double Vector::distance(Vector &v)
{
    return sqrt((this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y) + (this->z - v.z) * (this->z - v.z));
}

Vector::~Vector()
{
}
#include "includes/vector.hpp"

Vector::Vector()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector::Vector(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::operator+(Vector v) const
{
    return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector Vector::operator-(Vector v) const
{
    return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector Vector::operator-() const
{
    return Vector(-this->x, -this->y, -this->z);
}

Vector Vector::operator*(double value) const
{
    return Vector(this->x * value, this->y * value, this->z * value);
}

Vector Vector::operator/(double value) const
{
    return Vector(this->x / value, this->y / value, this->z / value);
}

double Vector::dotProduct(Vector v) const
{
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector Vector::crossProduct(Vector v) const
{
    return Vector(this->y * v.z - this->z * v.y, -(this->x * v.z - this->z * v.x), this->x * v.y - this->y * v.x);
}

double Vector::length() const
{
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector Vector::normalized() const
{
    return (*this) * (1.0 / this->length());
}

double Vector::distance(Vector v) const
{
    return sqrt((this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y) + (this->z - v.z) * (this->z - v.z));
}
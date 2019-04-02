#pragma once
#include <cmath>

class Vector
{
  public:
    double x;
    double y;
    double z;

    Vector();
    Vector(double x, double y, double z);
    Vector operator+(Vector v) const;
    Vector operator-(Vector v) const;
    Vector operator-() const;
    Vector operator*(double value) const;
    Vector operator/(double value) const;
    double dotProduct(Vector v) const;
    Vector crossProduct(Vector v) const;
    double length() const;
    Vector normalized() const;
    double distance(Vector v) const;
};
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
    Vector operator+(Vector v);
    Vector operator-(Vector &v);
    Vector operator-();
    Vector operator*(double value);
    double dot_product(Vector &v);
    Vector cross_product(Vector &v);
    double lenght();
    Vector normalized();
    double distance(Vector &v);
    ~Vector();
};
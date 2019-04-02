#include "includes/triangle.hpp"

Triangle::Triangle(Vector _vertices[3], Vector _normals[3])
{
    vertices[0] = _vertices[0];
    vertices[1] = _vertices[1];
    vertices[2] = _vertices[2];

    normals[0] = _normals[0];
    normals[1] = _normals[1];
    normals[2] = _normals[2];
}

bool Triangle::intersection(Ray ray, double &t) // Möller–Trumbore intersection algorithm
{
    const double EPSILON = 0.0000001;

    Vector vertex0 = vertices[0];
    Vector vertex1 = vertices[1];
    Vector vertex2 = vertices[2];
    Vector edge1, edge2, h, s, q;

    double a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = ray.direction.crossProduct(edge2);
    a = edge1.dotProduct(h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1 / a;
    s = ray.origin - vertex0;
    u = f * (s.dotProduct(h));
    if (u < 0.0 || u > 1.0)
        return false;

    q = s.crossProduct(edge1);
    v = f * ray.direction.dotProduct(q);
    if (v < 0.0 || u + v > 1.0)
        return false;

    t = f * edge2.dotProduct(q);
    return t > EPSILON;
}

double get_triangle_area(double a, double b, double c)
{
    double p = (a + b + c) * 0.5;
    double area_squared = p * (p - a) * (p - b) * (p - c);
    if (area_squared < 0.0)
        return 0.0;
    return sqrt(area_squared);
}

Vector Triangle::getNormal(Vector &hit_point)
{
    double a = vertices[0].distance(vertices[1]);
    double b = vertices[0].distance(vertices[2]);
    double c = vertices[1].distance(vertices[2]);

    double d0 = hit_point.distance(vertices[0]);
    double d1 = hit_point.distance(vertices[1]);
    double d2 = hit_point.distance(vertices[2]);

    double a2 = get_triangle_area(a, d0, d1);
    double a1 = get_triangle_area(b, d0, d2);
    double a0 = get_triangle_area(c, d1, d2);

    return (normals[0] * a0 + normals[1] * a1 + normals[2] * a2) / (a0 + a1 + a2);
}
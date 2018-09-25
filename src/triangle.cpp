#include "includes/triangle.hpp"
#include <stdio.h>

Triangle::Triangle(Vector _vertices[3], Vector _normals[3])
{
    vertices[0] = _vertices[0];
    vertices[1] = _vertices[1];
    vertices[2] = _vertices[2];

    // Vector edge1 = vertices[1] - vertices[0];
    // Vector edge2 = vertices[2] - vertices[0];
    // normal = edge1.cross_product(edge2);

    // normal = _normal;

    normals[0] = _normals[0];
    normals[1] = _normals[1];
    normals[2] = _normals[2];
}

Triangle::~Triangle()
{
    // printf("triangle object destroyed\n");
}

// double AreaOfTriangle(double a, double b, double c)
// {
//     double p = (a + b + c) * 0.5;
//     double area_sqr = p * (p - a) * (p - b) * (p - c);

//     if (area_sqr < 0.0)
//     {
//         return 0.0;
//     }

//     return sqrt(area_sqr);
// }

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
    h = ray.direction.cross_product(edge2);
    a = edge1.dot_product(h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1 / a;
    s = ray.origin - vertex0;
    u = f * (s.dot_product(h));
    if (u < 0.0 || u > 1.0)
        return false;

    q = s.cross_product(edge1);
    v = f * ray.direction.dot_product(q);
    if (v < 0.0 || u + v > 1.0)
        return false;

    t = f * edge2.dot_product(q);
    return t > EPSILON;
}

Vector Triangle::get_normal(Vector &hit_point)
{
    // Vector out;

    // double dist0 = 1 / hit_point.distance(vertices[0]);
    // double dist1 = 1 / hit_point.distance(vertices[1]);
    // double dist2 = 1 / hit_point.distance(vertices[2]);
    // out = (normals[0] * dist0 + normals[1] * dist1 + normals[2] * dist2) * (dist0 + dist1 + dist2);
    // return out.normalized();

    Matrix v(4, 1);
    v.matrix[0][0] = hit_point.x;
    v.matrix[1][0] = hit_point.y;
    v.matrix[2][0] = hit_point.z;
    v.matrix[3][0] = 1.0;

    Matrix r(4, 4);
    r.matrix[0][0] = vertices[0].x;
    r.matrix[1][0] = vertices[0].y;
    r.matrix[2][0] = vertices[0].z;
    r.matrix[3][0] = 1.0;

    r.matrix[0][1] = vertices[1].x;
    r.matrix[1][1] = vertices[1].y;
    r.matrix[2][1] = vertices[1].z;
    r.matrix[3][1] = 1.0;

    r.matrix[0][2] = vertices[2].x;
    r.matrix[1][2] = vertices[2].y;
    r.matrix[2][2] = vertices[2].z;
    r.matrix[3][2] = 1.0;

    r.matrix[0][3] = 1.0;
    r.matrix[1][3] = 1.0;
    r.matrix[2][3] = 1.0;
    r.matrix[3][3] = 1.0;

    Matrix h = r.inverse() * v;
    return (normals[0] * h.matrix[0][0] + normals[1] * h.matrix[1][0] + normals[2] * h.matrix[2][0]).normalized();

    // double a = vertices[0].distance(vertices[1]);
    // double b = vertices[1].distance(vertices[2]);
    // double c = vertices[2].distance(vertices[0]);

    // double p0 = hit_point.distance(vertices[0]);
    // double p1 = hit_point.distance(vertices[1]);
    // double p2 = hit_point.distance(vertices[2]);

    // double n0 = AreaOfTriangle(b, p2, p1);
    // double n1 = AreaOfTriangle(c, p0, p2);
    // double n2 = AreaOfTriangle(a, p1, p0);

    // double n = n0 + n1 + n2;

    // return (normals[0] * n0 + normals[1] * n1 + normals[2] * n2) * (1 / n);
}
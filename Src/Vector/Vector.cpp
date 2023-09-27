#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vector.h"
#include "../Widget/Widget.h"

Vector::Vector(double x, double y, sf::Color color) :
x (x),
y (y),
color (color)
{}

Vector::~Vector()
{
    this->x = NAN;
    this->y = NAN;
}

void Vector::Dump()
{
    fprintf(stderr, "(%lf, %lf)\n", x, y);
}

Vector operator+(const Vector& a, const Vector& b)
{
    sf::Color new_color((a.color.r + b.color.r)/2, 
                        (a.color.g + b.color.g)/2,
                        (a.color.b + b.color.b)/2);

    Vector res = Vector(a.x + b.x, a.y + b.y, new_color);
    return res;
}

Vector operator-(const Vector& a)
{
    sf::Color new_color(255 - a.color.r, 
                        255 - a.color.g, 
                        255 - a.color.b);
    return Vector(-a.x, -a.y, new_color);
}

Vector operator-(const Vector& a, const Vector& b)
{
    return a + (-b);
}

Vector operator*(const Vector& a, double b)
{
    return Vector(a.x * b, a.y * b, a.color);
}

Vector operator/(const Vector& a, double b)
{
    return Vector(a.x / b, a.y / b, a.color);
}

double operator,(const Vector& a, const Vector& b)
{
    return a.x * b.x + a.y * b.y;
}

Vector operator!(const Vector& a)
{
    return Vector(a.x / a.Length(), a.y / a.Length());
}

Vector operator+(const Vector& a)
{
    sf::Color new_color(255 - a.color.r, 
                        255 - a.color.g, 
                        255 - a.color.b);
    return Vector(-a.y, a.x, new_color);
}

Vector operator^(const Vector& a, double b)
{
    Vector vec = a;
    vec.Rotate(-b);
    return vec;
}

static void DrawTriangleTip(Widget* window, CoordSystem* coord_sys, 
                            Vector* vec, double x0, double y0)
{
    double x1 = coord_sys->СoordRecalcX(vec->GetX() + x0);
    double y1 = coord_sys->СoordRecalcY(vec->GetY() + y0);

    Vector v0(coord_sys->СoordRecalcX(vec->GetX()), coord_sys->СoordRecalcY(vec->GetY()));

    Vector left_side  = -(!(v0)) * 10;
    Vector right_side = -(!(v0)) * 10;

    left_side.Rotate(0);
    right_side.Rotate(270);

    double vertex_coords[] = {x1, y1,
                              left_side.GetX() + x1, left_side.GetY() + y1,
                              right_side.GetX() + x1,right_side.GetY() + y1};

    sf::VertexArray tip(sf::Triangles, 3);
    for (int i = 0; i < 3; i++)
        tip[i] = sf::Vertex(sf::Vector2f(vertex_coords[i*2], vertex_coords[i*2 + 1]), vec->GetColor());

    window->DrawInside(tip);
}

void Vector::Draw(Widget* window, CoordSystem* coord_sys,  
                        double x0, double y0)
{
    DrawTriangleTip(window, coord_sys, this, x0, y0);

    double x1 = coord_sys->СoordRecalcX(x + x0);
    double y1 = coord_sys->СoordRecalcY(y + y0);

    x0 = coord_sys->СoordRecalcX(x0);
    y0 = coord_sys->СoordRecalcY(y0);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x0, y0), color),
        sf::Vertex(sf::Vector2f(x1, y1), color)
    };

    window->DrawInside(line, 2, sf::Lines);
}

void Vector::Rotate(double deg)
{
    double rad = M_PI / 180 * deg;

    double rot_x = cos(rad);
    double rot_y = sin(rad);

    double old_x = x;
    double old_y = y;
    x = old_x * rot_x - old_y * rot_y;
    y = old_y * rot_x + old_x * rot_y;
}

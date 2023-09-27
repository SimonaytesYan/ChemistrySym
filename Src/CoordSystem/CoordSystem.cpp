#include <cmath>

#include "CoordSystem.h"
#include "../Widget/Widget.h"

CoordSystem::CoordSystem(double X0, double Y0, double unit_X, double unit_Y) :
x0 (X0),
y0 (Y0),
unit_x (unit_X),
unit_y (unit_Y)
{}

CoordSystem::~CoordSystem()
{
    x0     = NAN;
    y0     = NAN;
    unit_x = NAN;
    unit_y = NAN;
}

double max(double a, double b)
{
    return (a < b) ? b : a;
}

double min(double a, double b)
{
    return (a < b) ? a : b;
}

void CoordSystem::Draw(Widget* window)
{
    Vector OX((window->GetSize().GetX()) / this->unit_x, 0);
    Vector OY(0, (window->GetSize().GetY()) / this->unit_y);

    OX.Draw(window, this, -x0 / unit_x, 0);
    OY.Draw(window, this, 0, -(window->GetSize().GetY() - y0) / unit_y);

    double r_x = max(unit_x / 30, min(2, unit_x));
    double r_y = max(unit_y / 30, min(2, unit_y));

    for (double x = x0; x < window->GetSize().GetX(); x += unit_x)
    {
        sf::CircleShape circle(r_x);
        circle.setPosition(x - r_x, y0 - r_x);

        window->DrawInside(circle);
    }

    for (double y = y0; y < window->GetSize().GetX(); y += unit_y)
    {
        sf::CircleShape circle(r_y);
        circle.setPosition(x0 - r_y, y - r_y);

        window->DrawInside(circle);
    }

    for (double x = x0; x > 0; x -= unit_x)
    {
        sf::CircleShape circle(r_x);
        circle.setPosition(x - r_x, y0 - r_x);

        window->DrawInside(circle);
    }

    for (double y = y0; y > 0; y -= unit_y)
    {
        sf::CircleShape circle(r_y);
        circle.setPosition(x0 - r_y, y - r_y);

        window->DrawInside(circle);
    }
}

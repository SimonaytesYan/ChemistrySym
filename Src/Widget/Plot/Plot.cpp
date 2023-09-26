#include "Plot.h"

Plot::Plot (double    _x0,
            double    _y0,
            double    _width,
            double    _height,
            double    coord_sys_x0,
            double    coord_sys_y0,
            double    coord_unit_x,
            double    coord_unit_y,
            sf::Color _plot_color, 
            double    _border_thickness,
            sf::Color _border_color) :
Widget (_x0, _y0, _width, _height, _border_thickness, _border_color),
coord_sys (CoordSystem(coord_sys_x0, coord_sys_y0, coord_unit_x, coord_unit_y)),
data (DynArray<Vector>(0)),
plot_color (_plot_color)
{}

void Plot::AddPoint(Vector point)
{
    data.PushBack(point);
}

void Plot::Draw(sf::RenderWindow* window)
{
    coord_sys.Draw(this);

    sf::VertexArray array(sf::Lines, (data.GetLength() - 1) * 2);

    for (int i = 1; i < data.GetLength(); i++)
    {
        //printf("x0, y0 = (%lg, %lg)\n", data[i].GetX(), data[i].GetY());
        
        double x1 = coord_sys.СoordRecalcX(data[i - 1].GetX());
        double y1 = coord_sys.СoordRecalcY(data[i - 1].GetY());
        double x2 = coord_sys.СoordRecalcX(data[i].GetX());
        double y2 = coord_sys.СoordRecalcY(data[i].GetY());

        array[2 * i - 2] = sf::Vertex(sf::Vector2f(x1, y1), plot_color);
        array[2 * i - 1] = sf::Vertex(sf::Vector2f(x2, y2), plot_color);

        //sf::CircleShape circle(1);
        //circle.setPosition(sf::Vector2f(x, y));
        //circle.setFillColor(plot_color);
    }

    this->DrawInside(array);
    Widget::Draw(window);
}

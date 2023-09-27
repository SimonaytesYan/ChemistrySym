#include "Plot.h"

const int kMaxTextLength = 50;

Plot::Plot (double      _x0,
            double      _y0,
            double      _width,
            double      _height,
            double      coord_sys_x0,
            double      coord_sys_y0,
            double      coord_unit_x,
            double      coord_unit_y,
            Vector      _plot_unit,
            sf::Font    _font,
            const char* _ox_string,
            const char* _oy_string,
            sf::Color   _plot_color, 
            double      _border_thickness,
            sf::Color   _border_color) :
Widget       (_x0, _y0, _width, _height, _border_thickness, _border_color),
coord_sys    (CoordSystem(coord_sys_x0, coord_sys_y0, coord_unit_x, coord_unit_y)),
data         (DynArray<Vector>(0)),
plot_color   (_plot_color),
plot_unit    (_plot_unit),
left_point_i (0),
font         (_font),
ox_string    (_ox_string),
oy_string    (_oy_string)
{}

void Plot::AddPoint(Vector point)
{
    if (data.GetLength() >= (GetSize().GetX() - coord_sys.GetX0()) / coord_sys.GetUnitX() * plot_unit.GetX())
    {
        int x = point.GetX() > data.GetLength() ? data.GetLength() : point.GetX();
        data[left_point_i] = Vector(x, point.GetY());

        left_point_i++;
        if (left_point_i >= data.GetLength())
            left_point_i = 0;

        for (int i = 0; i < data.GetLength(); i++)
        {
            data[i] = data[i] + Vector(-1, 0);
        }        
    }
    else
        data.PushBack(Vector(point.GetX(), point.GetY()));
}

Vector Plot::ReculcFromData(size_t index)
{
    double x = coord_sys.СoordRecalcX(data[index].GetX() / plot_unit.GetX());
    double y = coord_sys.СoordRecalcY(data[index].GetY() / plot_unit.GetY());
    
    return Vector(x, y);
}

void Plot::DrawPlotUnits()
{
    char string[kMaxTextLength] = {};
    sf::Text text_i;
	text_i.setFont(font);

    sprintf(string, ox_string);
	text_i.setString(string);
    text_i.setCharacterSize(15);
    text_i.setPosition(GetSize().GetX() - coord_sys.GetUnitX() * 3 / 4, coord_sys.GetY0());
    DrawInside(text_i);

    double y_i = plot_unit.GetY();
    double y0 = coord_sys.GetY0() - coord_sys.GetUnitY();
    for (double y = y0; y > 0; y   -= coord_sys.GetUnitY(), 
                               y_i += plot_unit.GetY())
    {
        char string[kMaxTextLength] = {};
        sf::Text text_i;
	    text_i.setFont(font);

        sprintf(string, "%.0lf", y_i);
	    text_i.setString(string);
        text_i.setCharacterSize(20);
        text_i.setPosition(coord_sys.GetX0(), y);

        DrawInside(text_i);
    }

    sprintf(string, oy_string);
	text_i.setString(string);
    text_i.setCharacterSize(15);
    text_i.setPosition(0, 0);
    DrawInside(text_i);
}

void Plot::Draw(sf::RenderWindow* window)
{
    coord_sys.Draw(this);

    if (data.GetLength() > 1)
    {
        sf::VertexArray array(sf::Lines, (data.GetLength() - 1) * 2);
        
        int array_i = 0;
        for (int i = left_point_i + 1; i < data.GetLength(); i++)
        {
            Vector v1 = ReculcFromData(i - 1);
            Vector v2 = ReculcFromData(i);
            
            array[array_i++] = sf::Vertex(v1, plot_color);
            array[array_i++] = sf::Vertex(v2, plot_color);
        }

        if (left_point_i != 0)
        {
            Vector v1 = ReculcFromData(data.GetLength() - 1);
            Vector v2 = ReculcFromData(0);

            array[array_i++] = sf::Vertex(v1, plot_color);
            array[array_i++] = sf::Vertex(v2, plot_color);

            for (int i = 1; i < left_point_i; i++)
            {
                Vector v1 = ReculcFromData(i - 1);
                Vector v2 = ReculcFromData(i);

                array[array_i++] = sf::Vertex(v1, plot_color);
                array[array_i++] = sf::Vertex(v2, plot_color);
            }
        }

        this->DrawInside(array);
    }

    DrawPlotUnits();

    Widget::Draw(window);
}

#include "Widget.h"
#include "../Vector/Vector.h"

void Widget::Draw(sf::RenderWindow* window)      //Clear Widget
{
    sf::RectangleShape frame(sf::Vector2f(this->texture.getSize().x - 2 * border_thickness, 
                                          this->texture.getSize().y - 2 * border_thickness));
    frame.setPosition(border_thickness, border_thickness);
    
    frame.setFillColor(sf::Color::Transparent);
    
    frame.setOutlineThickness(border_thickness);
    frame.setOutlineColor(border_color);

    this->texture.draw(frame);

    this->texture.display();

    sf::Sprite sprite(this->texture.getTexture());
	sprite.setPosition(GetX(), GetY());
    
	window->draw(sprite);
    
    this->texture.clear();
    
    texture.draw(sf::Sprite(background));
}


bool Widget::Inside_p(double x, double y)
{
    return (GetX() < x && x < GetX() + texture.getSize().x &&
            GetY() < y && y < GetY() + texture.getSize().y);
}

Widget::Widget(double x0, double y0, double width, double height,
               int border_thickness, sf::Color _border_color,
               sf::Texture _background) :
position (Vector(x0, y0)),
border_thickness (border_thickness),
background (_background),
border_color (_border_color)
{
    texture.create(width, height); 
    texture.draw(sf::Sprite(background));
}

double Widget::GetX() 
{
    return position.GetX();
}

double Widget::GetY() 
{
    return position.GetY();
} 

Widget::~Widget()
{
    position.~Vector();
    texture.~RenderTexture();
}

Vector Widget::GetSize()
{
    return Vector(texture.getSize().x, 
                  texture.getSize().y);
}

int Widget::GetBorderThick()
{
    return border_thickness;
}

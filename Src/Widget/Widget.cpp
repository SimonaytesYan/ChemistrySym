#include "Widget.h"
#include "../Vector/Vector.h"

void Widget::Draw(sf::RenderWindow* window)      //Clear Widget
{

    sf::RectangleShape frame(sf::Vector2f(this->texture.getSize().x - 2 * kThicknessWeight, 
                                          this->texture.getSize().y - 2 * kThicknessWeight));
    frame.setPosition(kThicknessWeight, kThicknessWeight);
    
    frame.setFillColor(sf::Color::Transparent);
    
    frame.setOutlineThickness(kThicknessWeight);
    frame.setOutlineColor(sf::Color(255, 255, 255));

    this->texture.draw(frame);

    this->texture.display();

    sf::Sprite sprite(this->texture.getTexture());
	sprite.setPosition(GetX(), GetY());
    
	window->draw(sprite);
    
    this->texture.clear();
}


bool Widget::Inside_p(double x, double y)
{
    return (GetX() < x && x < GetX() + texture.getSize().x &&
            GetY() < y && y < GetY() + texture.getSize().y);
}

Widget::Widget(double x0, double y0, double width, double height) :
position (Vector(x0, y0))
{
    texture.create(width, height); 
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
    return Vector(texture.getSize().x, texture.getSize().y);
}

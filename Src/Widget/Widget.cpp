#include "Widget.h"

void Widget::Draw(Widget* window)      //Clear Widget
{

    sf::RectangleShape frame(sf::Vector2f(this->getSize().x - 2 * kThicknessWeight, 
                                          this->getSize().y - 2 * kThicknessWeight));
    frame.setPosition(kThicknessWeight, kThicknessWeight);
    
    frame.setFillColor(sf::Color::Transparent);
    
    frame.setOutlineThickness(kThicknessWeight);
    frame.setOutlineColor(sf::Color(255, 255, 255));

    this->draw(frame);

    this->display();

    sf::Sprite sprite(this->getTexture());
	sprite.setPosition(this->x0, this->y0);
    
	window->draw(sprite);
    
    this->clear();
}


bool Widget::Inside_p(double x, double y)
{
    return (this->x0 < x && x < this->x0 + this->getSize().x &&
            this->y0 < y && y < this->y0 + this->getSize().y);
}

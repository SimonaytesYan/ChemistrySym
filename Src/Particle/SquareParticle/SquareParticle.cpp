#include "SquareParticle.h"

#include "../../Widget/Flask/Flask.h"

void SquareParticle::Draw(Flask *flask)
{
    sf::RectangleShape shape(sf::Vector2f(2 * GetR(), 2 * GetR()));

    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position.GetX(), position.GetY());

    flask->DrawInside(shape);

    ChangePosition(flask);
}

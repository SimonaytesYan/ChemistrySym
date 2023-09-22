#include "SquareParticle.h"

#include "../../Widget/Flask/Flask.h"

void SquareParticle::Draw(Flask *flask)
{
    sf::RectangleShape shape(sf::Vector2f(2 * r, 2 * r));

    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position.GetX(), position.GetY());

    flask->DrawInside(shape);

    ChangePosition(flask);
}

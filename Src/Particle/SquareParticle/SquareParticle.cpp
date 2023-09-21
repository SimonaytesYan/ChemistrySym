#include "SquareParticle.h"

#include "../../Widget/Flask/Flask.h"

void SquareParticle::Draw(Flask *flask)
{
    sf::RectangleShape shape(sf::Vector2f(r, r));

    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position.GetX(), position.GetY());

    flask->DrawInside(shape);

    ChangePosition(flask);
}

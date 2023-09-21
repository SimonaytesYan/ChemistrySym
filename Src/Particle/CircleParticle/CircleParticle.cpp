#include "CircleParticle.h"

void CircleParticle::Draw(Flask &flask)
{
    sf::CircleShape shape(r);

    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position.GetX(), position.GetY());

    flask.DrawInside(shape);

    ChangePosition(flask);
}

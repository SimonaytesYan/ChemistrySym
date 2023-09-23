#include "CircleParticle.h"
#include "../../Widget/Flask/Flask.h"

void CircleParticle::Draw(Flask* flask)
{
    sf::CircleShape shape(GetR());

    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position.GetX(), position.GetY());

    flask->DrawInside(shape);

    ChangePosition(flask);
}

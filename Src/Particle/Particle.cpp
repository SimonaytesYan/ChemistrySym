#include "Particle.h"
#include "../Widget/Flask/Flask.h"

void Particle::ChangePosition(Flask* flask)
{
    position = position + speed * flask->GetTick();

    if (position.GetX() < 0 || flask->GetSize().GetX() < position.GetX())
        speed = Vector(-speed.GetX(), speed.GetY());

    if (position.GetY() < 0 || flask->GetSize().GetY() < position.GetY())
        speed = Vector(speed.GetX(), -speed.GetY());
}

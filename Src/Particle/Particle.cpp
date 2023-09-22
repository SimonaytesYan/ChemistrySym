#include "Particle.h"
#include "../Widget/Flask/Flask.h"

void Particle::ChangePosition(Flask* flask)
{
    position = position + speed * flask->GetTick();

    if (position.GetX() < flask->GetBorderThick() || 
        position.GetX() > flask->GetSize().GetX() - flask->GetBorderThick() - r * 2)
        speed = Vector(-speed.GetX(), speed.GetY());

    if (position.GetY() < flask->GetBorderThick() || 
        position.GetY() > flask->GetSize().GetY() - flask->GetBorderThick() - r * 2)
        speed = Vector(speed.GetX(), -speed.GetY());
}

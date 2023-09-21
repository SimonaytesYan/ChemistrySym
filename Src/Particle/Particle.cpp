#include "Particle.h"

void Particle::ChangePosition(Flask& flask)
{
    position = position + speed * flask.GetTick();

    //TODO Столкновение с границами
}
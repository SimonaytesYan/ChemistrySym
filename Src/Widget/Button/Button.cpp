#include "Button.h"

#include "../../Particle/CircleParticle/CircleParticle.h"
#include "../../Particle/SquareParticle/SquareParticle.h"

void IncreaseTemperature(Flask* flask)
{

}

void DecreaseTemperature(Flask* flask)
{

}

void AddSquareParticle(Flask* flask)
{
    Vector pos  (rand() % (int)flask->GetSize().GetX(), 
			     rand() % (int)flask->GetSize().GetY());
    Vector speed((0.5 - rand() / RAND_MAX) / 2, 
				 (0.5 - rand() / RAND_MAX) / 2);

    flask->AddParticle(new SquareParticle(pos, speed, 10, 2));
}

void AddCircleParticle(Flask* flask)
{
    Vector pos  (rand() % (int)flask->GetSize().GetX(), 
			     rand() % (int)flask->GetSize().GetY());
    Vector speed((0.5 - rand() / RAND_MAX) / 2, 
				 (0.5 - rand() / RAND_MAX) / 2);

    flask->AddParticle(new CircleParticle(pos, speed, 10));
}

void RaisePistole(Flask* flask)
{

}

void DropPistole(Flask* flask)
{

}


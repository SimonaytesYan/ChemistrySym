#include "Button.h"

#include "../../Particle/CircleParticle/CircleParticle.h"
#include "../../Particle/SquareParticle/SquareParticle.h"

void IncreaseTemperature(Flask* flask)
{
    flask->ChangeTemp(1);
}

void DecreaseTemperature(Flask* flask)
{
    flask->ChangeTemp(-1);
}

void AddSquareParticle(Flask* flask)
{
    Vector pos  (rand() % (int)flask->GetSize().GetX(), 
			     rand() % (int)flask->GetSize().GetY());
    Vector speed(rand() / (double)RAND_MAX - 0.5, 
				 rand() / (double)RAND_MAX - 0.5);

    flask->AddParticle(new SquareParticle(pos, speed, 10, 2));
}

void AddCircleParticle(Flask* flask)
{
    Vector pos  (rand() % (int)flask->GetSize().GetX(), 
			     rand() % (int)flask->GetSize().GetY());
    Vector speed(rand() / (double)RAND_MAX - 0.5, 
				 rand() / (double)RAND_MAX - 0.5);

    flask->AddParticle(new CircleParticle(pos, speed, 10));
}

void RaisePistole(Flask* flask)
{

}

void DropPistole(Flask* flask)
{

}


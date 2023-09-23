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

    flask->AddParticle(new SquareParticle(pos, speed));
}

void AddCircleParticle(Flask* flask)
{
    Vector pos  (rand() % (int)flask->GetSize().GetX(), 
			     rand() % (int)(flask->GetSize().GetY() - flask->GetPistonHeight()) 
                 + flask->GetPistonHeight());
    Vector speed(rand() / (double)RAND_MAX - 0.5, 
				 rand() / (double)RAND_MAX - 0.5);

    flask->AddParticle(new CircleParticle(pos, speed));
}

void RaisePistole(Flask* flask)
{
    flask->ChangePistonHeight(10);
}

void DropPistole(Flask* flask)
{
    flask->ChangePistonHeight(-10);
}


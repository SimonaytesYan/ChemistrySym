#include <SFML/Graphics.hpp>

#include "Widget/Flask/Flask.h"
#include "Particle/CircleParticle/CircleParticle.h"
#include "Particle/SquareParticle/SquareParticle.h"

int main()
{
    Flask flask(0, 0, 800, 800);
    flask.AddParticle(CircleParticle(Vector(100, 100), Vector(0, 0), 20));
}
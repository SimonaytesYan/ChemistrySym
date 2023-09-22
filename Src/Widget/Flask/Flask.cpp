#include "Flask.h"

Flask::Flask(double _x0,
             double _y0,
             double _width,
             double _height,
             double _piston_height, 
             double _tick) : 
Widget(_x0, _y0, _width, _height),
piston_height(_piston_height),
tick         (_tick),
particles    (DynArray<Particle*>(0))
{}

void Flask::AddParticle(Particle* particle)
{
    particles.PushBack(particle);
}

void Flask::Draw(sf::RenderWindow* window)
{
    for (int i = 0; i < particles.GetLength(); i++)
        particles[i]->Draw(this);

    Widget::Draw(window);
}
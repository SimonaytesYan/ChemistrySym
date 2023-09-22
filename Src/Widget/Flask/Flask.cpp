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

template <class T>
void Swap(T* a, T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}

void Flask::Draw(sf::RenderWindow* window)
{
    //fprintf(stderr, "Start draw\n");
    int particles_number = particles.GetLength();

    for (int i = 0; i < particles_number; i++)
    {
        particles[i]->Draw(this);
    }

    Widget::Draw(window);

    for (int i = 0; i < particles_number; i++)
    {
        for (int j = i + 1; j < particles_number; j++)
        {
            if (particles[i] == nullptr)
                break;
            if (particles[j] == nullptr)
                continue;

            CollideParticles(particles, i, j);
        }
    }

    int i = 0;
    for (i = 0; i < particles.GetLength(); i++)
    {
        if (particles[i] == nullptr)
        {   
            Swap(&particles[i], &particles[particles.GetLength() - 1]);
            particles.PopBack();
            i--;
        }
    }

    //fprintf(stderr, "End draw\n");
}

#include "Flask.h"

const double kBoltzmannConst = 1.38e-1;
const double kAccuracy       = 1e-6;

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
    int particles_number = particles.GetLength();

    for (int i = 0; i < particles_number; i++)
    {
        particles[i]->Draw(this);
    }

    sf::RectangleShape piston(sf::Vector2f(GetSize().GetX(), GetBorderThick() * 2));
    piston.setPosition(sf::Vector2f(GetX(), GetY() + piston_height));
    piston.setFillColor(sf::Color::Blue);

    DrawInside(piston);

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
}

//E = 3/2 * k * T

double Flask::CalcTemp()
{
    double t = 0;
    
    for (int i = 0; i < particles.GetLength(); i++)
    {
        t += particles[i]->GetM() * particles[i]->GetSpeed().Length() * 
                                    particles[i]->GetSpeed().Length() / 2;
    }

    t *= 3/2 * kBoltzmannConst / particles.GetLength();
    return t;
}

void Flask::ChangeTemp(double delta_t)
{
    delta_t *= 3/2 * kBoltzmannConst;

    for (int i = 0; i < particles.GetLength(); i++)
    {
        double v1 = particles[i]->GetSpeed().Length();
        double m  = particles[i]->GetM();

        if (sqrt(v1 * v1 + 2 * delta_t / m) > kAccuracy)
            particles[i]->ChangeSpeed(sqrt(v1 * v1 + 2 * delta_t / m));
    }
}

void Flask::ChangePistonHeight(double delta)
{
    piston_height += delta;
    if (piston_height < 0)
        piston_height = 0;
}

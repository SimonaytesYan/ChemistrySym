#include "Flask.h"

const double kBoltzmannConst = 138;
const double kAccuracy       = 1e-6;

Flask::Flask(double    _x0,
             double    _y0,
             double    _width,
             double    _height,
             double    _piston_height, 
             double    _tick,
             double    _border_thickness,
             sf::Color _border_color) : 
Widget       (_x0, _y0, _width, _height, _border_thickness, _border_color),
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

    sf::RectangleShape piston(sf::Vector2f(GetSize().GetX(), GetBorderThick()));
    piston.setPosition(sf::Vector2f(0, piston_height));
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

int Flask::CalcSquares()
{
    int result = 0;
    for (int i = 0; i < particles.GetLength(); i++)
        if (particles[i]->GetType() == SQUARE)
            result++;
    
    return result;
}

int Flask::CalcCircles()
{
    int result = 0;
    for (int i = 0; i < particles.GetLength(); i++)
        if (particles[i]->GetType() == CIRCLE)
            result++;
    
    return result;
}

//E = 3/2 * k * T

double Flask::CalcTemp()
{
    if (particles.GetLength() == 0)
        return 0;
    
    double t = 0;
    
    for (int i = 0; i < particles.GetLength(); i++)
    {
        t += particles[i]->GetM() * particles[i]->GetSpeed().Length() * 
                                    particles[i]->GetSpeed().Length() / 2;
    }

    t *= kBoltzmannConst / particles.GetLength();
    return t;
}

void Flask::ChangeTemp(double delta_t)
{
    delta_t /= kBoltzmannConst;

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

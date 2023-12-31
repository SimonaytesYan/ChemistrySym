#include "Particle.h"
#include "CircleParticle/CircleParticle.h"
#include "SquareParticle/SquareParticle.h"
#include "../Widget/Flask/Flask.h"
#include "../Vector/Vector.h"

#include <assert.h>

typedef void (*React)(DynArray<Particle*>&, size_t, size_t);

void Particle::ChangePosition(Flask* flask)
{
    position = position + speed * flask->GetTick();

    double right_border  = flask->GetSize().GetX() - flask->GetBorderThick() - GetR() * 2;
    double bottom_border = flask->GetSize().GetY() - flask->GetBorderThick() - GetR() * 2;
    double top_border    = flask->GetBorderThick() + flask->GetPistonHeight();
    double left_border   = flask->GetBorderThick();

    if (position.GetX() < left_border)
    {
        position = Vector(left_border, position.GetY());

        if (speed.GetX() < 0)
            speed = Vector(-speed.GetX(), speed.GetY());
    }
    if (position.GetX() > right_border)
    {
        position = Vector(right_border, position.GetY());

        if (speed.GetX() > 0)
            speed = Vector(-speed.GetX(), speed.GetY());
    }

    if (position.GetY() < top_border)
    {
        position = Vector(position.GetX(), top_border);

        if (speed.GetY() < 0)
            speed = Vector(speed.GetX(), -speed.GetY());
    }
    
    if (position.GetY() > bottom_border)
    {
        position = Vector(position.GetX(), bottom_border);

        if (speed.GetY() > 0)
            speed = Vector(speed.GetX(), -speed.GetY());
    }
}

void Particle::ChangeSpeed(double new_speed_module)
{
    speed = !speed * new_speed_module;
}

void DeleteTwoParticles(DynArray<Particle*>& particles, size_t i, size_t j)
{
    delete particles[i];
    delete particles[j];

    particles[i] = nullptr;
    particles[j] = nullptr;
}

Vector SumSpeeds(Particle* a, Particle* b)
{
    double sum_mass = a->GetM() + b->GetM();

    Vector imp_a    = a->GetSpeed() * a->GetM();
    Vector imp_b    = b->GetSpeed() * b->GetM();

    return (imp_a + imp_b) / sum_mass;
}

SquareParticle* BumpParticles(Particle* a, Particle* b)
{
    return new SquareParticle((a->GetPosition() + b->GetPosition()) / 2,
                               SumSpeeds(a, b),
                               a->GetM() + b->GetM());
}

void ReactCircleCircle(DynArray<Particle*> &particles, size_t i, size_t j)
{
    assert(i != j);

    SquareParticle* result = BumpParticles(particles[i], particles[j]);

    DeleteTwoParticles(particles, i, j);
    particles.PushBack(result);
}

void ReactCircleRect(DynArray<Particle*> &particles, size_t i, size_t j)
{
    ReactCircleCircle(particles, i, j);
}

void ReactRectCircle(DynArray<Particle*> &particles, size_t i, size_t j)
{
    ReactCircleCircle(particles, i, j);
}

void ReactRectRect(DynArray<Particle*> &particles, size_t i, size_t j)
{
    SquareParticle* part_i = (SquareParticle*)particles[i];
    SquareParticle* part_j = (SquareParticle*)particles[j];
    
    int    sum_mass  = part_i->GetM() + part_j->GetM();
    Vector center    = (part_i->GetPosition() + part_j->GetPosition()) / 2;

    for (int i = 0; i < sum_mass; i++)
    {
        double deg = rand() % 360;

        Vector new_pos   = (Vector(part_i->GetR() * 5, 0) ^ deg) + center;
        Vector new_speed = (!(new_pos - center)) * (rand() + 1) / RAND_MAX;

        particles.PushBack(new CircleParticle(new_pos, new_speed, 1));
    }

    DeleteTwoParticles(particles, i, j);
}

void CollideParticles(DynArray<Particle*> &particles, size_t i, size_t j)
{
    static const React Table[2][2] = { {&ReactCircleCircle, &ReactCircleRect},
                                        {&ReactRectCircle,   &ReactRectRect}};

    Particle* part_i = particles[i];
    Particle* part_j = particles[j];

    if ((part_i->GetPosition() - part_j->GetPosition()).Length() < 
         part_i->GetR() + part_j->GetR())
    {
        (*Table[particles[i]->GetType()][particles[j]->GetType()])(particles, i, j);
    }
}

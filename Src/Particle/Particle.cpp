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

    double right_border  = flask->GetSize().GetX() - flask->GetBorderThick();
    double bottom_border = flask->GetSize().GetY() - flask->GetBorderThick();

    if (position.GetX()       < flask->GetBorderThick() && speed.GetX() < 0 || 
        position.GetX() + 2*r > right_border            && speed.GetX() > 0)
        speed = Vector(-speed.GetX(), speed.GetY());

    if (position.GetY() < flask->GetBorderThick() && speed.GetY() < 0 || 
        position.GetY() + 2*r > bottom_border     && speed.GetY() > 0)
        speed = Vector(speed.GetX(), -speed.GetY());
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
                               10,
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

        particles.PushBack(new CircleParticle(new_pos, new_speed, 10, 1));
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

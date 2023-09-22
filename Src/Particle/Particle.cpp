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

    if (position.GetX() < flask->GetBorderThick() || 
        position.GetX() > flask->GetSize().GetX() - flask->GetBorderThick() - r * 2)
        speed = Vector(-speed.GetX(), speed.GetY());

    if (position.GetY() < flask->GetBorderThick() || 
        position.GetY() > flask->GetSize().GetY() - flask->GetBorderThick() - r * 2)
        speed = Vector(speed.GetX(), -speed.GetY());
}

void DeleteTwoParticles(DynArray<Particle*>& particles, size_t i, size_t j)
{
    delete particles[i];
    delete particles[j];

    particles[i] = nullptr;
    particles[j] = nullptr;
}

void ReactCircleCircle(DynArray<Particle*> &particles, size_t i, size_t j)
{
    //fprintf(stderr, "Collide Circles\n");

    assert(i != j);

    CircleParticle* part_i = (CircleParticle*)particles[i];
    CircleParticle* part_j = (CircleParticle*)particles[j];

    double sum_mass = part_i->GetM() + part_j->GetM();
    Vector imp_i    = part_i->GetSpeed() * part_i->GetM();
    Vector imp_j    = part_j->GetSpeed() * part_j->GetM();
    SquareParticle* result = new SquareParticle((part_i->GetPosition() + part_j->GetPosition()) / 2,
                                                 (imp_i + imp_j) /sum_mass,
                                                 10,
                                                 sum_mass);

    DeleteTwoParticles(particles, i, j);

    particles.PushBack(result);
}

void ReactCircleRect(DynArray<Particle*> &particles, size_t i, size_t j)
{
    
}

void ReactRectCircle(DynArray<Particle*> &particles, size_t i, size_t j)
{

}


void ReactRectRect(DynArray<Particle*> &particles, size_t i, size_t j)
{
    
}

void CollideParticles(DynArray<Particle*> &particles, size_t i, size_t j)
{
    static const React Table[2][2] = { {&ReactCircleCircle, &ReactCircleRect},
                                        {&ReactRectCircle,   &ReactRectRect}};

    Particle* part_i = particles[i];
    Particle* part_j = particles[j];

    //fprintf(stderr, "Collide parts\n");


    if ((part_i->GetPosition() - part_j->GetPosition()).Length() < 
         part_i->GetR() + part_j->GetR())
    {
        (*Table[particles[i]->GetType()][particles[j]->GetType()])(particles, i, j);
    }

    //fprintf(stderr, "End collide\n");
}

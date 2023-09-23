#ifndef SYM_PARTICLE
#define SYM_PARTICLE

#include "../Vector/Vector.h"

#include "../DynArray.h"

class Flask;

enum ParticleTypes
{
    CIRCLE = 0,
    SQUARE = 1
};

const double kDensity = 1;

class Particle
{
protected :
    
    ParticleTypes type;
    Vector        position;
    Vector        speed;
    double        m;
    
public :

    Particle(ParticleTypes _type, 
            Vector _position = Vector(0, 0), 
            Vector _speed    = Vector(0, 0),
            double _m        = 0) :
    type (_type),
    position (_position),
    speed (_speed),
    m (_m)
    {};

    ParticleTypes GetType()     { return type;               };
    Vector        GetPosition() { return position;           };
    Vector        GetSpeed()    { return speed;              };
    double        GetR()        { return sqrt(m / kDensity); };
    double        GetM()        { return m;                  };

    virtual void Draw(Flask *flask) = 0;

    void ChangePosition(Flask *flask);
    void ChangeSpeed(double new_speed_module);
};

void CollideParticles(DynArray<Particle*> &particles, size_t i, size_t j);

#endif //SYM_PARTICLE
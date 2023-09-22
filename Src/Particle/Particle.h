#ifndef SYM_PARTICLE
#define SYM_PARTICLE

#include "../Vector/Vector.h"

class Flask;

enum ParticleTypes
{
    CIRCLE,
    SQUARE
};

class Particle
{
protected :
    
    ParticleTypes type;
    Vector        position;
    Vector        speed;
    double        r;
    
public :

    Particle(ParticleTypes _type, 
            Vector _position = Vector(0, 0), 
            Vector _speed    = Vector(0, 0), 
            double _r        = 0) :
    type (_type),
    position (_position),
    speed (_speed),
    r (_r)
    {};

    virtual void Draw(Flask *flask) = 0;

    void ChangePosition(Flask *flask);
};

#endif //SYM_PARTICLE
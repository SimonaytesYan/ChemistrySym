#ifndef SYM_CIRCLE_PARTICLE
#define SYM_CIRCLE_PARTICLE

#include "../Particle.h"

class CircleParticle : public Particle 
{
public :
    CircleParticle(Vector _position = Vector(0, 0), 
                   Vector _speed    = Vector(0, 0),
                   double _m        = 1) : 
    Particle(CIRCLE, _position, _speed, _m)
    {};

    void Draw(Flask *flask) override;
};

#endif //SYM_CIRCLE_PARTICLE
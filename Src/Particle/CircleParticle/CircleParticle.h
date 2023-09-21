#ifndef SYM_CIRCLE_PARTICLE
#define SYM_CIRCLE_PARTICLE

#include "../Particle.h"

class CircleParticle : public Particle 
{
    
    CircleParticle(Vector _position = Vector(0, 0), 
                   Vector _speed    = Vector(0, 0), 
                   double _r        = 0) : 
    Particle(CIRCLE, _position, _speed, r)
    {};

    void Draw(Flask &flask);
};

#endif //SYM_CIRCLE_PARTICLE
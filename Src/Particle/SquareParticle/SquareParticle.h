#ifndef SYM_SQUARE_PARTICLE
#define SYM_SQUARE_PARTICLE

#include "../Particle.h"

class SquareParticle : public Particle 
{
    
public:

    SquareParticle(Vector _position = Vector(0, 0), 
                   Vector _speed    = Vector(0, 0), 
                   double _r        = 0) : 
    Particle(SQUARE, _position, _speed, _r)
    {};

    void Draw(Flask* flask) override;
};

#endif //SYM_SQUARE_PARTICLE
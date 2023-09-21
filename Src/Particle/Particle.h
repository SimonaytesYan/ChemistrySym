#ifndef SYM_PARTICLE
#define SYM_PARTICLE

#include "../Vector/Vector.h"

enum ParticleTypes
{
    CIRCLE,
    SQUARE
};

class Particle
{
    Vector position;
    ParticleTypes type;
};

#endif //SYM_PARTICLE
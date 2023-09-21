#ifndef SYM_FLASK
#define SYM_FLASK

#include "../Widget.h"
#include "../../DynArray.h"
#include "../../Particle/Particle.h"

class Flask : Widget
{
    double piston_height = 0;

    DynArray<Particle> particles;
}

#endif //SYM_FLASK
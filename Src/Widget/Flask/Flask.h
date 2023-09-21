#ifndef SYM_FLASK
#define SYM_FLASK

#include "../Widget.h"
#include "../../DynArray.h"
#include "../../Particle/Particle.h"

class Flask : public Widget
{
    double piston_height = 0;
    double tick          = 0;   //time between drawing
    DynArray<Particle> particles;

    public : 
    //TODO Конструктор

    double GetTick() { return tick; };
}

#endif //SYM_FLASK
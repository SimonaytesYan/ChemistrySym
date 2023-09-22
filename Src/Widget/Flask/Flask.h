#ifndef SYM_FLASK
#define SYM_FLASK

#include "../Widget.h"
#include "../../DynArray.h"
#include "../../Particle/Particle.h"

class Flask : public Widget
{
    DynArray<Particle*> particles;
    double              piston_height = 0;
    double              tick          = 0;   //time between drawing

public : 
    
    Flask(double _x0,
          double _y0,
          double _width,
          double _height,
          double _piston_height = 0, 
          double _tick          = 0.1);
    
    void Draw(sf::RenderWindow* window) override;

    double GetTick() { return tick; };
    void   AddParticle(Particle* particle);
};

#endif //SYM_FLASK
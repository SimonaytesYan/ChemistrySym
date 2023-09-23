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
    
    Flask(double    _x0,
          double    _y0,
          double    _width,
          double    _height,
          double    _piston_height    = 0, 
          double    _tick             = 0.1,
          double    _border_thickness = 10,
          sf::Color _border_color     = sf::Color::White);
    
    void Draw(sf::RenderWindow* window) override;
    
    double CalcTemp();
    void   ChangeTemp(double delta);
    void   ChangePistonHeight(double delta);

    void   AddParticle(Particle* particle);
    
    double GetTick        () { return tick;          };
    double GetPistonHeight() { return piston_height; };
};

#endif //SYM_FLASK
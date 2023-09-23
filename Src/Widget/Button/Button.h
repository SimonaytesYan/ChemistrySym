#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../Widget.h"
#include "../Flask/Flask.h"

typedef void (*OnClickFunction)(Flask* flask);

class Button : public Widget
{
public :

    OnClickFunction on_click;

    Button(double          _x0, 
           double          _y0, 
           double          _width, 
           double          _height,
           OnClickFunction on_click_func, 
           double          _border_thickness = 10,
           sf::Color       _border_color     = sf::Color::White,
           sf::Texture     _background       = sf::Texture()) :
    Widget(_x0, _y0, _width, _height, _border_thickness, _border_color, _background),
    on_click (on_click_func)
    {};
};

void IncreaseTemperature(Flask* flask);
void DecreaseTemperature(Flask* flask);
void AddSquareParticle  (Flask* flask);
void AddCircleParticle  (Flask* flask);
void RaisePistole       (Flask* flask);
void DropPistole        (Flask* flask);

#endif //SYM_BUTTON
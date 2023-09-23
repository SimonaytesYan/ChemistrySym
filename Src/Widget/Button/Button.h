#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../Widget.h"
#include "../Flask/Flask.h"

typedef void (*OnClickFunction)(Flask* flask);

class Button : public Widget
{
public :

    OnClickFunction on_click;

    Button(double x0, 
           double y0, 
           double width, 
           double height,
           OnClickFunction on_click_func, 
           double border_thickness = 10) :
    Widget(x0, y0, width, height, border_thickness),
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
#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <SFML/Graphics.hpp>
#include <cmath>

const int kThicknessWeight = 10;

class Widget : public sf::RenderTexture
{
    double x0;
    double y0;

    public : 
    Widget(double X0, double Y0, double weight, double height) : 
    x0 (X0),
    y0 (Y0)
    { this->create(weight, height); }
    
    double GetX0() {return x0;}
    double GetY0() {return y0;} 

    ~Widget()
    {
        x0 = NAN;
        y0 = NAN;
        this->~Widget();
    }

    virtual void Draw(Widget* window);
    bool Inside_p(double x, double y);
};

#endif  //SYM_SUB_WINDOW
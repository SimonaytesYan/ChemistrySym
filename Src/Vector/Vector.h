#ifndef SYM_GEOM_VECTOR
#define SYM_GEOM_VECTOR

#include <SFML/Graphics.hpp>
#include <math.h>

class Widget;

#include "../CoordSystem/CoordSystem.h"

class Vector
{
    double x;
    double y;

    sf::Color color;

public : 
    Vector(double x, double y, sf::Color color = sf::Color::White);
    ~Vector();

    double    GetX()     {return x;};
    double    GetY()     {return y;};
    sf::Color GetColor() {return color;};

    void Dump();
    void Draw(Widget* texture, CoordSystem* coord_sys,  
                    double x0, double y0);
    double Length() const { return sqrt(x*x + y*y); };
    void   Rotate(double deg);

    operator sf::Vector2f() { return sf::Vector2f(x, y); };

    friend Vector operator+(const Vector& a, const Vector& b);
    friend Vector operator-(const Vector& a);
    friend Vector operator-(const Vector& a, const Vector& b);
    friend Vector operator*(const Vector& a, double b);
    friend Vector operator/(const Vector& a, double b);
    friend double operator,(const Vector& a, const Vector& b);  
    friend Vector operator!(const Vector& a);
    friend Vector operator+(const Vector& a);
    friend Vector operator^(const Vector& a, double b);
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, double b);
Vector operator/(const Vector& a, double b);
double operator,(const Vector& a, const Vector& b);		//scalar product
Vector operator!(const Vector& a);						//return normalized vector
Vector operator+(const Vector& a);						//return normal to vector
Vector operator^(const Vector& a, double b);            //rotate a by b degrees clockwise

#endif //SYM_GEOM_VECTOR

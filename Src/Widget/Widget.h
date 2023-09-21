#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <SFML/Graphics.hpp>
#include <cmath>

#include "../Vector/Vector.h"

const int kThicknessWeight = 10;

class Widget
{
    sf::RenderTexture texture;
    Vector            position;

public : 
    Widget(double x0, double y0, double width, double height);

    double GetX();
    double GetY(); 
    Vector GetSize();

    ~Widget();

    virtual void Draw(sf::RenderWindow* window);
    
    void DrawInside(const sf::Drawable     &drawable,
                    const sf::RenderStates &states = sf::RenderStates::Default)
    { texture.draw(drawable, states); }

    void DrawInside(const sf::Vertex       *vertices,
                    std::size_t 	        vertexCount,
                    sf::PrimitiveType 	    type,
                    const sf::RenderStates &states = sf::RenderStates::Default )
    { texture.draw(vertices, vertexCount, type, states); };

    bool Inside_p(double x, double y);
};

#endif  //SYM_SUB_WINDOW
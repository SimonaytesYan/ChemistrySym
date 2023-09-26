#ifndef SYM_PLOT
#define SYM_PLOT

#include "../Widget.h"
#include "../../CoordSystem/CoordSystem.h"
#include "../../DynArray.h"

class Plot : Widget
{
    DynArray<Vector> data;
    CoordSystem      coord_sys;
    sf::Color        plot_color;

public:
    Plot (double    _x0,
          double    _y0,
          double    _width,
          double    _height,
          double    coord_sys_x0,
          double    coord_sys_y0,
          double    coord_unit_x,
          double    coord_unit_y,
          sf::Color _plot_color       = sf::Color::White,
          double    _border_thickness = 0,
          sf::Color _border_color     = sf::Color::White);
    
    void Draw(sf::RenderWindow* window) override;
    void AddPoint(Vector point);
};

#endif //SYM_PLOT
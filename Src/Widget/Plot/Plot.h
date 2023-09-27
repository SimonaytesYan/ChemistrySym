#ifndef SYM_PLOT
#define SYM_PLOT

#include "../Widget.h"
#include "../../CoordSystem/CoordSystem.h"
#include "../../DynArray.h"

class Plot : public Widget
{
    DynArray<Vector> data;
    CoordSystem      coord_sys;
    sf::Color        plot_color;
    int              left_point_i;
    Vector           plot_unit;
    sf::Font         font;
    const char*      ox_string;
    const char*      oy_string;

public:
    Plot (double      _x0,
          double      _y0,
          double      _width,
          double      _height,
          double      coord_sys_x0,
          double      coord_sys_y0,
          double      coord_unit_x,
          double      coord_unit_y,
          Vector      _plot_unit,
          sf::Font    _font,
          const char* _ox_string,
          const char* _oy_string,
          sf::Color   _plot_color       = sf::Color::White,
          double      _border_thickness = 0,
          sf::Color   _border_color     = sf::Color::White);
    
    void   Draw(sf::RenderWindow* window) override;
    void   AddPoint(Vector point);
    Vector ReculcFromData(size_t index);
    void   DrawPlotUnits();
};

#endif //SYM_PLOT
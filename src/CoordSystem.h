#ifndef INCLUDE_COORD_SYSTEM
#define INCLUDE_COORD_SYSTEM
#include "ToolStructs.h"

class CoordSystem {

private:
    float x_min = 0;
    float y_min = 0;
    float x_max = 0;
    float y_max = 0;

    int pixel_x = 0;
    int pixel_y = 0;
    int pixel_width  = 0;
    int pixel_height = 0;

    float point_to_pixel_coeff_x = 0;
    float point_to_pixel_coeff_y = 0;

public:
    CoordSystem(){}
    ~CoordSystem(){
        //exit(1); // debug
    }

    CoordSystem(Rectf range_rect, Recti pixel_rect);

    Recti getPixelRect() const;
    Rectf getCoordRect() const;
    void translatePoint(const Pointf point, Pointf* result) const;
};

#endif
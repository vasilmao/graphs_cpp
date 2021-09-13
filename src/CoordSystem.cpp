#include "CoordSystem.h"

Recti CoordSystem::getPixelRect() const{
    return {pixel_x, pixel_y, pixel_width, pixel_height};
}

Rectf CoordSystem::getCoordRect() const {
    return {x_min, y_min, x_max - x_min, y_max - y_min};
}

CoordSystem::CoordSystem(Rectf range_rect, Recti pixel_rect) {
    x_min = range_rect.x;
    y_min = range_rect.y;
    x_max = range_rect.x + range_rect.width;
    y_max = range_rect.y + range_rect.height;

    pixel_x = pixel_rect.x;
    pixel_y = pixel_rect.y;
    pixel_width = pixel_rect.width;
    pixel_height = pixel_rect.height;

    point_to_pixel_coeff_x = pixel_width   / (x_max - x_min);
    point_to_pixel_coeff_y = pixel_height  / (y_max - y_min);
}

void CoordSystem::translatePoint(const Pointf point, Pointf* result) const {
    float delta_x = point.x - x_min;
    float delta_y = point.y - y_min;
    (*result).x = pixel_x +                 delta_x * point_to_pixel_coeff_x;
    (*result).y = pixel_y + (pixel_height - delta_y * point_to_pixel_coeff_y); // (pixel_height - ...) because y counts for top
}
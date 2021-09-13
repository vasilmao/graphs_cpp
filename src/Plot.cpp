#include "Plot.h"

const int POINT_CNT = 100;


// -------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------


Plot::Plot(CoordSystem coord_system, float (*function)(float x)) : coord_system(coord_system), function(function) {}

void Plot::render(Renderer* renderer) const {
    // prepare axis
    SDL_SetRenderDrawColor(renderer->renderer, 255, 255, 255, 255);
    Recti screen_rect = coord_system.getPixelRect();
    Rectf range_rect = coord_system.getCoordRect();
    SDL_Rect screen_rect_SDL = {screen_rect.x, screen_rect.y, screen_rect.width, screen_rect.height};
    SDL_RenderFillRect(renderer->renderer, &screen_rect_SDL);

    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    // todo: struct point
    Pointf zero_point;

    coord_system.translatePoint({0, 0}, &zero_point);
    printf("zero is %f %f\n", zero_point.x, zero_point.y);

    // horizontal
    Vector horizontal_axis(range_rect.width, 0);
    renderVector(renderer, horizontal_axis, {range_rect.x, 0});

    // vertical
    Vector vertical_axis(0, range_rect.height);
    renderVector(renderer, vertical_axis, {0, range_rect.y});

    // draw function
    SDL_FPoint points[POINT_CNT] = {};
    Rectf plot_rect = coord_system.getCoordRect();
    float point_step = plot_rect.width / POINT_CNT;
    float current_x = plot_rect.x;
    for (int i = 0; i < POINT_CNT; ++i, current_x += point_step) {
        Pointf pixel_point;
        float current_y = function(current_x);
        // полезно - plot->coords (с которым работаем) передавать первым
        coord_system.translatePoint({current_x, current_y}, &pixel_point);
        points[i] = {pixel_point.x, pixel_point.y};
    }
    SDL_RenderDrawLinesF(renderer->renderer, points, POINT_CNT);
    SDL_SetRenderDrawColor(renderer->renderer, 255, 0, 0, 255);
    SDL_RenderDrawPointF(renderer->renderer, zero_point.x, zero_point.y);
    SDL_RenderDrawPointF(renderer->renderer, zero_point.x + 1, zero_point.y + 1);
    SDL_RenderDrawPointF(renderer->renderer, zero_point.x + 1, zero_point.y);
    SDL_RenderDrawPointF(renderer->renderer, zero_point.x, zero_point.y + 1);
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
}

void Plot::renderVector(Renderer* renderer, const Vector& vector, const Pointf& point) const {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    renderSegment(renderer, vector, point);

    Vector reverse = vector * -1;
    reverse.normalize();
    
    Vector perp1, perp2;
    vector.getPerp(&perp1, &perp2);
    perp1 *= 0.3;
    perp2 *= 0.3;

    renderSegment(renderer, perp1 + reverse, point + vector);
    renderSegment(renderer, perp2 + reverse, point + vector);    
}

void Plot::renderSegment(Renderer* renderer, const Vector& seg_vector, const Pointf& point) const {
    Pointf real_point;
    Pointf real_vector_end;
    coord_system.translatePoint(point, &real_point);
    coord_system.translatePoint({point.x + seg_vector.getX(), point.y + seg_vector.getY()}, &real_vector_end);

    SDL_RenderDrawLineF(renderer->renderer, real_point.x, real_point.y, real_vector_end.x, real_vector_end.y);
}
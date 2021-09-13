#include "Vector.h"

Vector::Vector(float x, float y): x(x), y(y) {
    length = sqrt(x * x + y * y);
    angle  = atan2(y, x);
}

Vector::Vector(float x, float y, float speed): x(x), y(y), rotating_speed(speed) {
    length = sqrt(x * x + y * y);
    angle  = atan2(y, x);
}

void Vector::update() {
    angle += rotating_speed;
    x = length * cos(angle);
    y = length * sin(angle);
}

float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

float Vector::getLength() const {
    return length;
}

float Vector::getAngle() const {
    return angle;
}

void Vector::getPerp(Vector* res1, Vector* res2) const {
    *res1 = Vector(-y, x);
    (*res1).normalize();
    *res2 = *res1 * -1.0;
}

void Vector::normalize() {
    x /= length;
    y /= length;
    length = 1;
}

Vector& operator += (Vector& v1, const Vector& v2) {
    v1.x += v2.x;
    v1.y += v2.x;
    return v1;
}

Vector& operator -= (Vector& v1, const Vector& v2) {
    v1.x -= v2.x;
    v1.y -= v2.x;
    return v1;
}

Vector operator + (const Vector& v1, const Vector& v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y);
}

Pointf operator + (const Pointf& p, const Vector& v) {
    return {p.x + v.x, p.y + v.y};
}

Vector operator - (const Vector& v1, const Vector& v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

Vector operator * (const Vector& v1, const float coef) {
    return Vector(v1.x * coef, v1.y * coef);
}

Vector& operator *= (Vector& v1, const float coef) {
    v1.x *= coef;
    v1.y *= coef;
    return v1;
}

// void drawVector(SDL_Renderer* renderer, float x, float y, float x_pr, float y_pr) {
//     SDL_RenderDrawLineF(renderer, x, y, x + x_pr, y + y_pr);


//     float angle = atan2(y_pr, x_pr);
//     float length = sqrt(x_pr * x_pr + y_pr * y_pr);

//     float angle_arrow_left  = angle + M_PI * 5 / 6; //90 + 60
//     float angle_arrow_right = angle - M_PI * 5 / 6;
//     float arrow_length = length / 10;
//     float arrow_start_x = x + x_pr;
//     float arrow_start_y = y + y_pr;

//     float left_arrow_x2 = arrow_start_x + arrow_length * cos(angle_arrow_left);
//     float left_arrow_y2 = arrow_start_y + arrow_length * sin(angle_arrow_left);
//     SDL_RenderDrawLineF(renderer, arrow_start_x, arrow_start_y, left_arrow_x2, left_arrow_y2);

//     float right_arrow_x2 = arrow_start_x + arrow_length * cos(angle_arrow_right);
//     float right_arrow_y2 = arrow_start_y + arrow_length * sin(angle_arrow_right);
//     SDL_RenderDrawLineF(renderer, arrow_start_x, arrow_start_y, right_arrow_x2, right_arrow_y2);
// }

#ifndef INCLUDE_VECTOR_CLASS
#define INCLUDE_VECTOR_CLASS

#include <stdio.h>
#include <math.h>
#include "ToolStructs.h"

class Vector {

private:
    float x = 0;
    float y = 0;
    float length = 0;
    float angle = 0;
    float rotating_speed = 0;

public:
    Vector(float x, float y);

    Vector(float x, float y, float speed);

    Vector(){}
    ~Vector(){}

    void update();
    float getX() const;
    float getY() const;
    float getLength() const;
    float getAngle() const;
    void getPerp(Vector* res1, Vector* res2) const;
    void normalize();

    friend Vector& operator += (Vector& v1,     const Vector& v2);
    friend Vector& operator -= (Vector& v1,     const Vector& v2);
    friend Vector operator + (const Vector& v1, const Vector& v2);
    friend Pointf operator + (const Pointf& p, const Vector& v);
    friend Vector operator - (const Vector& v1, const Vector& v2);
    friend Vector operator * (const Vector& v1, const float coef);
    friend Vector& operator *= (Vector& v1, const float coef);

};


#endif
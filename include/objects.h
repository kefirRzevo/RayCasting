#ifndef OBJECTS_H
#define OBJECTS_H

#include "myvector.h"


struct Sphere
{
    double radius;
    Vector center;

    double Kd;
    double Ks;
    Vector color;
};

struct Lamp
{
    Vector position;
    Vector color;
    double Ka;
};

struct Camera
{
    Vector position;
    unsigned int width;
    unsigned int height;
};

#endif //OBJECTS_H

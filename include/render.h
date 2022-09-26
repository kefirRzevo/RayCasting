#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>

#include "myvector.h"


struct Sphere
{
    Vector center;
    double radius;
    double Kd;
    double Ks;
    Vector color;
};

struct Lamp
{
    Vector position;
    double Ka;
    Vector color;
};

struct Camera
{
    Vector position;
    unsigned int width;
    unsigned int height;
};

class Pixel
{
    private:
        sf::Uint8 R;
        sf::Uint8 G;
        sf::Uint8 B;
        sf::Uint8 A;

    public:
        Pixel():
            R(0), G(0), B(0), A(0) {};

        Pixel(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue):
            R(Red), G(Green), B(Blue), A(255) {};

        Pixel(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue, sf::Uint8 Alpha):
            R(Red), G(Green), B(Blue), A(Alpha) {};

        ~Pixel()
            {}

        Vector PixToVector(Pixel pxl)
            { return Vector(pxl.R/255, pxl.G/255, pxl.B/255); }
};

bool LineCrossSphere(Vector linepoint1, Vector linepoint2, 
                     double radius, Vector spherecenter, Vector& nearest_crosspoint);

Vector CountIntensity(Vector pixel, int n_spheres, 
                                  Sphere* spheres, Lamp lamp, Camera camera);

Pixel VectorToPix(Vector v, double Alpha);

#endif  //RENDER_H

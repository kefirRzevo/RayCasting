#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics.hpp>

#include "myvector.h"


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

Pixel VectorToPix(Vector v, double Alpha)
{
    double kR = v.GetX();
    double kG = v.GetY();
    double kB = v.GetZ();

    if(kR    < 0) kR    = 0; else if(kR    > 1) kR    = 1;
    if(kG    < 0) kG    = 0; else if(kG    > 1) kG    = 1;
    if(kB    < 0) kB    = 0; else if(kB    > 1) kB    = 1;
    if(Alpha < 0) Alpha = 0; else if(Alpha > 1) Alpha = 1;

    return Pixel((sf::Uint8)(kR*255), (sf::Uint8)(kG*255), (sf::Uint8)(kB*255), (sf::Uint8)(Alpha*255));
} 

#endif //PIXEL_H

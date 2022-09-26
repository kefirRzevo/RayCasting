#include <iostream>
#include <cmath>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "include/myvector.h"
#include "include/config.h"
#include "include/objects.h"
#include "include/pixel.h"
#include "include/angem.h"


Vector CountIntensity(Vector pixel, int n_spheres, 
                                          Sphere* spheres, Lamp lamp, Camera camera)
{
    int sphere = -1;
    double min_distance = 0;

    Vector cross_point  = Vector();
    Vector camera_point = camera.position;

    for(int i = 0; i < n_spheres; i++)
    {
        if(!LineCrossSphere(camera_point, pixel, 
                           spheres[i].radius, spheres[i].center, cross_point))
            continue;

        if(sphere < 0)
        {
            min_distance = cross_point.GetLen();
        }
        else
        {
            double current_distance = cross_point.GetLen();
            if(current_distance < min_distance)
                min_distance = current_distance;
        }
        sphere = i;
    }

    if(sphere < 0)
        return Vector();

    Vector normal = cross_point-spheres[sphere].center;
    normal.Normalize();
    Vector incident_beam  = lamp.position-cross_point;
    Vector reflected_beam = 2*ScalarMul(normal, incident_beam)*normal-incident_beam;
    Vector camera_beam    = lamp.position-cross_point;

    double D = Cos(normal, incident_beam);
    double S = std::pow(Cos(reflected_beam, camera_beam), n);

    return (D*spheres[sphere].Kd+lamp.Ka)*ComponentMul(     \
              spheres[sphere].color, lamp.color)+S*spheres[sphere].Ks*lamp.color;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

    Pixel *pixels  = new Pixel[WIDTH * HEIGHT];
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    sf::Sprite sprite(texture);

    Lamp   lamps[1]   = {};
    Sphere spheres[1] = {};
    Camera camera;

    lamps[0].color    = Vector(1, 1, 1);
    lamps[0].position = Vector(10, 500, 50);
    lamps[0].Ka = 0.15;

    lamps[1].color    = Vector(0.8, 0.9, 0.6);
    lamps[1].position = Vector(400, 600, 600);
    lamps[1].Ka = 0.2;

    spheres[0].center = Vector(400, 300, 200);
    spheres[0].color  = Vector(1, 0, 0);
    spheres[0].radius = 90;
    spheres[0].Kd = 0.4;
    spheres[0].Ks = 0.3;

    spheres[1].center = Vector(500, 200, 500);
    spheres[1].color  = Vector(0, 1, 0);
    spheres[1].radius = 50;
    spheres[1].Kd = 0.4;
    spheres[1].Ks = 0.3;

    camera.position = Vector(400, 300, -500);
    camera.height   = HEIGHT;
    camera.width    = WIDTH;

    for(unsigned int j = 0; j < camera.height; j++)
        for(unsigned int i = 0; i < camera.width; i++)
        {
            Vector ptcolor = Vector();
            for(int k = 0; k < 2; k++)
                ptcolor+=CountIntensity(Vector(i, j, 0), 2, spheres, lamps[k], camera);

            pixels[j*WIDTH+i] = VectorToPix(ptcolor, 255);
        }
    
    while(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        texture.update((sf::Uint8* )pixels);
        window.draw(sprite);
        window.display();
    }

    delete[] pixels;
    return 0;
}

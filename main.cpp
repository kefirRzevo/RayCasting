#include <iostream>
#include <cmath>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "include/myvector.h"
#include "include/config.h"
#include "include/render.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

    Pixel *pixels  = new Pixel[WIDTH * HEIGHT];
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    sf::Sprite sprite(texture);

    Camera camera;
    const unsigned int n_lamps   = 1;
    Lamp lamps[n_lamps] = {};
    const unsigned int n_spheres = 2;
    Sphere spheres[n_spheres] = {};


    lamps[0].position = Vector(0, 0, 100);
    lamps[0].Ka = 0.2;
    lamps[0].color = Vector(1, 1, 1);

    spheres[0].center = Vector(400, 400, 500);
    spheres[0].radius = 300;
    spheres[0].Kd = 0.4;
    spheres[0].Ks = 0.4;
    spheres[0].color = Vector(1, 1, 0);

    spheres[1].center = Vector(600, 600, 800);
    spheres[1].radius = 100;
    spheres[1].Kd = 0.4;
    spheres[1].Ks = 0.4;
    spheres[1].color = Vector(0, 1, 1);
/*
    spheres[2].center = Vector(20, 10, 300);
    spheres[2].radius = 200;
    spheres[2].Kd = 0.1;
    spheres[2].Ks = 0.1;
    spheres[2].color = Vector(1, 0, 1);*/

    camera.position = Vector(400, 300, -500);
    camera.height = HEIGHT;
    camera.width = WIDTH;

    for(unsigned int j = 0; j < camera.height; j++)
        for(unsigned int i = 0; i < camera.width; i++)
        {
            Vector pixcolor = Vector();
            for(int k = 0; k < n_lamps; k++)
                pixcolor += CountIntensity(Vector(i, j, 0), n_spheres, spheres, lamps[k], camera);

            pixels[j * WIDTH + i] = VectorToPix(pixcolor, 255);
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

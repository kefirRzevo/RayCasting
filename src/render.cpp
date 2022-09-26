#include "../include/render.h"
#include "../include/myvector.h"


bool LineCrossSphere(Vector l1, Vector l2, 
                 double radius, Vector r0, Vector& point)
{
    double r21  = ScalarMul(l2 - l1, l2 - l1);
    double r10  = ScalarMul(l1 - r0, l1 - r0);
    double r210 = ScalarMul(l2 - l1, l1 - r0);

    double a = r21, b = 2 * r210, c = r10 - radius * radius;
    double D = b * b - 4 * a * c;

    if(D <= 0)
        return false;

    double t1 = (-b - std::sqrt(D)) / (2 * a);
    double t2 = (-b + std::sqrt(D)) / (2 * a);

    if(fabs(t1) > fabs(t2))
        t1 = t2;

    point = l1 + t1 * (l2 - l1);
    return true;
}


Vector CountIntensity(Vector pixel, int n_spheres, 
                                  Sphere* spheres, Lamp lamp, Camera camera)
{
    int    nearest_sphere = -1;
    double min_distance   = 0;

    Vector  cross_point = Vector();
    Vector camera_point = camera.position;

    for(int i = 0; i < n_spheres; i++)
    {
        if(!LineCrossSphere(camera_point, pixel, 
                           spheres[i].radius, spheres[i].center, cross_point))
            continue;

        if(nearest_sphere < 0)
        {
            min_distance = (lamp.position-cross_point).GetLen();
        }
        else
        {
            double current_distance = (lamp.position - cross_point).GetLen();
            if(current_distance < min_distance)
                min_distance = current_distance;
        }
        nearest_sphere = i;
    }

    if(nearest_sphere < 0)
        return Vector();

    Vector normal = cross_point - spheres[nearest_sphere].center;
    normal.Normalize();
    Vector incident_beam  = lamp.position - cross_point;
    Vector reflected_beam = 2 * ScalarMul(normal, incident_beam) * normal - incident_beam;
    Vector camera_beam    = lamp.position - cross_point;

    double D = Cos(normal, incident_beam);
    double S = std::pow(Cos(reflected_beam, camera_beam), n);

    return (D * spheres[nearest_sphere].Kd + lamp.Ka) * ComponentMul( \
                spheres[nearest_sphere].color, lamp.color) + S * spheres[nearest_sphere].Ks * lamp.color;
}


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

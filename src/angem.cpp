#include "../include/myvector.h"

bool LineCrossSphere(Vector r1, Vector r2, 
                 double radius, Vector r0, Vector& point)
{
    double r21  = ScalarMul(r2-r1, r2-r1);
    double r10  = ScalarMul(r1-r0, r1-r0);
    double r210 = ScalarMul(r2-r1, r1-r0);

    double a = r21, b = 2*r210, c = r10-radius*radius;
    double D = b*b-4*a*c;

    if(D <= 0)
        return false;

    double t1 = (-b-std::sqrt(D))/(2*a);
    double t2 = (-b+std::sqrt(D))/(2*a);

    if(fabs(t1)>fabs(t2))
        t1 = t2;

    point = r1+t1*(r2-r1);
    return true;
}

#ifndef LINAL_H
#define LINAL_H

#include <cmath>
#include "myvector.h"


bool LineCrossSphere(Vector r1, Vector r2, 
                     double radius, Vector r0, Vector& point);

#endif //LINAL_H
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <cmath>

#include "config.h"


class Vector
{
    private:
        double x;
        double y;
        double z;

    public:
        Vector():
            x(0), y(0), z(0) {};

        Vector(double anX):
            x(anX), y(0), z(0) {};

        Vector(double anX, double anY):
            x(anX), y(anY), z(0) {};

        Vector(double anX, double anY, double anZ):
            x(anX), y(anY), z(anZ) {};

       ~Vector()
            {}

        void PrintVector()
            { std::cout << x << ";\t" << y << ";\t" << z << "\n"; }

        double GetX()
            { return x; }

        double GetY()
            { return y; }

        double GetZ()
            { return z; }

        double GetLen()
            { return std::sqrt(x*x+y*y+z*z); }

        double GetLen2()
            { return x*x+y*y+z*z; }

        Vector& operator += (const Vector& v)
        {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this;
        }

        Vector& operator -= (const Vector& v)
        {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            return *this;
        }

        Vector& operator *= (double k)
        {
            this->x *= k;
            this->y *= k;
            this->z *= k;
            return *this;
        }

        Vector& operator /= (double k)
        {
            assert(k < EPSILON);
            this->x /= k;
            this->y /= k;
            this->z /= k;
            return *this;
        }

        friend Vector operator + (Vector v1, Vector v2)
            { return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }

        friend Vector operator - (Vector v1, Vector v2)
            { return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }

        friend Vector operator * (Vector v, double k)
            { return Vector(v.x*k, v.y*k, v.z*k); }

        friend Vector operator * (double k, Vector v)
            { return Vector(v.x*k, v.y*k, v.z*k); }

        friend Vector operator / (Vector v, double k)
            {
                assert(k > EPSILON);
                return Vector(v.x/k, v.y/k, v.z/k); 
            }

        Vector Normalize()
            {
                double len = this->GetLen();
                assert(len != 0);
                return *this / this->GetLen(); 
            } 

        friend Vector VectorMul(Vector v1, Vector v2)
            { return Vector(v1.y * v2.z - v1.z * v2.y, 
                            v1.z * v2.x - v1.x * v2.z, 
                            v1.x * v2.y - v1.y * v2.x); }

        friend Vector ComponentMul(Vector v1, Vector v2)
            { return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); } 

        friend double ScalarMul(Vector v1, Vector v2)
            { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

        friend double Cos(Vector v1, Vector v2)
            {
                double len1 = v1.GetLen();
                double len2 = v2.GetLen();
                assert(len1 != 0 && len2 != 0);
                return ScalarMul(v1, v2)/(len1*len2); }
};

#endif  //MYVECTOR_H

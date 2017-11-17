#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "kep/Core.h"
namespace shad
{
    class Triangle
    {
    public:
        kep::Vector3 p[3];
        kep::Vector3 n;
        Triangle(kep::Vector3 _p0 = kep::Vector3(0.0f, 0.0f, 0.0f), kep::Vector3 _p1 = kep::Vector3(0.0f, 0.0f, 0.0f), kep::Vector3 _p2 = kep::Vector3(0.0f, 0.0f, 0.0f), kep::Vector3 _n = kep::Vector3(0.0f ,0.0f, 0.0f));
        ~Triangle();
        
    };
};
#endif //TRIANGLE_H_

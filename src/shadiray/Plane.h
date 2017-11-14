#ifndef SHAD_PLANE_H_
#define SHAD_PLANE_H_
#include "kep/Core.h"

namespace shad 
{
    class Plane
    {
    public:
        kep::Vector3 p;
        kep::Vector3 n;
        
        Plane(kep::Vector3 _point = kep::Vector3(0.0f, 0.0f, 0.0f), kep::Vector3 _normal = kep::Vector3(0.0f, 1.0f, 0.0f));
        ~Plane();
    };
};


#endif //SHAD_PLANE_H_

#ifndef SHAD_RAY_H_
#define SHAD_RAY_H_
#include "kep/Core.h"
namespace shad 
{
    class Ray
    {
    public:
        kep::Vector3 s;
        kep::Vector3 d;
        Ray(kep::Vector3 _source = kep::Vector3(0.0f, 0.0f, 0.0f), kep::Vector3 _direction = kep::Vector3(0.0f, 0.0f, 1.0f));
        ~Ray();
        
    };
};

#endif //SHAD_RAY_H_

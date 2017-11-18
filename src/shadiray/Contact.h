#ifndef SHAD_CONTACT_H_
#define SHAD_CONTACT_H_
#include "Triangle.h"
#include "Plane.h"
#include "Ray.h"
namespace shad
{
    class Contact//intersect
    {
    public:
        bool e;//exists
        kep::Vector3 p;//position
        
        Contact(bool _exists = false, kep::Vector3 _position = kep::Vector3(0.0f, 0.0f, 0.0f));
        ~Contact();
        static Contact rayPlane(Ray _ray, Plane _plane);
        static Contact rayTriangle(Ray _ray, Triangle _triangle);
    };
};

#endif //SHAD_CONTACT_H_

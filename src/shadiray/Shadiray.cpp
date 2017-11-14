#include "Shadiray.h"
using namespace shad;

Contact::Contact(bool _exists, kep::Vector3 _position)
{
    e = _exists;
    p = _position;
}
Contact::~Contact()
{
}

Contact Contact::rayPlane(Ray _ray, Plane _plane)
{
    float nu = kep::dot((_plane.p - _ray.s), _plane.n);
    float de = kep::dot(_ray.d, _plane.n);
    if(de == 0.0f)
        return Contact();
    
    float t = nu/de;
    if(t < 0.0f)
        return Contact();
    
    kep::Vector3 contact = _ray.s + (_ray.d*t);
    return Contact(true, contact);
}

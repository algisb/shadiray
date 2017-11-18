#include "Contact.h"
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
Contact Contact::rayTriangle(shad::Ray _ray, shad::Triangle _triangle)
{
    Plane plane(_triangle.p[0], _triangle.n);
    Contact contact = rayPlane(_ray, plane);
    if(!contact.e)//no intersection exit
        return Contact();
    
    //edge 0
    kep::Vector3 ab = _triangle.p[1] - _triangle.p[0];
    kep::Vector3 aq = contact.p - _triangle.p[0];
    kep::Vector3 c = kep::cross(ab,aq);
    float d = kep::dot(c, _triangle.n);
    if(d < 0)
        return Contact();
    //edge 1
    ab = _triangle.p[2] - _triangle.p[1];
    aq = contact.p - _triangle.p[1];
    c = kep::cross(ab,aq);
    d = kep::dot(c, _triangle.n);
    if(d < 0)
        return Contact();
    //edge 2
    ab = _triangle.p[0] - _triangle.p[2];
    aq = contact.p - _triangle.p[2];
    c = kep::cross(ab,aq);
    d = kep::dot(c, _triangle.n);
    if(d < 0)
        return Contact();    
    
    return contact;
}

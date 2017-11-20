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

Contact Contact::rayPlane(Ray _ray, Plane _plane)//total 17 ops
{
    float nu = kep::dot((_plane.p - _ray.s), _plane.n);//5 ops
    float de = kep::dot(_ray.d, _plane.n);//5 ops
    if(de == 0.0f)
        return Contact();
    
    float t = nu/de;// 1 op
    if(t < 0.0f)
        return Contact();
    
    kep::Vector3 contact = _ray.s + (_ray.d*t);//6 ops
    return Contact(true, contact);
}

Contact Contact::rayTriangle(shad::Ray _ray, shad::Triangle _triangle)//77 ops
{
    Plane plane(_triangle.p[0], _triangle.n);
    Contact contact = rayPlane(_ray, plane); //17 ops
    if(!contact.e)//no intersection exit
        return Contact();
    
    //edge 0
    kep::Vector3 ab = _triangle.p[1] - _triangle.p[0];//3ops
    kep::Vector3 aq = contact.p - _triangle.p[0];//3 ops
    kep::Vector3 c = kep::cross(ab,aq);//9 ops
    float d = kep::dot(c, _triangle.n);//5 ops
    if(d < 0)
        return Contact();
    //edge 1
    ab = _triangle.p[2] - _triangle.p[1];//3 ops
    aq = contact.p - _triangle.p[1];//3 ops
    c = kep::cross(ab,aq);//9 ops
    d = kep::dot(c, _triangle.n);//5 ops
    if(d < 0)
        return Contact();
    //edge 2
    ab = _triangle.p[0] - _triangle.p[2];//3 ops
    aq = contact.p - _triangle.p[2];//3 ops
    c = kep::cross(ab,aq);//9 ops
    d = kep::dot(c, _triangle.n);//5 ops
    if(d < 0)
        return Contact();    
    
    return contact;
}
Contact Contact::rayTriangleBarycentric(Ray _ray, Triangle _triangle)
{
    kep::Vector3 ab = _triangle.p[1] - _triangle.p[0];
    kep::Vector3 ac = _triangle.p[2] - _triangle.p[0];
    kep::Vector3 qp = _ray.d;

    kep::Vector3 n = _triangle.n;
    // Compute denominator d. If d <= 0, segment is parallel to or points
    // away from triangle, so exit early
    float d = kep::dot(qp, n);
    if (d <= 0.0f) 
        return Contact();
    // Compute intersection t value of pq with plane of triangle. A ray
    // intersects iff 0 <= t. Segment intersects iff 0 <= t <= 1. Delay
    // dividing by d until intersection has been found to pierce triangle
    
    kep::Vector3 ap = _ray.s - _triangle.p[0];
    float t = kep::dot(ap, n);
    if (t < 0.0f) 
        return Contact();
    
    // Compute barycentric coordinate components and test if within bounds
    kep::Vector3 e = kep::cross(qp, ap);
    float v = kep::dot(ac, e);
    if (v < 0.0f || v > d) 
        return Contact();
    
    float w = -kep::dot(ab, e);
    if (w < 0.0f || v + w > d) 
        return Contact();
    
    // Segment/ray intersects triangle. Perform delayed division and
    // compute the last barycentric coordinate component
    float ood = 1.0f / d;
    t *= ood;
    v *= ood;
    w *= ood;
    float u = 1.0f - v - w;
    return Contact(true, _ray.s + _ray.d * t);
}

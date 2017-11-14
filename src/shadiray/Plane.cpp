#include "Plane.h"

using namespace shad;

Plane::Plane(kep::Vector3 _point, kep::Vector3 _normal)
{
    p = _point;
    n = _normal;
}

Plane::~Plane()
{
}


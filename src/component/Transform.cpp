#include "Transform.h"

using namespace kelp;

Transform::Transform(kep::Vector3 _position, kep::Quaternion _orientation, kep::Vector3 _scale) : Component()
{
    m_position = _position;
    m_orientation = _orientation;
    m_scale = _scale;
}
Transform::~Transform()
{
    
}

void Transform::init()
{
    
}

void Transform::update()
{
    
}

void Transform::dump()
{
    printf("pos: %f %f %f\n", m_position.x, m_position.y, m_position.z);
}

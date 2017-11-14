#include "Camera.h"

using namespace kelp;

Camera::Camera(kep::Vector3 _up, kep::Matrix4 _projectionMat)
{
    m_up = _up;
    m_projectionMat = _projectionMat;
}
Camera::~Camera()
{
}

void Camera::init()
{
    if(m_owner->m_world->m_renderCamera == NULL)
        m_owner->m_world->m_renderCamera = this;
    m_transform = m_owner->getComponent<Transform>();
}
void Camera::update()
{
    m_transform->m_orientation.normalize();
    m_viewMat.setOrientationAndPos(m_transform->m_orientation, m_transform->m_position);
    m_viewMat.invert();
    m_viewMat = m_viewMat.transpose(); //cuz opengl is idgaf-major
    
    m_front =  m_viewMat * kep::Vector3(0.0f, 0.0f, -1.0f);
    m_front.normalize();
    
    m_left = kep::cross(m_up, m_front);
    m_left.normalize();
}

void Camera::render()
{
}

void Camera::setAsRenderCamera()
{
    m_owner->m_world->m_renderCamera = this;
}


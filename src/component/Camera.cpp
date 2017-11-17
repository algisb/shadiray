#include "Camera.h"
#include "Input.h"
#include "Time.h"
using namespace kelp;

Camera::Camera(kep::Vector3 _up, kep::Matrix4 _projectionMat, bool _possessed)
{
    m_up = _up;
    m_projectionMat = _projectionMat;
    m_possessed = _possessed;
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
    if(m_possessed)
        possessedControls();
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

void Camera::possessedControls()
{
    //Camera * rc = m_owner->m_world->m_renderCamera;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_W, Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position +=  (m_front*Time::s_deltaT) * 10.0f;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_S, Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position +=  (m_front*Time::s_deltaT) * -10.0f;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_A, Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_left*Time::s_deltaT) * 10.0f;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_D, Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_left*Time::s_deltaT) * -10.0f;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_E, Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_up*Time::s_deltaT) * 10.0f;
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_C, Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_up*Time::s_deltaT) * -10.0f;
    
    
    
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_LEFT, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        kep::Quaternion q;
        q.setEuler(m_up, -1.0f);
        m_transform->m_orientation *= q;
    }
    //printf("%f %f %f %f\n", m_transform->m_orientation.i, m_transform->m_orientation.j, m_transform->m_orientation.k, m_transform->m_orientation.r);
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_RIGHT, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        kep::Quaternion q;
        q.setEuler(m_up, 1.0f);
        m_transform->m_orientation *= q;
    }
    
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_UP, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        
        kep::Quaternion q;
        q.setEuler(m_left, -1.0f);
        m_transform->m_orientation *= q;
    }
    
    if(Input::Keyboard::is(Input::Keyboard::KeyboardKey::KEY_DOWN, Input::Keyboard::KeyboardAction::HELD))
    {
        //rc->m_transform->m_orientation.addScaledVector(kep::Vector3(0.0f, 1.0f, 0.0f), 0.01f);
        
        kep::Quaternion q;
        q.setEuler(m_left, 1.0f);
        m_transform->m_orientation *= q;
    }
}
void Camera::setAsRenderCamera()
{
    m_owner->m_world->m_renderCamera = this;
}


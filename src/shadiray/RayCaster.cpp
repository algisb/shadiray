#include "RayCaster.h"
#include "RayReciever.h"

using namespace shad;
RayCaster::RayCaster()
{
    m_maxRayLength = 40.0f;
    m_up = kep::Vector3(0.0f, 1.0f, 0.0f);
}
RayCaster::~RayCaster()
{
}

void RayCaster::init()
{
    m_transform = m_owner->getComponent<kelp::Transform>();
    ray = Ray(m_transform->m_position, kep::Vector3(0.0f, 0.0f, -1.0f).normalized());
    rline = new kelp::RenderLine(ray.s, ray.s + ray.d);
    m_owner->addComponent(rline);
}

void RayCaster::update()
{
    m_transform->m_orientation.normalize();
    kep::Matrix4 tmpMat4;
    tmpMat4.setOrientationAndPos(m_transform->m_orientation, m_transform->m_position);
    kep::Matrix3 tmpMat3 = kep::Matrix3(tmpMat4);
    Ray tempRay = Ray(ray.s, tmpMat3 * ray.d);
    //Contact c = Contact::rayPlane(tempRay, Plane(kep::Vector3(5.0f, 0.0f, 0.0f), kep::Vector3(-1.0f, 0.0f, 0.0f)));
    //Contact c = Contact::rayPlane(tempRay, Plane(RayReciever::s_rayRecievers[0]->m_tTriangles->p[0], RayReciever::s_rayRecievers[0]->m_tTriangles->n));
    Contact c = Contact::rayTriangle(tempRay, RayReciever::s_rayRecievers[0]->m_tTriangles[0]);
    if(c.e)
    {
        //printf("collision\n");
        rline->m_p0 = tempRay.s;
        rline->m_p1 = c.p;
    }
    else
    {
        //printf("no collision\n");
        rline->m_p0 = tempRay.s;
        rline->m_p1 = tempRay.s + (tempRay.d * m_maxRayLength);
    }
    
    
    
    m_front =  tmpMat3 * kep::Vector3(0.0f, 0.0f, -1.0f);
    m_front.normalize();
    
    m_left = kep::cross(m_up, m_front);
    m_left.normalize();
    
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_J, kelp::Input::Keyboard::KeyboardAction::HELD))
    {
        kep::Quaternion q;
        q.setEuler(kep::Vector3(0.0f, 1.0f, 0.0f), -1.0f);
        m_transform->m_orientation *= q;
    }
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_L, kelp::Input::Keyboard::KeyboardAction::HELD))
    {
        kep::Quaternion q;
        q.setEuler(kep::Vector3(0.0f, 1.0f, 0.0f), 1.0f);
        m_transform->m_orientation *= q;
    }
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_I, kelp::Input::Keyboard::KeyboardAction::HELD))
    {
        kep::Quaternion q;
        q.setEuler(m_left, -1.0f);
        m_transform->m_orientation *= q;
    }
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_K, kelp::Input::Keyboard::KeyboardAction::HELD))
    {   
        kep::Quaternion q;
        q.setEuler(m_left, 1.0f);
        m_transform->m_orientation *= q;
    }
    

    
}

void RayCaster::render()
{
}

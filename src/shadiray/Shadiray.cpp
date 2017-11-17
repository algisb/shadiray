#include "Shadiray.h"
#include "Input.h"
#include "Time.h"
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
    return Contact();
}




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
    Contact c = Contact::rayPlane(tempRay, Plane(kep::Vector3(5.0f, 0.0f, 0.0f), kep::Vector3(-1.0f, 0.0f, 0.0f)));
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



RayReciever::RayReciever()
{
    m_mesh = NULL;
    m_numTriangles = 0;
    m_triangles = NULL;
    m_tTriangles = NULL;
}

RayReciever::~RayReciever()
{
    delete[] m_triangles;
    delete[] m_tTriangles;
}

void RayReciever::init()
{
    m_mesh = m_owner->getComponent<kelp::Render>()->m_mesh; // get mesh from the renderer
    float * dataV = m_mesh->m_dataV;
    float * dataN = m_mesh->m_dataN;
    
    m_numTriangles = m_mesh->m_numVertices/3;
    m_triangles = new Triangle[m_numTriangles];
    m_tTriangles = new Triangle[m_numTriangles];
    
    for(int i = 0; i < m_mesh->m_numVertices*3; i = i + 9)
    {
        m_triangles[i/9] = (kep::Vector3( dataV[i+0], dataV[i+1], dataV[i+2]),
                                       kep::Vector3( dataV[i+3], dataV[i+4], dataV[i+5]),
                                       kep::Vector3( dataV[i+6], dataV[i+7], dataV[i+8]),
                                       kep::Vector3( dataN[i+0], dataN[i+1], dataN[i+2])
                                      );
    }
    //printf("num triangles: %d \n", m_triangles.size());
}

void RayReciever::update()
{
}

void RayReciever::render()
{
}



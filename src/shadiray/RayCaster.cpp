#include "RayCaster.h"
#include "RayReciever.h"
#include <Time.h>
#include "Shadiray.h"

using namespace shad;
RayCaster::RayCaster(int _width, int _height, float _nearPlane, float _farPlane, float _raySpread)
{
    m_width = _width;
    m_height = _height;
    m_nearPlane = _nearPlane;
    m_farPlane = _farPlane;
    m_raySpread = _raySpread;
    m_up = kep::Vector3(0.0f, 1.0f, 0.0f);
    m_front = kep::Vector3(0.0f, 0.0f, -1.0f);
    m_left = kep::Vector3(1.0f, 0.0f, 0.0f);
}
RayCaster::~RayCaster()
{
}

void RayCaster::init()
{
    m_transform = m_owner->getComponent<kelp::Transform>();
    //////////////////////////////////////////////////////////
    initViewCone();
    initRays();
}

void RayCaster::update()
{
    m_front =  kep::Matrix3(m_transform->m_modelMat) * kep::Vector3(0.0f, 0.0f, -1.0f);
    m_front.normalize();
    
    m_left = kep::cross(m_up, m_front);
    m_left.normalize();
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_T, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position +=  (m_front*kelp::Time::s_deltaT) * 10.0f;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_G, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position +=  (m_front*kelp::Time::s_deltaT) * -10.0f;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_F, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_left*kelp::Time::s_deltaT) * 10.0f;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_H, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_left*kelp::Time::s_deltaT) * -10.0f;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_Y, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_up*kelp::Time::s_deltaT) * 10.0f;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_N, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += (m_up*kelp::Time::s_deltaT) * -10.0f;
    
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
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_SPACE, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        printf("num rays:   %d \n", m_width*m_height);
        int numTri = 0;
        for(int i = 0; i<RayReciever::s_rayRecievers.size();i++)
            numTri += RayReciever::s_rayRecievers[i]->m_numTriangles;
        printf("num triangles:  %d \n", numTri);
        
        
        Ray ray(kep::Vector3(), kep::Vector3(0.0f, 0.0f, -1.0f).normalized());
        Triangle tri(kep::Vector3(-1.0f,-1.0f,-1.0f), kep::Vector3(1.0f,-1.0f,-1.0f), kep::Vector3(0.5f, 1.0f,-1.0f), kep::Vector3(0.0f, 0.0f, 1.0f).normalized());
        double singleCastTime = 0.0f;
        EXEC_TIMER_SAMPLE(singleCastTime,
        Contact::rayTriangle(ray, tri);
        );
        printf("single ray cast time:   %.9f s \n", singleCastTime);
        printf("predicted cast time:    %f s \n", singleCastTime * ((m_width*m_height)* numTri));
        
        double castTime = 0.0f;
        EXEC_TIMER(castTime,
        updateRays();
        );
        printf("actual cast time:  %f s \n", castTime);
        printf("\n");
    }
    
    updateViewCone();
}

void RayCaster::render()
{
}

void RayCaster::initRays()
{
    m_rays = new Ray*[m_width*m_height];//needs to be deleted
    m_rLines = new kelp::RenderLine*[m_width*m_height];//
    
    kep::Vector3 inD(-((m_width-1)/2)*m_raySpread, -((m_height-1)/2)*m_raySpread, -1.0f); //initial vector
    
    for(int j = 0; j<m_height; j++)
    {
        for(int i = 0; i<m_width; i++)
        {
            int tIndex = i+j*m_height;
            m_rays[tIndex] = new Ray(m_transform->m_position, (kep::Vector3(i*m_raySpread, j*m_raySpread, 0.0f) + inD).normalized()); 
            m_rLines[tIndex] =  new kelp::RenderLine(m_rays[tIndex]->s, m_rays[tIndex]->s + m_rays[tIndex]->d* m_farPlane);
            m_rLines[tIndex]->m_enabled = false;
            m_owner->addComponent(m_rLines[tIndex]);
        }
    }
}

void RayCaster::updateRays()
{
    for(int i = 0; i<m_width*m_height; i++)
    {
        
        Ray tempRay = Ray(m_transform->m_modelMatUnscaled * m_rays[i]->s, kep::Matrix3(m_transform->m_modelMatUnscaled) * m_rays[i]->d);
        bool collided = false;
        for(int j = 0; j<RayReciever::s_rayRecievers.size(); j++)
        {
            RayReciever::s_rayRecievers[j]->updateR();
            for(int k = 0; k<RayReciever::s_rayRecievers[j]->m_numTriangles; k++)
            {
                if(kep::dot(RayReciever::s_rayRecievers[j]->m_tTriangles[k].n, tempRay.d) > 0.0f) // check if polygon normal is facing away
                    continue;
                Contact c = Contact::rayTriangle(tempRay, RayReciever::s_rayRecievers[j]->m_tTriangles[k]);
                if(c.e)
                {
                    //printf("collision\n");
                    m_rLines[i]->m_p0 = tempRay.s;
                    m_rLines[i]->m_p1 = c.p;
                    m_rLines[i]->m_enabled = true;
                    collided = true;
                    break;
                }
            }
        }
//         m_rLines[i]->m_p0 = tempRay.s;
//         m_rLines[i]->m_p1 = tempRay.s + (tempRay.d * m_farPlane)
        if(!collided)
            m_rLines[i]->m_enabled = false;
        
        
    }
}

void RayCaster::initViewCone()
{
    kep::Vector3 d[4];
    d[0] = kep::Vector3(-((m_width-1)/2)*m_raySpread, -((m_height-1)/2)*m_raySpread, -1.0f).normalized();
    d[1] = kep::Vector3(-((m_width-1)/2)*m_raySpread, ((m_height-1)/2)*m_raySpread, -1.0f).normalized();
    d[2] = kep::Vector3(((m_width-1)/2)*m_raySpread, ((m_height-1)/2)*m_raySpread, -1.0f).normalized();
    d[3] = kep::Vector3(((m_width-1)/2)*m_raySpread, -((m_height-1)/2)*m_raySpread, -1.0f).normalized();
    
    for(int i = 0; i<4; i++)
        m_viewCone[i] = Ray(kep::Vector3(), d[i]);
    
    for(int i = 0; i<12; i++)
    {
        m_vcLines[i] = new kelp::RenderLine(kep::Vector3(), kep::Vector3());
        m_owner->addComponent(m_vcLines[i]);
    }
    
}

void RayCaster::updateViewCone()
{
    for(int i = 0; i<4; i++)
    {
        m_vcLines[i]->m_p0 = m_transform->m_modelMatUnscaled*(m_viewCone[i].s + m_viewCone[i].d * m_nearPlane);
        m_vcLines[i]->m_p1 = m_transform->m_modelMatUnscaled*(m_viewCone[i].s + m_viewCone[i].d * m_farPlane);
    }
    for(int i = 4; i<8; i++)
    {
        int i0 = i - 4;
        int i1 = i0 + 1;
        int i2 = i + 4;
        if(i1 > 3)
            i1 = 0;
        
        m_vcLines[i]->m_p0 = m_vcLines[i0]->m_p0;
        m_vcLines[i]->m_p1 = m_vcLines[i1]->m_p0;
        
        m_vcLines[i2]->m_p0 = m_vcLines[i0]->m_p1;
        m_vcLines[i2]->m_p1 = m_vcLines[i1]->m_p1;
    }
}


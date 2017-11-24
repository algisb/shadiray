#include "RayCaster.h"
#include "RayReciever.h"
#include <Time.h>
#include "Shadiray.h"
#include "Contact.h"
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
    initBoxVolume();
}

void RayCaster::update()
{
    m_front =  kep::Matrix3(m_transform->m_modelMat) * kep::Vector3(0.0f, 0.0f, -1.0f);
    m_front.normalize();
    
    m_left = kep::cross(m_up, m_front);
    m_left.normalize();
    
    const float movSpd = 20.0f * kelp::Time::s_deltaT;
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_T, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += m_front * movSpd;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_G, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += m_front * -movSpd;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_F, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += m_left * movSpd;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_H, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += m_left * -movSpd;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_Y, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += m_up * movSpd;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_N, kelp::Input::Keyboard::KeyboardAction::HELD))
        m_transform->m_position += m_up * -movSpd;
    
    const float rotSpd = 70.0f * kelp::Time::s_deltaT;
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_J, kelp::Input::Keyboard::KeyboardAction::HELD))
    {
        kep::Quaternion q;
        q.setEuler(kep::Vector3(0.0f, 1.0f, 0.0f), -rotSpd);
        m_transform->m_orientation *= q;
    }
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_L, kelp::Input::Keyboard::KeyboardAction::HELD))
    {
        kep::Quaternion q;
        q.setEuler(kep::Vector3(0.0f, 1.0f, 0.0f), rotSpd);
        m_transform->m_orientation *= q;
    }
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_I, kelp::Input::Keyboard::KeyboardAction::HELD))
    {
        kep::Quaternion q;
        q.setEuler(m_left, -rotSpd);
        m_transform->m_orientation *= q;
    }
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_K, kelp::Input::Keyboard::KeyboardAction::HELD))
    {   
        kep::Quaternion q;
        q.setEuler(m_left, rotSpd);
        m_transform->m_orientation *= q;
    }
    


    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_1, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        printf("Cone raycast brute-force ray triangle intersection \n");
        printf("77 flops per test \n");
        updateRays(rayTriangleBForce, 0);
    }
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_2, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        printf("Cone raycast MT97 ray triangle intersection \n");
        printf("64 flops per test \n");
        updateRays(rayTriangleMT97, 0);
    }
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_3, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        printf("Box raycast brute-force ray triangle intersection \n");
        printf("64 flops per test \n");
        updateRays(rayTriangleBForce, 1);
    }
    
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_4, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        printf("Box raycast MT97 ray triangle intersection \n");
        printf("64 flops per test \n");
        updateRays(rayTriangleMT97, 1);
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
            m_rays[tIndex] = new Ray(kep::Vector3(), (kep::Vector3(i*m_raySpread, j*m_raySpread, 0.0f) + inD).normalized()); 
            m_rLines[tIndex] =  new kelp::RenderLine(m_rays[tIndex]->s, m_rays[tIndex]->s + m_rays[tIndex]->d* m_farPlane);
            m_rLines[tIndex]->m_enabled = false;
            m_owner->addComponent(m_rLines[tIndex]);
        }
    }
    //m_owner->addComponent(new kelp::RenderLineUI(kep::Vector3(-6,-4,-10), kep::Vector3(-4,-4, -10)));
}
#define TEST_FACILITY(_func2Test)\
{\
uint64_t numRays = (m_width*m_height);\
printf("num rays:   %llu \n", numRays);\
uint64_t numTri = 0;\
for(int i = 0; i<RayReciever::s_rayRecievers.size();i++)\
    numTri += RayReciever::s_rayRecievers[i]->m_numTriangles;\
printf("num triangles:  %llu \n", numTri);\
printf("num tests:  %llu \n", numTri*numRays);\
Ray ray(kep::Vector3(), kep::Vector3(0.0f, 0.0f, -1.0f).normalized());\
Triangle tri(kep::Vector3(-1.0f,-1.0f,-1.0f), kep::Vector3(1.0f,-1.0f,-1.0f), kep::Vector3(0.5f, 1.0f,-1.0f), kep::Vector3(0.0f, 0.0f, 1.0f).normalized());\
kep::Vector3 p;\
double singleCastTime = 0.0f;\
EXEC_TIMER_SAMPLE(singleCastTime,\
_testFunc(&ray, &tri, &p);\
);\
printf("1 ray vs 1 triangle average test time:   %.9f s \n", singleCastTime);\
printf("all rays vs 1 triangle test time:   %.9f s \n", singleCastTime * numRays);\
printf("predicted total test time:    %f s \n", singleCastTime * (double)(numRays* numTri));\
double testTime = 0.0f;\
EXEC_TIMER(testTime ,\
_func2Test;\
);\
printf("actual test time:  %f s \n", testTime );\
printf("\n");\
}

void RayCaster::updateRays(int (*_testFunc)(Ray *, Triangle *,  kep::Vector3 * ), int _type)
{
    for(int j = 0; j<RayReciever::s_rayRecievers.size(); j++)
        RayReciever::s_rayRecievers[j]->updateR();//updates triangles using their model matrix
    
    //different casting approaches
    switch(_type)
    {
        case 0:
            TEST_FACILITY(raycastCone(_testFunc));
            break;
        case 1:
            for(int x = 0; x<m_width; x++)
                for(int y = 0; y<m_height; y++)
                {
                    Ray tempRay = Ray(kep::Vector3(0,x,y), kep::Vector3(1, 0, 0).normalized());
                    int xy = x*m_height + y;
                    m_rLines[xy]->m_p0 = tempRay.s;
                    m_rLines[xy]->m_p1 = tempRay.s + tempRay.d;
                    m_rLines[xy]->m_enabled = true;
                }
            TEST_FACILITY(raycastBox(_testFunc));
            break;
    }
    
}

void RayCaster::raycastCone(int (*_testFunc)(Ray *, Triangle *,  kep::Vector3 * ))
{
    for(int i = 0; i<m_width*m_height; ++i)
    {
        Ray tempRay = Ray(m_transform->m_modelMatUnscaled * m_rays[i]->s, kep::Matrix3(m_transform->m_modelMatUnscaled) * m_rays[i]->d);
        bool collided = false;
        for(int j = 0; j<RayReciever::s_rayRecievers.size(); ++j)
            for(int k = 0; k<RayReciever::s_rayRecievers[j]->m_numTriangles; ++k)
            {
                if(kep::dot(RayReciever::s_rayRecievers[j]->m_tTriangles[k].n, tempRay.d) > 0.0f) // check if polygon normal is facing away
                    continue;
                kep::Vector3 p;
                if(_testFunc(&tempRay, &RayReciever::s_rayRecievers[j]->m_tTriangles[k], &p) == 1)
                {
                    m_rLines[i]->m_p0 = tempRay.s;
                    m_rLines[i]->m_p1 = p;
                    m_rLines[i]->m_enabled = true;
                    collided = true;
                    break;
                }
            }
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


void RayCaster::raycastBox(int (*_testFunc)(Ray *, Triangle *,  kep::Vector3 * ))
{
    Contacts contacts;
    
    for(int j = 0; j<RayReciever::s_rayRecievers.size(); ++j)
        for(int k = 0; k<RayReciever::s_rayRecievers[j]->m_numTriangles; ++k)
            
            for(int x = 0; x<m_width; ++x)
                for(int y = 0; y<m_height; ++y)
                {
                    Ray tempRay = Ray(kep::Vector3(0,x,y), kep::Vector3(1, 0, 0));
                    kep::Vector3 p;
                    if(_testFunc(&tempRay, &RayReciever::s_rayRecievers[j]->m_tTriangles[k], &p) == 1)
                    {
                        int xy = x*m_height + y;
                        m_rLines[xy]->m_p0 = tempRay.s;
                        m_rLines[xy]->m_p1 = p;
                        contacts.push_back(new Contact(p, tempRay, RayReciever::s_rayRecievers[j]->m_tTriangles[k]));
                    }
                }
    //Contact::printToConsole(contacts);
    Contact::writeToLogFile(contacts);
    for(uint64_t i = 0; i<contacts.size(); i++)
        delete contacts[i];
    contacts.clear();
    
}
void RayCaster::initBoxVolume()
{

    m_box[0] = kep::Vector3(0.0f, 0.0f, 0.0f);
    m_box[1] = kep::Vector3(0.0f, m_width, 0.0f);
    m_box[2] = kep::Vector3(0.0f, m_width, m_height);
    m_box[3] = kep::Vector3(0.0f, 0.0f, m_height);
    
    m_box[4] = kep::Vector3(255, 0.0f, 0.0f);
    m_box[5] = kep::Vector3(255, m_width, 0.0f);
    m_box[6] = kep::Vector3(255, m_width, m_height);
    m_box[7] = kep::Vector3(255, 0.0f, m_height);
    
    int l = 0;
    for(int i = 0; i<4; i++)
    {
        int ind1 = i;
        int ind2 = i+1;
        if(ind2 > 3)
            ind2 = 0;
        
        m_bLines[l] = new kelp::RenderLine(m_box[ind1], m_box[ind2]);
        m_owner->addComponent(m_bLines[l]);
        l++;
        m_bLines[l] = new kelp::RenderLine(m_box[ind1+4], m_box[ind2+4]);
        m_owner->addComponent(m_bLines[l]);
        l++;
        m_bLines[l] = new kelp::RenderLine(m_box[ind1], m_box[ind1+4]);
        m_owner->addComponent(m_bLines[l]);
        l++;
    }
        

    
}


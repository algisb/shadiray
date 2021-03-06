#include "RayReciever.h"
using namespace shad;

std::vector<RayReciever*> RayReciever::s_rayRecievers = std::vector<RayReciever*>();

RayReciever::RayReciever()
{
    m_mesh = NULL;
    m_numTriangles = 0;
    m_triangles = NULL;
    m_tTriangles = NULL;
    m_transform = NULL;
    s_rayRecievers.push_back(this); //also neeeds to ber removed in destructor
}

RayReciever::~RayReciever()
{
    delete[] m_triangles;
    delete[] m_tTriangles;
}

void RayReciever::init()
{
    m_mesh = m_owner->getComponent<kelp::Render>()->m_mesh; // get mesh from the renderer
    m_transform = m_owner->getComponent<kelp::Transform>();
    float * dataV = m_mesh->m_dataV;
    float * dataN = m_mesh->m_dataN;
    
    m_numTriangles = m_mesh->m_numVertices/3;
    m_triangles = new Triangle[m_numTriangles];
    m_tTriangles = new Triangle[m_numTriangles];
    
    for(int i = 0; i < m_mesh->m_numVertices*3; i = i + 9)
    {
        m_triangles[i/9] = Triangle(kep::Vector3( dataV[i+0], dataV[i+1], dataV[i+2]),
                            kep::Vector3( dataV[i+3], dataV[i+4], dataV[i+5]),
                            kep::Vector3( dataV[i+6], dataV[i+7], dataV[i+8]),
                            kep::Vector3( dataN[i+0], dataN[i+1], dataN[i+2])
                                      );
    }
}

void RayReciever::update()
{
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_MINUS, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        m_transform->m_scale = m_transform->m_scale - kep::Vector3(1.0f, 1.0f, 1.0f);
        printf("scale: x%d \n", (int)m_transform->m_scale.x);
    }
    if(kelp::Input::Keyboard::is(kelp::Input::Keyboard::KeyboardKey::KEY_EQUAL, kelp::Input::Keyboard::KeyboardAction::PRESSED))
    {
        m_transform->m_scale = m_transform->m_scale + kep::Vector3(1.0f, 1.0f, 1.0f);
        printf("scale: x%d \n", (int)m_transform->m_scale.x);
    }
}

void RayReciever::render()
{
}

void RayReciever::updateR()
{
    for(int i = 0 ; i < m_numTriangles; i++)
    {
        m_tTriangles[i] = Triangle(m_transform->m_modelMat * m_triangles[i].p[0],
                                   m_transform->m_modelMat * m_triangles[i].p[1],
                                   m_transform->m_modelMat * m_triangles[i].p[2],
                                   kep::Matrix3(m_transform->m_modelMat) * m_triangles[i].n);
    }
}
